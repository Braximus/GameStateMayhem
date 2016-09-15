#ifndef COMETWARS_SUBSTATE_START_H
#define COMETWARS_SUBSTATE_START_H

#include "Comet Wars SubStates BaseClass.h"
#include "Comet Wars Data.h"
#include "Comet Wars Game Objects.h"
#include "Comet Wars UI Objects.h"

class CometWars_UI_Manager;
class CometWars_Deco_Manager;
class CometWars_SubState_Start : public CometWarsSubStates
{
	CometWarsData&					mData;
	CometWars_UI_Manager*			pUImanager;
	CometWars_Deco_Manager*			pDecoManager;
public:
	explicit			CometWars_SubState_Start(CometWarsData& data, CometWars_UI_Manager* ui_man, CometWars_Deco_Manager* deco_man);
	void				update_Substate(sf::Time&);
	void				handle_Events(sf::Event&);
	void				handle_RealTimeInput();
};


#endif 
