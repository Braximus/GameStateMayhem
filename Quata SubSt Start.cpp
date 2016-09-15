#include "stdafx.h"
#include "Quata SubSt Start.h"
#include "Quata Data.h"
#include "Quata Level.h"
#include "Quata Player.h"
#include "Quata AI.h"
#include "Quata UI Manager.h"

QuataStartSubState::QuataStartSubState(QuataData& data, Quata_Player* player, QuataAI* ai, Quata_Level* level, Quata_UI_Manager* UI)
	: mData(data)
	, pPlayer(player)
	, pAI(ai)
	, pLevel(level)
	, pUI(UI)
{
	initialised = false;	
}

void QuataStartSubState::update_SubState(sf::Time&)
{
	if (!initialised)
	{
		pUI->create_SplashScreen(mData.get_Text(Qua::txt_Start));
		pPlayer->reset_Paddle_position();
		pAI->reset_Paddle_Position();
		pLevel->reset_ball();
		initialised = true;
	}
}

void QuataStartSubState::handle_Events(sf::Event& param)
{
	if (param.type == sf::Event::KeyPressed)
	{
		if (param.key.code == sf::Keyboard::Return)
		{
			mData.changeSubState(Qua::Play);
			reset_init();
			pLevel->start_ball();
		}
	}
}

void QuataStartSubState::handle_Realtime_Input()
{
	//
}

void QuataStartSubState::reset_init()
{
	initialised = false;
	pUI->delete_SplashScreen();
}