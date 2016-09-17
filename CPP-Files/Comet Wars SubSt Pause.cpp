#include "stdafx.h"
#include "Comet Wars SubSt Pause.h"
#include "Comet Wars UI Manager.h"
#include "Comet Wars Game.h"

CometWars_SubState_Pause::CometWars_SubState_Pause(CometWarsData& data, CometWars_UI_Manager* ui, CometWarsGame* g)
	:mData(data)
	, pUI_Manager(ui)
	, game(g)
{
	sound_block = false;
}

void CometWars_SubState_Pause::update_Substate(sf::Time& time)
{
	if (pUI_Manager->is_mouse_hovering_in_Pause())
	{
		if (!sound_block)
		{
			mData.Play_Sound(CW::snd_Hover);
			sound_block = true;
		}
	}
	else
	{
		sound_block = false;
	}
}

void CometWars_SubState_Pause::handle_Events(sf::Event& mEvent)
{
	if (mEvent.type == sf::Event::KeyPressed)
	{
		if (mEvent.key.code == sf::Keyboard::Escape)
		{
			pUI_Manager->delete_Pause();
			mData.Play_Sound(CW::snd_Escape);
			mData.ChangeSubState(CW::sub_Play);
		}
	}
	else if (mEvent.type == sf::Event::MouseButtonPressed)
	{
		if (mEvent.mouseButton.button == sf::Mouse::Left)
		{
			mData.Play_Sound(CW::snd_Select);
		}
	}
	else if (mEvent.type == sf::Event::MouseButtonReleased)
	{
		CW::Button_Selection sel = pUI_Manager->response_Pause();
		if (mEvent.mouseButton.button == sf::Mouse::Left)
		{
			if (sel == CW::bt_Continue)
			{
				mData.ChangeSubState(CW::sub_Play);
				pUI_Manager->delete_Pause();
			}
			else if (sel == CW::bt_New)
			{
				mData.ChangeSubState(CW::sub_Start);
				game->RestartGame();
				pUI_Manager->create_CountDown();
				pUI_Manager->delete_Pause();
			}
			else if (sel == CW::bt_Exit)
			{
				pUI_Manager->delete_Pause();
				mData.Exit();
			}
		}
	}
}

void CometWars_SubState_Pause::handle_RealTimeInput()
{
	pUI_Manager->interact_Pause();
}

