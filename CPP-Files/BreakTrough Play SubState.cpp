#include "stdafx.h"
#include "BreakTrough Play SubState.h"
#include "BreakTrough Data.h"
#include "BreakTrough UI Manager.h"
#include "BreakTrough Player.h"
#include "BreakTrough Level Manager.h"


BrkTr_SubSt_Play::BrkTr_SubSt_Play(BreakTrough_Data& data, BreakTrough_Player* pPlay, BreakTrough_Level_Manager* pLevel, BreakTrough_UI_Manager* pUI)
	: mData(data)
	, mLogic(data)
{
	pPlayer = pPlay;
	pLevel_Manager = pLevel;
	pUI_Manager = pUI;
	mLogic.pass_Pointers(pPlay, pLevel, pUI);
}

void BrkTr_SubSt_Play::update_Substate(sf::Time& time)
{
	if (!mData.Set_TheEnd())
	{
		
		if (pLevel_Manager->get_Number_of_Blocks() == 0)
		{
			mData.set_Object_Quantities(Break::Current_Level, mData.get_Object_Quantities(Break::Current_Level) + 1);
			if (! (mData.get_Object_Quantities(Break::Current_Level) == 7))
				mData.Change_SubState(Break::SubSt_StartMission);
			pPlayer->reset_Paddle();
			pPlayer->reset_Ball();
			pPlayer->delete_Laser();
			if (pLevel_Manager->does_PowerUp_falls())
				pLevel_Manager->delete_PowerUp();
			pUI_Manager->remove_all_PowerUps();
			
			pLevel_Manager->Load_Level(mData.get_Object_Quantities(Break::Current_Level));
		}
		else if (pPlayer->get_number_of_Balls() < 1)
		{
			pPlayer->delete_Laser();
			if (pLevel_Manager->does_PowerUp_falls())
				pLevel_Manager->delete_PowerUp();
			if (pPlayer->get_is_Paddle_fading())
			{
				pPlayer->fade_Paddle();
			}
			else
			{
				pPlayer->reset_Paddle();
				pPlayer->reset_Ball();
				pUI_Manager->remove_all_PowerUps();
				mData.Change_SubState(Break::SubSt_StartMission);
			}
		}
		else
		{
			pPlayer->update(time);
			pLevel_Manager->update(time);
			pUI_Manager->update(time);
			mLogic.Logic_function();
		}
	}
	else
	{
		mData.Change_SubState(Break::SubSt_End);
	}

}

void BrkTr_SubSt_Play::handle_Events(sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
		{
			pUI_Manager->show_or_hide_Pause(true);
			mData.Change_SubState(Break::SubSt_Pause);
		}
		else if (Event.key.code == sf::Keyboard::Return)
		{
			pPlayer->set_Paddle_Type(Break::Paddle_Laser);
		}
	}
}

void BrkTr_SubSt_Play::handle_RealTimeInput()
{
	pPlayer->move_Paddle();
}


