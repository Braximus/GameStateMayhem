#include "stdafx.h"
#include "Comet Wars SubSt Play.h"
#include "Comet Wars Data.h"
#include "Comet Wars Player.h"
#include "Comet Manager.h"
#include "Comet Wars UI Manager.h"
#include "Comet Wars Logic.h"
#include "Comet Wars Decorations Manager.h"
#include "Debug.h"


CometWars_SubState_Play::CometWars_SubState_Play(CometWarsData& data, CometWars_Player* player, Comet_Manager* c_manager, CometWars_UI_Manager* ui_manager, CometWarsLogic* logic, CometWars_Deco_Manager* deco)
	:mData(data)
	, pPlayer(player)
	, pCometManager(c_manager)
	, pUImanager(ui_manager)
	, pLogic(logic)
	, pDecoManager(deco)
{

};


void CometWars_SubState_Play::update_Substate(sf::Time& time)
{
	pLogic->LogicFunction();
	pDecoManager->update(time);
	pPlayer->update(time);
	pCometManager->update(time);
	pUImanager->update(time);
}

void CometWars_SubState_Play::handle_Events(sf::Event& mEvent)
{
	if (mEvent.type == sf::Event::KeyPressed)
	{
		if (mEvent.key.code == sf::Keyboard::Escape)
		{
			mData.ChangeSubState(CW::sub_Pause);
			pUImanager->create_Pause();
		}
	}
}

void CometWars_SubState_Play::handle_RealTimeInput()
{
	pPlayer->handle_ship_movement();
}
