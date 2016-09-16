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

	Paddle_Movement_restriction();

	for (auto& it : pPlayer->get_Balls())
	{
		Ball_Paddle_Collision_response(it);

		Ball_Block_Collision_response(it);

		Ball_Level_Collision_response(it);
	}

	PowerUp_Behavior();	

	Laser_Behavior_and_Block_Collision();

	Ball_Lost();
}

void BreakTrough_Logic::Paddle_Movement_restriction()
{
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
	//	Angle calculation - it is dependant on a place the ball hits the paddle:

	sf::Vector2f vel;
	float angle, x, y;
	float relative_intersect = (pPlayer->get_Paddle().getBounds().left + (pPlayer->get_Paddle().getBounds().width / 2)) - param.getPosition().x;
	float normalised_relative_intersection = relative_intersect / (pPlayer->get_Paddle().getBounds().width / 2);
	angle = normalised_relative_intersection * 60;
	// 	Angle needs to be increased by 270 degrees, for the ball to go upwards!
	angle += 270;
	angle = static_cast<float>(angle*(3.14 / 180));
	param.setAngle(angle);
	x = -cos(angle);
	y = sin(angle);

	return vel = sf::Vector2f(x, y);
}

void BreakTrough_Logic::Ball_Random_direction_launch(bool is_left_boundry, BrkTr_Ball& ball)
{
	//	This function is called when the ball hits the level's bounds third time which the same vertical distance; 
	//	It prevents the ball to constantly bounce horizontaly between walls.
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
		//	First I check whether the block is alive.
		if (pLevel_Manager->get_Block_Health(i) != 0)	
		{
			sf::FloatRect bl = pLevel_Manager->get_Block_Bounds(i);

			if (bl.intersects(ball_bounds))
			{
				//	If the ball hit the block, I put the block bounds in a seperate container -  this is 
				//	crucial if the ball hitted more than one block;
				collided_bl_bounds.insert(std::pair<UINT, sf::FloatRect>(i,bl));
			}
		}
	}
	//	Response
	if (!collided_bl_bounds.empty())
	{
		//	First I check if there is more than one block collision:
		if (collided_bl_bounds.size() > 1)
		{
			//	Then I check which collision has greater scalar value.
			//	When I find it, the progam will register that the "ball hitted him".
			//	But the response on the ball will be different.
			
			//	First, I need to calculate the area of intersection.
			std::map<UINT, sf::FloatRect> intersections;
			for (std::map<UINT, sf::FloatRect>::iterator it = collided_bl_bounds.begin(); it != collided_bl_bounds.end(); ++it)
			{
				sf::FloatRect intrs;
				it->second.intersects(ball_bounds, intrs);
				intersections.insert(std::pair<UINT, sf::FloatRect>(it->first, intrs));
			}

			//	Then I determine which one is greater - "the alpha block" - the ball will hit him.
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

			//	I put the second intersection as - "beta block". The ball will not destroy him, but I will
			//	use it's bounds to make a response to the ball.
			UINT beta_indice;
			for (std::map<UINT, sf::FloatRect>::iterator it = collided_bl_bounds.begin(); it != collided_bl_bounds.end(); ++it)
			{
				if (it->first != alpha_indice)
				{
					beta_indice = it->first;
				}
			}

			//	The final bound - ut is the combination of the two blocks that the ball has hitted.
			//	Shape (is it the horizontal or vertical rectangle) depends on the position of the "beta" block.
			sf::FloatRect final_rect;

			//	if they are next to each other from left or right:
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
			//	if they are next to each other from up or down:
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

			//	Finally, the response:
			Ball_Block_Response(ball, final_rect);
			Block_hit(alpha_indice, final_rect);
			boundry_hits.clear();
		}
		else
		{
			//	If there is only a collision with one block, then it is simple:
			std::map<UINT, sf::FloatRect>::iterator it = collided_bl_bounds.begin();
			Ball_Block_Response(ball, it->second);
			Block_hit(it->first, it->second);
			boundry_hits.clear();
		}
	}

}

void BreakTrough_Logic::Ball_Level_Collision_response(BrkTr_Ball& ball)
{
	sf::FloatRect ball_bounds = ball.getBounds();
	sf::FloatRect level_bounds = pLevel_Manager->get_Level_Bounds();

	// 	Ball is deleted here when it reaches the bottom.
	if (ball_bounds.top + ball_bounds.height > level_bounds.top + level_bounds.height)
	{
		ball.set_delete(true);
		boundry_hits.clear();	 
		erase_ball = true;
	}
	//	Ball will bounce from top border only when her vector speed is lower that the top of the level bounds.
	else if (ball_bounds.top < level_bounds.top)
	{
		if (ball.getVelocity().y < 0)
		{
			mData.Play_Sound(Break::snd_Wall_hit);
			ball.bounce(false);
			boundry_hits.clear();	
		}
	}
	
	//	Checking whether the ball has hit the left side of the level.
	for (const auto& it : pLevel_Manager->get_Left_Boundries())
	{
		if (it.second.intersects(ball_bounds))
		{
			if (boundry_hits.size() >= 3)
			{
				Ball_Random_direction_launch(true, ball);
				boundry_hits.clear();
			}
			else
			{
				if (ball.getVelocity().x < 0)
				{
					mData.Play_Sound(Break::snd_Wall_hit);
					boundry_hits.push_back(it.first);	//	Adds the type of boundry that is hit;
										//	When the ball hits three times the boundry of the same type, 
										//	the ball is given a radnom dierction;
					ball.bounce(true);
				}
			}
		}
	}

	//	Checking whether the ball has hit the right side of the level.
	for (const auto& it : pLevel_Manager->get_Right_Boundries())
	{
		if (it.second.intersects(ball_bounds))
		{
			if (boundry_hits.size() >= 3)
			{
				Ball_Random_direction_launch(false, ball);
				boundry_hits.clear();
			}
			else
			{
				if (ball.getVelocity().x > 0)
				{
					mData.Play_Sound(Break::snd_Wall_hit);
					boundry_hits.push_back(it.first);	//	Adds the type of boundry that is hit;
										//	When the ball hits three times the boundry of the same type, 
										//	the ball is given a radnom dierction;
					ball.bounce(true);
				}
			}
		}
	}

	check_boundry_hits();
}

void BreakTrough_Logic::Ball_Paddle_Collision_response(BrkTr_Ball& ball)
{
	//	When ball is glued, the it is calculated it's position on the paddle and refreshed as long is on a paddle.
	if (ball.sticked())
	{
		//	Needs to be calculated only once.
		if (ball.is_calculated())
		{
			ball.setPosition_on_Paddle(ball.getPosition().x - pPlayer->get_Paddle().getPosition().x);
			ball.set_calculated(true);
		}
		ball.setPosition(sf::Vector2f(pPlayer->get_Paddle().getPosition().x + ball.getPosition_on_Paddle(), pPlayer->get_Paddle().getPosition().y - 2 * mData.get_Component_Sizes(Break::size_Ball).x));
	}

	if (ball.getBounds().intersects(pPlayer->get_Paddle().getBounds()))
	{
		boundry_hits.clear();
		sf::Vector2f vel = Ball_velocity_calculation(ball);

		if (pPlayer->get_Current_Paddle_Type() == Break::Paddle_Sticky)
		{
			//	When ball launches from a sticky paddle.
			if (!ball.sticked())
			{
				mData.Play_Sound(Break::snd_Paddle_hit);
				ball.setPosition_on_Paddle(ball.getPosition().x - pPlayer->get_Paddle().getPosition().x);
				ball.reset_or_stick_Ball(sf::Vector2f(pPlayer->get_Paddle().getPosition().x + ball.getPosition_on_Paddle(), pPlayer->get_Paddle().getPosition().y - 2 * mData.get_Component_Sizes(Break::size_Ball).x));
				ball.setStored_Velocity(sf::Vector2f(mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.x, mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.y));
			}
		}
		//	Normal bounce
		if (!ball.sticked())
		{
			mData.Play_Sound(Break::snd_Paddle_hit);
			ball.setVelocity(sf::Vector2f(mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.x, mData.get_Speed(pPlayer->get_Current_Ball_Speed())*vel.y));
		}
	}
}

void BreakTrough_Logic::PowerUp_Behavior()
{

	if (pLevel_Manager->does_PowerUp_falls())
	{
		//	Taking the type of powerup.
		Break::PowerUp_ID	ID = pLevel_Manager->get_PowerUp()->pass_ID();
		if (pLevel_Manager->get_PowerUp()->getBounds().intersects(pPlayer->get_Paddle().getBounds()))
		{
			pPlayer->take_PowerUp(ID);
			//	When player takes the power up, theese will have different behavior for the UI than "standard" power ups.
			if (ID != Break::pID_Extra_Life && ID != Break::pID_Triple_Ball)
			{
				pUI_Manager->add_PowerUp(ID);
			}
			else if (ID == Break::pID_Extra_Life)
			{
				pUI_Manager->add_life();
			}
			//	When the power up is bad, apply negative efefcts, but give player bigger score
			if (ID == Break::pID_Shrink_Paddle || ID == Break::pID_Fast_Ball)
			{
				Increase_Score(mData.get_Score_increase(Break::score_badpowerup));
			}
			else
			{	//	otherwise, give player normal score
				Increase_Score(mData.get_Score_increase(Break::score_large));
			}
			pLevel_Manager->delete_PowerUp();
			mData.Play_Sound(Break::snd_PowerUp_taken);
		}
		//	if it reaches the bottom the power up is deleted;
		else if (!pLevel_Manager->get_PowerUp()->getBounds().intersects(pLevel_Manager->get_Level_Bounds()))
		{
			pLevel_Manager->delete_PowerUp();
		}
	}
}

void BreakTrough_Logic::PowerUp_Creation(sf::FloatRect param)
{
	//	It gives the random chance to create power up - about 20% chance
	if (!pLevel_Manager->does_PowerUp_falls())
	{
		std::uniform_int_distribution<int>	dis(0, 99);
		UINT number = dis(mData.get_Random_Engine());
		if (number < 20)
		{
			pLevel_Manager->create_PowerUp(param);
		}
	}
}

void BreakTrough_Logic::Laser_Behavior_and_Block_Collision()
{
	//	There has to be a bool for laser erasion, otherwise the program will crash.
	bool erase_laser = false;
	if (pPlayer->has_fired_check())
	{
		sf::FloatRect laser_bounds = pPlayer->get_Laser()->getBounds();
		sf::FloatRect level_bounds = pLevel_Manager->get_Level_Bounds();
		//	Laser must not cross the left or right border of the level
		if ((laser_bounds.left < level_bounds.left) || (laser_bounds.left + laser_bounds.width > level_bounds.left + level_bounds.width))
		{
			pPlayer->get_Laser()->setPosition(pPlayer->get_Paddle().getPosition());
		}
		//	Laser is delelted when it leaves the level bounds.
		if (!laser_bounds.intersects(level_bounds))
		{
			mData.Play_Sound(Break::snd_Wall_hit);
			erase_laser = true;
			pPlayer->delete_Laser();
		}
		//	Laser is also deleted when it hits the block
		for (UINT i = 0; i < pLevel_Manager->get_Number_of_Total_Blocks(); ++i)
		{
			if (pLevel_Manager->get_Block_Health(i) != 0)	//	Checking is the block alive.
			{
				sf::FloatRect bl = pLevel_Manager->get_Block_Bounds(i);
				if (pPlayer->has_fired_check())
				{
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
	//	Special function for ball response to one or two blocks.
	//	Second parameter is the bounds of one or both blocks.

	sf::FloatRect ball_bounds = ball.getBounds();

	sf::Vector2f bounced_distance = sf::Vector2f(mData.get_Component_Sizes(Break::size_Ball).x / 2, mData.get_Component_Sizes(Break::size_Ball).y / 2);

	//	Making the bounds for response from the block(s).
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
		//	Ball comes from left:
		ball.bounce(true);
		ball.move(-bounced_distance.x, 0);
	}
	else if (right_intersection.height > top_intersection.width && right_intersection.height > bottom_intersection.width && right_intersection.height != 0)
	{
		//	Ball comes from right:
		ball.bounce(true);
		ball.move(bounced_distance.x, 0);
	}
	else if (top_intersection.width > right_intersection.height && top_intersection.width > left_intersection.height && top_intersection.width != 0)
	{
		//	Ball comes from up:
		ball.bounce(false);
		ball.move(0, -bounced_distance.y);
	}
	else if (bottom_intersection.width > right_intersection.height && bottom_intersection.width > left_intersection.height && bottom_intersection.width != 0)
	{
		//	Ball comes from bellow:
		ball.bounce(false);
		ball.move(0, bounced_distance.y);
	}

}

void BreakTrough_Logic::Increase_Score(UINT param)
{
	//	Function for score increase.
	//	Takes the current score and increases it.
	
	UINT old_score = mData.get_Object_Quantities(Break::Score_Number);
	mData.set_Object_Quantities(Break::Score_Number, old_score + param);
	pUI_Manager->change_score(mData.get_Object_Quantities(Break::Score_Number));

	//	Also it increases the score buffer, which is used to give a life to the player when it reaches 1000 points.
	//	Then it is substracted with 1000 and rinse and repeat.
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
	for (UINT i = 0; i < pLevel_Manager->get_Number_of_Total_Blocks(); ++i)
	{
		if (pLevel_Manager->get_Block_Health(i) != 0)	
		{
			if (pLevel_Manager->get_Block_ID(i) == Break::bID_Grey || pLevel_Manager->get_Block_ID(i) == Break::bID_Gold)
			{
				pLevel_Manager->reset_Block_Texture_coordinates(i, pLevel_Manager->get_Block_ID(i));
			}
		}
	}
}

void BreakTrough_Logic::Block_hit(UINT indice, sf::FloatRect bl_bound)
{
	mData.Play_Sound(Break::snd_Block_hit);
	//	Checking whether the blocks are special
	if (pLevel_Manager->get_Block_ID(indice) == Break::bID_Grey || pLevel_Manager->get_Block_ID(indice) == Break::bID_Gold)
	{
		//	If so, then it needs to call a hit animation.
		pLevel_Manager->animate_Block_hit(indice, pLevel_Manager->get_Block_ID(indice));
	}
	if (pLevel_Manager->get_Block_Health(indice) > 0)
	{
		//	Decreasing the health of a block - if it hits zero, then I delete the block.
		pLevel_Manager->decrease_Block_Health(indice);
		if (pLevel_Manager->get_Block_Health(indice) == 0)
		{
			pLevel_Manager->delete_Block(indice);
			//	Calling the power up creation function;
			PowerUp_Creation(bl_bound);
			//	Score increase function;
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

