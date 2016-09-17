#include "stdafx.h"
#include "Quata SubSt End.h"
#include "Quata Data.h"
#include "Quata UI Manager.h"

QuataEndSubState::QuataEndSubState(QuataData& data, Quata_UI_Manager* UI)
	:mData(data)
	, pUI(UI)
{
	is_created = false;	
}

void QuataEndSubState::update_SubState(sf::Time& time)
{
	if (!is_created)
	{
		if (mData.victory())
		{
			pUI->create_SplashScreen(mData.get_Text(Qua::txt_Win));
		}
		else
		{
			pUI->create_SplashScreen(mData.get_Text(Qua::txt_Loose));
		}
		is_created = true;
	}
}

void QuataEndSubState::handle_Events(sf::Event& param)
{
	if (param.type == sf::Event::KeyPressed)
	{
		if (param.key.code == sf::Keyboard::Return)
		{
			mData.Exit();
		}
	}
	if (param.type == sf::Event::MouseButtonPressed)
	{
		if (param.mouseButton.button == sf::Mouse::Left)
		{
			mData.Exit();
		}
	}
}

void QuataEndSubState::handle_Realtime_Input()
{
	//
}
