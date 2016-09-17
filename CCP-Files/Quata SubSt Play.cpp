#include "stdafx.h"
#include "Quata SubSt Play.h"
#include "Quata Data.h"
#include "Quata AI.h"
#include "Quata Logic.h"
#include "Quata Player.h"
#include "Quata Level.h"
#include "Quata UI Manager.h"

QuataPlaySubState::QuataPlaySubState(QuataData& data, Quata_Player* player, QuataAI* ai, Quata_Level* level, Quata_UI_Manager* UI)
	:mData(data)
	, mLogic(data)
	, pAI(ai)
	, pPlayer(player)
	, pLevel(level)
	, pUI(UI)
{
	mLogic.get_pointers(pPlayer, pAI, pLevel, pUI);
}

void QuataPlaySubState::update_SubState(sf::Time& time)
{
	AI_turn(time);
	pAI->update(time);
	pPlayer->update(time);
	pLevel->update(time);
	mLogic.LogicFunction();
}

void QuataPlaySubState::handle_Events(sf::Event& param)
{
	if (param.type == sf::Event::KeyPressed)
	{
		if (param.key.code == sf::Keyboard::Escape)
		{
			pUI->create_Pause();
			mData.changeSubState(Qua::Pause);
		}
	}
}

void QuataPlaySubState::handle_Realtime_Input()
{
	sf::FloatRect border_paddle = pPlayer->get_Paddle_Bounds();
	sf::FloatRect border_upper_pf = mData.get_Zone(Qua::z_UpperPlayField);
	sf::FloatRect border_bottom_pf = mData.get_Zone(Qua::z_BottomPlayField);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!border_upper_pf.intersects(border_paddle))
		{
			pPlayer->move_Paddle(true);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!border_bottom_pf.intersects(border_paddle))
		{
			pPlayer->move_Paddle(false);
		}
	}
}

void QuataPlaySubState::AI_turn(sf::Time& time)
{
	bool upper_border_collision = false;
	bool bottom_border_collision = false;

	sf::FloatRect border_paddle = pAI->get_Paddle_Bounds();
	sf::FloatRect border_upper_pf = mData.get_Zone(Qua::z_UpperPlayField);
	sf::FloatRect border_bottom_pf = mData.get_Zone(Qua::z_BottomPlayField);

	if (border_upper_pf.intersects(border_paddle))
	{
		upper_border_collision = true;
	}
	else if (border_bottom_pf.intersects(border_paddle))
	{
		bottom_border_collision = true;
	}
	pAI->move_Paddle(pLevel->get_Ball_Position(), upper_border_collision, bottom_border_collision);
}
