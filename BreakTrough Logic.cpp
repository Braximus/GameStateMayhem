#include "stdafx.h"
#include "BreakTrough Data.h"
#include "BreakTrough Logic.h"
#include "BreakTrough Player.h"

#include "BreakTrough UI Manager.h"
#include "BreakTrough Ball.h"



BreakTrough_Logic::BreakTrough_Logic(BreakTrough_Data& data)
	:mData(data)
{
	erase_ball = false;
	score_buffer = 0;
}

void BreakTrough_Logic::pass_Pointers(BreakTrough_Player* pPlay, BreakTrough_Level_Manager* pLevel, BreakTrough_UI_Manager* pUI)
{
	pPlayer = pPlay;
	pLevel_Manager = pLevel;
	pUI_Manager = pUI;
}

void BreakTrough_Logic::Logic_function()
{
	Reset_Block_animations();
	check_Collisions();
}

void BreakTrough_Logic::check_boundry_hits()
{
	//	Kada su granice razlicitog tipa, da se izbrise!
	if (boundry_hits.size() > 1)
	{
		for (auto& i : boundry_hits)
		{
			if (i != boundry_hits.at(0))
			{
				boundry_hits.clear();
				break;
			}
		}
	}
}

void BreakTrough_Logic::check_Collisions()
{
	//	Pedala i Nivo
	Paddle_Movement_restriction();
	//	Lopte
	for (auto& it : pPlayer->get_Balls())
	{
		//	Lopta i pedala
		Ball_Paddle_Collision_response(it);
		// Lopta i blokovi
		Ball_Block_Collision_response(it);
		//	Odbijanje lopte o ivicu igralista.
		Ball_Level_Collision_response(it);
	}
	// PowerUp
	PowerUp_Behavior();	
	//	Laser
	Laser_Behavior_and_Block_Collision();
	//	Kada se izgubi lopta:
	Ball_Lost();
}

void BreakTrough_Logic::Paddle_Movement_restriction()
{

	//	Kada je pedala van nivoa, onda ce se vratiti na mesto odakle je izasao.
	if (((pPlayer->get_Paddle().getBounds().left + pPlayer->get_Paddle().getBounds().width) > (pLevel_Manager->get_Level_Bounds().left + pLevel_Manager->get_Level_Bounds().width)))
	{
		float b = pLevel_Manager->get_Level_Bounds().left + pLevel_Manager->get_Level_Bounds().width - pPlayer->get_Paddle().getBounds().width / 2;
		pPlayer->get_Paddle().setPosition(sf::Vector2f(b, 0));
	}
	else if (pPlayer->get_Paddle().getBounds().left < pLevel_Manager->get_Level_Bounds().left)
	{
		float b = pLevel_Manager->get_Level_Bounds().left + pPlayer->get_Paddle().getBounds().width / 2;
		pPlayer->get_Paddle().setPosition(sf::Vector2f(b, 0));
	}
}

sf::Vector2f BreakTrough_Logic::Ball_velocity_calculation(BrkTr_Ball& param)
{
	//	Racunam angle u zavisnosti od mesta udara na pedalu:

	sf::Vector2f vel;
	float angle, x, y;
	float relative_intersect = (pPlayer->get_Paddle().getBounds().left + (pPlayer->get_Paddle().getBounds().width / 2)) - param.getPosition().x;
	float normalised_relative_intersection = relative_intersect / (pPlayer->get_Paddle().getBounds().width / 2);
	angle = normalised_relative_intersection * 60;
	// Uvek moram da povecam za 270 stepeni, da bi lopta isla uspravno!
	angle += 270;
	angle = static_cast<float>(angle*(3.14 / 180));
	param.setAngle(angle);
	x = -cos(angle);
	y = sin(angle);

	return vel = sf::Vector2f(x, y);
}

void BreakTrough_Logic::Ball_Random_direction_launch(bool is_left_boundry, BrkTr_Ball& ball)
{
	//	Ova funkcija se poziva kada lopta treci put dodirne granicu nivoa koji je istog vertikalnog odstojanja;
	int sign;
	std::default_random_engine& random = mData.get_Random_Engine();

	std::uniform_int_distribution<int> i(0, 100);
	UINT percent = i(random);
	if (percent > 50)
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	std::uniform_int_distribution<int> j(15, 45);
	float angle = static_cast<float>(sign * j(random));

	//angle = -30;
	angle = angle*(3.14 / 180);

	float x;
	if (is_left_boundry)
	{
		x = cos(angle);
	}
	else
	{
		x = -cos(angle);
	}
	float y = sin(angle);

	sf::Vector2f vel = sf::Vector2f(x, y)*mData.get_Speed(pPlayer->get_Current_Ball_Speed());
	ball.setVelocity(vel);
}

void BreakTrough_Logic::Ball_Block_Collision_response(BrkTr_Ball& ball)
{
	
	sf::FloatRect ball_bounds = ball.getBounds();
	std::map<UINT, sf::FloatRect>	collided_bl_bounds;

	for (UINT i = 0; i < pLevel_Manager->get_Number_of_Total_Blocks(); ++i)
	{
		//	Prvo proveravam da li je blok uopste ziv, ako jeste onda proveravamo granice.
		if (pLevel_Manager->get_Block_Health(i) != 0)	
		{
			sf::FloatRect bl = pLevel_Manager->get_Block_Bounds(i);

			if (bl.intersects(ball_bounds))
			{
				//	Ako ga udarila, ubacujem granicu bloka u zaseban kontejner za detaljan odgovor - bitno je ako je udarila
				//	vise blokova.
				collided_bl_bounds.insert(std::pair<UINT, sf::FloatRect>(i,bl));
			}
		}
	}
	//	Odgovor
	if (!collided_bl_bounds.empty())
	{
		//	Prvo gledam da li ima vise od jednog sudara sa blokom:
		if (collided_bl_bounds.size() > 1)
		{
			//	Potom gledam koji sudar je skalarno veci.
			//	Kada ga pronadjem lopta ce njega "udariti".
			//	Ali odgovor na loptu ce biti drugaciji.
			
			//	Pre toga, moram da proverim povrsinu preseka.
			//	Ovde ih skupljam:
			std::map<UINT, sf::FloatRect> intersections;
			for (std::map<UINT, sf::FloatRect>::iterator it = collided_bl_bounds.begin(); it != collided_bl_bounds.end(); ++it)
			{
				sf::FloatRect intrs;
				it->second.intersects(ball_bounds, intrs);
				intersections.insert(std::pair<UINT, sf::FloatRect>(it->first, intrs));

			}

			//	Onda gledam koji je presek veci.
			//	Kada pronadjem, on je "alfa" - njega ce lopta unistiti.
			sf::FloatRect alpha_intrs;
			UINT alpha_indice;
			std::max_element(intersections.begin(), intersections.end(), [&](std::pair<UINT, sf::FloatRect> a, std::pair<UINT, sf::FloatRect> b)
			{
				if (a.second.width >= b.second.width && a.second.height >= b.second.height)
				{
					alpha_intrs = a.second;
					alpha_indice = a.first;
					return true;
				}
				else
				{
					alpha_intrs = b.second;
					alpha_indice = b.first;
					return false;
				}
			});

			//	Ovde eventualno da stavim da se izbrise najmanji element, ako ih ima vise od dva.

			//	Ubacujem drugi presek kao beta - "beta blok". Njega lopta nece unistiti, ali cu koristiti njegove granice da 
			//	napravim odgovor za loptu.
			UINT beta_indice;
			for (std::map<UINT, sf::FloatRect>::iterator it = collided_bl_bounds.begin(); it != collided_bl_bounds.end(); ++it)
			{
				if (it->first != alpha_indice)
				{
					beta_indice = it->first;
				}
			}

			//	Glavna granica - ona je spoj dve granice bloka koju je lopta udarila.
			//	Oblik (da li ce biti uspravan ili lezeci pravougaonik) zavisi od mesta gde se nalazi "beta" blok.
			sf::FloatRect final_rect;

			//	Ako su jedan do drugog sa leve ili sa desne strane:
			if (beta_indice == alpha_indice + 1)
			{
				final_rect.left = collided_bl_bounds.at(alpha_indice).left;
				final_rect.top = collided_bl_bounds.at(alpha_indice).top;
				final_rect.width = collided_bl_bounds.at(alpha_indice).width + collided_bl_bounds.at(beta_indice).width;
				final_rect.height = collided_bl_bounds.at(alpha_indice).height;
			}
			else if (beta_indice == alpha_indice - 1)
			{
				final_rect.left = collided_bl_bounds.at(beta_indice).left;
				final_rect.top = collided_bl_bounds.at(beta_indice).top;
				final_rect.width = collided_bl_bounds.at(alpha_indice).width + collided_bl_bounds.at(beta_indice).width;
				final_rect.height = collided_bl_bounds.at(alpha_indice).height;
			}
			//	Ako su jedno do drugog s gornje ili s donje strane:
			else if (beta_indice == alpha_indice - 10) 
			{
				final_rect.left = collided_bl_bounds.at(beta_indice).left;
				final_rect.top = collided_bl_bounds.at(beta_indice).top;
				final_rect.width = collided_bl_bounds.at(alpha_indice).width;
				final_rect.height = collided_bl_bounds.at(alpha_indice).height + collided_bl_bounds.at(beta_indice).height;
			}
			else 
			{
				final_rect.left = collided_bl_bounds.at(alpha_indice).left;
				final_rect.top = collided_bl_bounds.at(alpha_indice).top;
				final_rect.width = collided_bl_bounds.at(alpha_indice).width;
				final_rect.height = collided_bl_bounds.at(alpha_indice).height + collided_bl_bounds.at(beta_indice).height;
			}
			//	Za sada, treba i dijagonalno da se misli... to cu kasnije i ovo je dovoljno.

			//	I konacno odgovor:
			Ball_Block_Response(ball, final_rect);
			Block_hit(alpha_indice, final_rect);
			boundry_hits.clear();	 //	Brisem prethodne udarce o zid;
		}
		else
		{
			//	Ako postoji samo jedan onda samo dajem odgovor:
			std::map<UINT, sf::FloatRect>::iterator it = collided_bl_bounds.begin();
			Ball_Block_Response(ball, it->second);
			Block_hit(it->first, it->second);
			boundry_hits.clear();	 //	Brisem prethodne udarce o zid;
		}
	}

}

void BreakTrough_Logic::Ball_Level_Collision_response(BrkTr_Ball& ball)
{
	sf::FloatRect ball_bounds = ball.getBounds();
	sf::FloatRect level_bounds = pLevel_Manager->get_Level_Bounds();



	// Ovde se brise lopta kada dodirne dno.
	if (ball_bounds.top + ball_bounds.height > level_bounds.top + level_bounds.height)	//	Kada dodirne dno
	{
		ball.set_delete(true);
		boundry_hits.clear();	 //	Brisem prethodne udarce o zid;
		erase_ball = true;
	}
	//	Lopta ce se odbiti samo kada je njena vektorsa speed u suprotnosti od mesta gde je izasla iz nivoa.
	else if (ball_bounds.top < level_bounds.top)
	{
		if (ball.getVelocity().y < 0)
		{
			mData.Play_Sound(Break::snd_Wall_hit);
			ball.bounce(false);
			boundry_hits.clear();	 //	Brisem prethodne udarce o zid;
		}
	}
	
	//	Proveravam da li je lopta udarila levu stranu nivoa.
	for (const auto& it : pLevel_Manager->get_Left_Boundries())
	{
		if (it.second.intersects(ball_bounds))
		{
			if (boundry_hits.size() >= 3)
			{
				Ball_Random_direction_launch(true, ball);
				boundry_hits.clear();	 //	Brisem prethodne udarce o zid;
			}
			else
			{
				if (ball.getVelocity().x < 0)
				{
					mData.Play_Sound(Break::snd_Wall_hit);
					boundry_hits.push_back(it.first);	//	Dodaje tip pozicije granice koji je udaren; 
														//	Kada lopta tri puta udari granicu istog tipa pozicije, 
														//	lopta biva usmerena na nasumicnu direkciju;
					ball.bounce(true);
				}
			}
		}
	}

	//	Proveravam da li je lopta udarila levu stranu nivoa.
	for (const auto& it : pLevel_Manager->get_Right_Boundries())
	{
		if (it.second.intersects(ball_bounds))
		{
			if (boundry_hits.size() >= 3)
			{
				Ball_Random_direction_launch(false, ball);
				boundry_hits.clear();	 //	Brisem prethodne udarce o zid;
			}
			else
			{
				if (ball.getVelocity().x > 0)
				{
					mData.Play_Sound(Break::snd_Wall_hit);
					boundry_hits.push_back(it.first);	//	Dodaje tip pozicije granice koji je udaren; 
														//	Kada lopta tri puta udari granicu istog tipa pozicije, 
														//	lopta biva usmerena na nasumicnu direkciju;
					ball.bounce(true);
				}
			}
		}
	}

	check_boundry_hits();
}

void BreakTrough_Logic::Ball_Paddle_Collision_response(BrkTr_Ball& ball)
{
	//	Kada je lopta zalepljen, onda se racuna njena pozicija na pedali i onda se osvezava dokle god je zalepljena.
	if (ball.sticked())
	{
		//	Treba da se izracuna samo jednom.
		if (ball.is_calculated())
		{
			ball.setPosition_on_Paddle(ball.getPosition().x - pPlayer->get_Paddle().getPosition().x);
			ball.set_calculated(true);
		}
		ball.setPosition(sf::Vector2f(pPlayer->get_Paddle().getPosition().x + ball.getPosition_on_Paddle(), pPlayer->get_Paddle().getPosition().y - 2 * mData.get_Component_Sizes(Break::size_Ball).x));
	}

	if (ball.getBounds().intersects(pPlayer->get_Paddle().getBounds()))
	{
		//	Brisem prethodne udarce o zid;
		boundry_hits.clear();

		//	Uzimam vektorsku brzinu.
		sf::Vector2f vel = Ball_velocity_calculation(ball);
		//	Ako je pedala lepljiva, onda moram da izracunam poziciju na pedali i da je osvezavam (gore)
		if (pPlayer->get_Current_Paddle_Type() == Break::Paddle_Sticky)
		{
			//	Ako lopta nije lepljiva, onda treba samo jednom da se izracuna.
			if (!ball.sticked())
			{
				mData.Play_Sound(Break::snd_Paddle_hit);
				ball.setPosition_on_Paddle(ball.getPosition().x - pPlayer->get_Paddle().getPosition().x);
				ball.reset_or_stick_Ball(sf::Vector2f(pPlayer->get_Paddle().getPosition().x + ball.getPosition_on_Paddle(), pPlayer->get_Paddle().getPosition().y - 2 * mData.get_Component_Sizes(Break::size_Ball).x));
				ball.setStored_Velocity(sf::Vector2f(mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.x, mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.y));
			}
		}
		//	Onda samo odbijam loptu koristeci proizvod vektorsku brzine i skalarne brzine.
		if (!ball.sticked())
		{
			mData.Play_Sound(Break::snd_Paddle_hit);
			ball.setVelocity(sf::Vector2f(mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.x, mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.y));
		}
	}
}

void BreakTrough_Logic::PowerUp_Behavior()
{
	//	Proveravam da li pada - u protivnom ce se srusiti program.
	if (pLevel_Manager->does_PowerUp_falls())
	{
		//	Uzimam tip pojacanja.
		Break::PowerUp_ID	ID = pLevel_Manager->get_PowerUp()->pass_ID();
		if (pLevel_Manager->get_PowerUp()->getBounds().intersects(pPlayer->get_Paddle().getBounds()))
		{
			//	Igrac uzima pojacanje
			pPlayer->take_PowerUp(ID);
			//	Kada ga uzme, bice drugacije ponasanje za UI.
			if (ID != Break::pID_Extra_Life && ID != Break::pID_Triple_Ball)
			{
				pUI_Manager->add_PowerUp(ID);
			}
			else if (ID == Break::pID_Extra_Life)
			{
				pUI_Manager->add_life();
			}
			//	Ako je lose pojacanje.
			if (ID == Break::pID_Shrink_Paddle || ID == Break::pID_Fast_Ball)
			{
				Increase_Score(mData.get_Score_increase(Break::score_badpowerup));
			}
			else
			{	//	Povecanje rezultata
				Increase_Score(mData.get_Score_increase(Break::score_large));
			}
			pLevel_Manager->delete_PowerUp();
			mData.Play_Sound(Break::snd_PowerUp_taken);
		}
		//	Ako dodirne dno, brise se.
		else if (!pLevel_Manager->get_PowerUp()->getBounds().intersects(pLevel_Manager->get_Level_Bounds()))
		{
			pLevel_Manager->delete_PowerUp();
		}
	}
}

void BreakTrough_Logic::PowerUp_Creation(sf::FloatRect param)
{
	//	Daje se nasumicnu sansu da se napravi pojacanje.
	if (!pLevel_Manager->does_PowerUp_falls())
	{
		std::uniform_int_distribution<int>	dis(0, 99);
		UINT number = dis(mData.get_Random_Engine());
		//	Ima 20% sanse da se pojavi pojacanje.
		if (number < 20)
		{
			pLevel_Manager->create_PowerUp(param);
		}
	}
}

void BreakTrough_Logic::Laser_Behavior_and_Block_Collision()
{
	//	Mora da postoji prekidac za brisanje - u protivnom moze da se srusi program.
	bool erase_laser = false;
	if (pPlayer->has_fired_check())
	{
		sf::FloatRect laser_bounds = pPlayer->get_Laser()->getBounds();
		sf::FloatRect level_bounds = pLevel_Manager->get_Level_Bounds();
		//	Moram da namestim da laser ne napusta nivo sa strane.
		if ((laser_bounds.left < level_bounds.left) || (laser_bounds.left + laser_bounds.width > level_bounds.left + level_bounds.width))
		{
			pPlayer->get_Laser()->setPosition(pPlayer->get_Paddle().getPosition());
		}
		//	Kada laser napusti nivo, onda se brise.
		if (!laser_bounds.intersects(level_bounds))
		{
			mData.Play_Sound(Break::snd_Wall_hit);
			erase_laser = true;
			pPlayer->delete_Laser();
		}
		//	Laser takodje mora da prodje kroz sve blokove.
		for (UINT i = 0; i < pLevel_Manager->get_Number_of_Total_Blocks(); ++i)
		{
			if (pLevel_Manager->get_Block_Health(i) != 0)	//	Prvo proveravam da li je blok uopste ziv, ako jeste onda proveravamo granice.
			{
				sf::FloatRect bl = pLevel_Manager->get_Block_Bounds(i);
				if (pPlayer->has_fired_check())
				{
					//	Dok listam kod blokova, nije na odmet da pogledam da li ga i laser pogadja
					if (bl.intersects(pPlayer->get_Laser()->getBounds()))
					{
						erase_laser = true;
						Block_hit(i,bl);
						break;
					}
				}
			}
		}

		if (erase_laser)
		{
			pPlayer->delete_Laser();
		}

	}
}

void BreakTrough_Logic::Ball_Lost()
{
	//	Kada lopta dodirne dno:
	if (erase_ball)
	{
		pPlayer->delete_Ball();
		if (pPlayer->get_number_of_Balls() < 1)
		{
			mData.Play_Sound(Break::snd_Player_loose);
			pUI_Manager->remove_life();
			pPlayer->start_Paddle_fade();
			mData.set_Object_Quantities(Break::Number_of_Lives, mData.get_Object_Quantities(Break::Number_of_Lives) - 1);
		}
		erase_ball = false;
	}
}

void BreakTrough_Logic::Ball_Block_Response(BrkTr_Ball& ball, sf::FloatRect bl)
{

	//	Posebna funkcija za odbijanje lopte od bloka ili blokova.
	//	Drugi parametar je granica jednog ili dva bloka.

	sf::FloatRect ball_bounds = ball.getBounds();

	sf::Vector2f bounced_distance = sf::Vector2f(mData.get_Component_Sizes(Break::size_Ball).x / 2, mData.get_Component_Sizes(Break::size_Ball).y / 2);

	//	Pravim okvir za odgovor od bloka.
	sf::FloatRect top_border = sf::FloatRect(bl.left, bl.top, bl.width, 1);
	sf::FloatRect top_intersection;
	sf::FloatRect bottom_border = sf::FloatRect(bl.left, bl.top + bl.height, bl.width, 1);
	sf::FloatRect bottom_intersection;
	sf::FloatRect left_border = sf::FloatRect(bl.left, bl.top, 1, bl.height);
	sf::FloatRect left_intersection;
	sf::FloatRect right_border = sf::FloatRect(bl.left + bl.width, bl.top, 1, bl.height);
	sf::FloatRect right_intersection;

	top_border.intersects(ball_bounds, top_intersection);
	bottom_border.intersects(ball_bounds, bottom_intersection);
	left_border.intersects(ball_bounds, left_intersection);
	right_border.intersects(ball_bounds, right_intersection);

	if (left_intersection.height > top_intersection.width && left_intersection.height > bottom_intersection.width && left_intersection.height != 0)
	{
		//	Lopta dolazi sleva:
		ball.bounce(true);
		ball.move(-bounced_distance.x, 0);
	}
	else if (right_intersection.height > top_intersection.width && right_intersection.height > bottom_intersection.width && right_intersection.height != 0)
	{
		//	Lopta dolazi sdesna:
		ball.bounce(true);
		ball.move(bounced_distance.x, 0);
	}
	else if (top_intersection.width > right_intersection.height && top_intersection.width > left_intersection.height && top_intersection.width != 0)// Poslednji parametar da uzmem sa rezervom.
	{
		//	Lopta dolazi odozgo:
		ball.bounce(false);
		ball.move(0, -bounced_distance.y);
	}
	else if (bottom_intersection.width > right_intersection.height && bottom_intersection.width > left_intersection.height && bottom_intersection.width != 0)
	{
		//	Lopta dolazi odozdo:
		ball.bounce(false);
		ball.move(0, bounced_distance.y);
	}
	else
	{
		//	Da ne zaboravim - sta da se uradi ako lopta ide toliko brzo da udje u blok!
		//	Dodati ovde:


	}
}

void BreakTrough_Logic::Increase_Score(UINT param)
{
	//	Funkcija za povecavanje rezultata.
	//	Uzima trenutan rezultat i povecava ga.
	
	UINT old_score = mData.get_Object_Quantities(Break::Score_Number);
	mData.set_Object_Quantities(Break::Score_Number, old_score + param);
	pUI_Manager->change_score(mData.get_Object_Quantities(Break::Score_Number));

	//	Takodje povecava i drugi rezultat, koji sluzi da se doda zivot kad god predje 1000 poena.
	//	Potom se oduzima sa 1000 i onda jovo nanovo.
	score_buffer += param;
	if (score_buffer >= 1000)
	{
		pUI_Manager->add_life();
		mData.set_Object_Quantities(Break::Number_of_Lives, mData.get_Object_Quantities(Break::Number_of_Lives) + 1);
		mData.Play_Sound(Break::snd_PowerUp_taken);
		score_buffer -= 1000;
	}

}

void BreakTrough_Logic::Reset_Block_animations()
{
	//	Resetujem animacije
	for (UINT i = 0; i < pLevel_Manager->get_Number_of_Total_Blocks(); ++i)
	{
		//	Prvo proveravam da li je blok uopste ziv, ako nije, onda ga preskacemo.
		if (pLevel_Manager->get_Block_Health(i) != 0)	
		{
			if (pLevel_Manager->get_Block_ID(i) == Break::bID_Grey || pLevel_Manager->get_Block_ID(i) == Break::bID_Gold)
			{
				//	Resetujemo animacije
				pLevel_Manager->reset_Block_Texture_coordinates(i, pLevel_Manager->get_Block_ID(i));
			}
		}
	}
}

void BreakTrough_Logic::Block_hit(UINT indice, sf::FloatRect bl_bound)
{
	mData.Play_Sound(Break::snd_Block_hit);
	//	Proveravam da li su blokovi "specijalni"
	if (pLevel_Manager->get_Block_ID(indice) == Break::bID_Grey || pLevel_Manager->get_Block_ID(indice) == Break::bID_Gold)
	{
		//	Ako jesu, da se izvede animacija udarca.
		pLevel_Manager->animate_Block_hit(indice, pLevel_Manager->get_Block_ID(indice));
	}
	if (pLevel_Manager->get_Block_Health(indice) > 0)
	{
		//	Smanjujem zdravlje bloka, potom proveravam da li je na nuli - ako jeste, onda ga brisem.
		pLevel_Manager->decrease_Block_Health(indice);
		if (pLevel_Manager->get_Block_Health(indice) == 0)
		{
			pLevel_Manager->delete_Block(indice);
			//	Pozivam funkciju za pojacanje.
			PowerUp_Creation(bl_bound);
			//	Povecavam rezultat;
			if (pLevel_Manager->get_Block_ID(indice) == Break::bID_Grey)
			{
				Increase_Score(mData.get_Score_increase(Break::score_medium));
			}
			else
			{
				Increase_Score(mData.get_Score_increase(Break::score_small));
			}

		}
	}
}

