#include "stdafx.h"
#include "BreakTrough Pause SubState.h"
#include "BreakTrough Data.h"
#include "BreakTrough UI Manager.h"

BrkTr_SubSt_Pause::BrkTr_SubSt_Pause(BreakTrough_Data& data, BreakTrough_UI_Manager* pUI)
	:mData(data)
{
	block = false;
	pUI_Manager = pUI;
}

void BrkTr_SubSt_Pause::update_Substate(sf::Time& time)
{
	if (pUI_Manager->is_mouse_hovering_in_pause_menu())
	{
		if (!block)
		{
			mData.Play_Sound(Break::snd_Hover);
			block = true;
		}
	}
	else
	{
		block = false;
	}
}

void BrkTr_SubSt_Pause::handle_Events(sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
		{
			pUI_Manager->show_or_hide_Pause(false);
			mData.Change_SubState(Break::SubSt_Play);
			mData.Play_Sound(Break::snd_Escape);
		}
	}
	else if (Event.type == sf::Event::MouseButtonPressed)
	{
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			mData.Play_Sound(Break::snd_Select);
		}
	}
	else if (Event.type == sf::Event::MouseButtonReleased)
	{
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (pUI_Manager->Pause_response() == Break::Continue)
			{
				pUI_Manager->show_or_hide_Pause(false);
				mData.Change_SubState(Break::SubSt_Play);
				
			}
			else if (pUI_Manager->Pause_response() == Break::Exit)
			{
				mData.Exit();
			}
		}
	}
		
}

void BrkTr_SubSt_Pause::handle_RealTimeInput()
{
	pUI_Manager->interact_pause(static_cast<sf::Vector2f>(mData.get_Mouse_Coordinates()));

}
