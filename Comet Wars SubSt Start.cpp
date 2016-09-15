#include "stdafx.h"
#include "Comet Wars SubSt Start.h"
#include "Comet Wars UI Manager.h"
#include "Comet Wars Decorations Manager.h"


CometWars_SubState_Start::CometWars_SubState_Start(CometWarsData& data, CometWars_UI_Manager* ui_man, CometWars_Deco_Manager* deco_man)
	:mData(data)
	, pUImanager(ui_man)
	, pDecoManager(deco_man)
{
	pUImanager->create_CountDown();
}

void CometWars_SubState_Start::update_Substate(sf::Time& time)
{
	if (pUImanager->getCountDown_time() <= 1.1)
	{
		pUImanager->delete_CountDown();
		mData.ChangeSubState(CW::sub_Play);
	}
	pUImanager->update(time);
	pDecoManager->update(time);
}

void CometWars_SubState_Start::handle_Events(sf::Event& mEvent)
{
	if (mEvent.type == sf::Event::KeyPressed)
	{
		if (mEvent.key.code == sf::Keyboard::Escape)
		{
			mData.Exit();
		}
	}
}

void CometWars_SubState_Start::handle_RealTimeInput()
{
	//
}