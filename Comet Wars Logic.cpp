#include "stdafx.h"
#include "Comet Wars Logic.h"
#include "Debug.h"
#include "Comet Wars Player.h"
#include "Comet Manager.h"
#include "Comet Wars UI Manager.h"


CometWarsLogic::CometWarsLogic(CometWarsData& data, CometWars_UI_Manager* pUI, CometWars_Player* pPlay, Comet_Manager* pComets)
	: mData(data)
{
	pUI_Manager = pUI;
	pPlayer = pPlay;
	pComet_Manager = pComets;
}

void CometWarsLogic::LogicFunction()
{

	DebugClass::top = false;
	DebugClass::left = false;
	DebugClass::right = false;
	DebugClass::bottom = false;

	//	Sudari Objekata sa granice nivoa;
	Collision_Object_Border_Check();
	//	Sudari Igraca sa Kometama granicom nivoa;
	Collision_Player_Check();
}

void CometWarsLogic::Calculate_position(CW::Zones zone, sf::Vector2f& position)
{
	if (zone == CW::z_Top)
	{
		position.y = mData.getKey_Position(CW::kp_BottomLeft).y - mData.getObj_Sizes(CW::size_UI_Area).y - mData.getDistance(CW::dis_Near);
		DebugClass::top = true;
	}
	else if (zone == CW::z_Left)
	{
		position.x = mData.getKey_Position(CW::kp_TopRight).x - mData.getDistance(CW::dis_Near);
		DebugClass::left = true;
	}
	else if (zone == CW::z_Right)
	{
		position.x = mData.getDistance(CW::dis_Near);
		DebugClass::right = true;
	}
	else if (zone == CW::z_Bottom)
	{
		position.y = mData.getDistance(CW::dis_Near);
		DebugClass::bottom = true;
	}
}

void CometWarsLogic::Asteroid_Ship_Response()
{	
	// Da ga ne aktivira kada je umro... kasnije cu da namestim da u potpunosti izbrise brod!
	if (mData.getCurrentSubState() != CW::sub_End)
	{
		if (!pPlayer->getIs_shield_on())
		{
			mData.remove_life();
			pUI_Manager->delete_life();
			if (mData.getNumber_of_Lives() > 0)
			{
				mData.Play_Sound(CW::snd_Hit);
				mData.Play_Sound(CW::snd_PlayerShieldUp);
				pPlayer->activate_shield();
			}
			else
			{
				pPlayer->destroy_ship();
				mData.Play_Sound(CW::snd_PlayerShipDestroyed);
			}
		}
	}
}

void CometWarsLogic::Asteroid_Damage_Response(UINT param)
{
	mData.Play_Sound(CW::snd_Hit);
	if (pComet_Manager->damage_comet(param) == CW::Dead && !pComet_Manager->isMini_Comet(param))
	{
		Big_Comet_Destroyed_Response(param);
	}
	else if (pComet_Manager->isMini_Comet(param))
	{
		mData.change_Score(1);
		pUI_Manager->refresh_score();
	}
	mData.setNumber_of_Comets(pComet_Manager->getNumber_of_comets());
}

void CometWarsLogic::Big_Comet_Destroyed_Response(UINT param)
{
	sf::Vector2f big_comet_pos = pComet_Manager->getComet_Position(param);

	UINT new_number_of_comets = mData.getNumber_of_Comets();
	--new_number_of_comets;
	mData.Play_Sound(CW::snd_CometBigDead);
	mData.change_Score(5);
	pUI_Manager->refresh_score();
	//	Sada pravimo male asteroide ovde :)
	std::uniform_int_distribution<int>		distributor(3, 7);
	UINT random_number = distributor(mData.get_random_engine());

	for (UINT i = 0; i <= random_number; ++i)
	{
		pComet_Manager->create_comet(true);
		pComet_Manager->setComet_Position(pComet_Manager->getNumber_of_comets() - 1, big_comet_pos);
		//	Trebalo bi da napravi 3 do 7 manjih kometa na mestu umrle velike komete.
	}
}

void CometWarsLogic::Collision_Object_Border_Check()
{
	for (auto& j : mData.getZone_map())
	{
		for (UINT i = 0; i < pComet_Manager->getNumber_of_comets(); ++i)
		{
			if (j.second.contains(pComet_Manager->getComet_Position(i)))
			{
				Comet_Border_Response(i, j.first);
			}
		}
		if (j.second.contains(pPlayer->getShip_Position()))
		{
			Player_Border_Response(j.first);
		}
		for (UINT i = 0; i < pPlayer->getNumber_of_projectiles(); ++i)
		{
			if (pPlayer->getProjectile_Bounds(i).intersects(j.second))
			{
				pPlayer->mark_projectile_for_deletion(i);
			}
		}	
	}
}

void CometWarsLogic::Collision_Player_Check()
{
	for (UINT i = 0; i < pComet_Manager->getNumber_of_comets(); ++i)
	{
		if (pComet_Manager->getComet_Bounds(i).intersects(pPlayer->getShip_Bounds()))
		{
			Asteroid_Ship_Response();
		}
		for (UINT j = 0; j < pPlayer->getNumber_of_projectiles(); ++j)
		{
			if (pComet_Manager->getComet_Bounds(i).intersects(pPlayer->getProjectile_Bounds(j)))
			{
				pPlayer->mark_projectile_for_deletion(j);
				Asteroid_Damage_Response(i);
				break;
			}
		}
	}
}

void CometWarsLogic::Comet_Border_Response(UINT param, CW::Zones zone)
{
	sf::Vector2f new_pos = pComet_Manager->getComet_Position(param);
	Calculate_position(zone, new_pos);
	pComet_Manager->setComet_Position(param, new_pos);
}

void CometWarsLogic::Player_Border_Response(CW::Zones zone)
{
	sf::Vector2f new_pos = pPlayer->getShip_Position();
	Calculate_position(zone, new_pos);
	pPlayer->setShip_Position(new_pos);
}