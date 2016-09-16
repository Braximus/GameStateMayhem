#ifndef COMETWARS_LOGIC_H
#define COMETWARS_LOGIC_H

#include "Comet Wars Game Objects.h"
#include "Comet Wars Data.h"
#include "Comet Wars Enumerations.h"

class CometWars_UI_Manager;
class CometWars_Player;
class Comet_Manager;

class CometWarsLogic
{
	CometWarsData&			mData;
	CometWars_UI_Manager*	pUI_Manager;
	CometWars_Player*		pPlayer;
	Comet_Manager*			pComet_Manager;
	//	Collisions:
	void				Collision_Object_Border_Check();
	void				Collision_Player_Check();
	//	Operations:
	void				Calculate_position(CW::Zones zone, sf::Vector2f& position);
	void				Asteroid_Ship_Response();
	void				Asteroid_Damage_Response(UINT param);
	void				Big_Comet_Destroyed_Response(UINT param);
	void				Comet_Border_Response(UINT param, CW::Zones zone);
	void				Player_Border_Response(CW::Zones zone);
public:
	explicit			CometWarsLogic(CometWarsData& data, CometWars_UI_Manager* pUI, CometWars_Player* pPlay, Comet_Manager* pComets);
	void				LogicFunction();
};
#endif
