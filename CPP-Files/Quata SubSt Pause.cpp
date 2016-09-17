#include "stdafx.h"
#include "Quata SubSt Pause.h"
#include "Quata Data.h"
#include "Quata UI Manager.h"

QuataPauseSubState::QuataPauseSubState(QuataData& data, Quata_UI_Manager* UI)
	:mData(data)
	, pUI(UI)
{
	sound_block = false;
}

void QuataPauseSubState::update_SubState(sf::Time& time)
{
	if (pUI->is_mouse_hovering_in_pause())
	{
		if (!sound_block)
		{
			mData.Play_Sound(Qua::snd_Hover);
			sound_block = true;
		}
	}
	else
	{
		sound_block = false;
	}
}

void QuataPauseSubState::handle_Events(sf::Event& param)
{
	if (param.type == sf::Event::KeyPressed)
	{
		if (param.key.code == sf::Keyboard::Escape)
		{
			pUI->delete_Pause();
			mData.changeSubState(Qua::Play);
			mData.Play_Sound(Qua::snd_Escape);
		}
	}
	else if (param.type == sf::Event::MouseButtonPressed)
	{
		if (param.mouseButton.button == sf::Mouse::Left)
		{
			mData.Play_Sound(Qua::snd_Select);
		}
	}
	else if (param.type == sf::Event::MouseButtonReleased)
	{
		if (param.mouseButton.button == sf::Mouse::Left)
		{
			Qua::Button_Selection sel = pUI->pause_response();
			if (sel == Qua::Continue)
			{
				pUI->delete_Pause();
				mData.changeSubState(Qua::Play);				
			}
			else if (sel == Qua::Exit)
			{
				pUI->delete_Pause();
				mData.Exit();
			}
			else if (sel == Qua::New)
			{ 
				pUI->delete_Pause();
				mData.set_Score(Qua::cu_Score1, 0);
				pUI->change_score(Qua::cu_Score1);
				mData.set_Score(Qua::cu_Score2, 0);
				pUI->change_score(Qua::cu_Score2);
				mData.changeSubState(Qua::Start);
			}
		}
	}
}

void QuataPauseSubState::handle_Realtime_Input()
{
	pUI->pause_interact(mData.get_Mouse_Coordinates());
}

