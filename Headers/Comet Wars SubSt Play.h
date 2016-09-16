#ifndef COMETWARS_SUBSTATE_PLAY_H
#define COMETWARS_SUBSTATE_PLAY_H

#include "Comet Wars SubStates BaseClass.h"
#include "Comet Wars UI Objects.h"
#include "Comet Wars Game Objects.h"

class CometWars_Player;
class Comet_Manager;
class CometWars_UI_Manager;
class CometWarsData;
class CometWarsLogic;
class CometWars_Deco_Manager;

class CometWars_SubState_Play : public CometWarsSubStates
{
	CometWarsData&					mData;
	CometWars_Player*				pPlayer;
	Comet_Manager*					pCometManager;
	CometWars_UI_Manager*			pUImanager;
	CometWarsLogic*					pLogic;
	CometWars_Deco_Manager*			pDecoManager;
public:
	explicit		CometWars_SubState_Play(CometWarsData& data, CometWars_Player* player, Comet_Manager* manager, CometWars_UI_Manager* ui_manager, CometWarsLogic* logic, CometWars_Deco_Manager* deco);

	void	update_Substate(sf::Time&);				
	void	handle_Events(sf::Event& );
	void	handle_RealTimeInput();
};
#endif 
