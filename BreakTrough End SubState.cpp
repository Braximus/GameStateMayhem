#include "stdafx.h"
#include "BreakTrough End SubState.h"
#include "BreakTrough Data.h"
#include "BreakTrough UI Manager.h"

BrkTr_SubSt_End::BrkTr_SubSt_End(BreakTrough_Data& data, BreakTrough_UI_Manager* pUI)
	:mData(data)
{
	pUI_Manager = pUI;
	is_set = false;
}

void BrkTr_SubSt_End::update_Substate(sf::Time& time)
{
	if (!is_set)
	{
		pUI_Manager->show_or_hide_Overlay(true);
		if (mData.get_Switches(Break::sw_Victory))
		{
			pUI_Manager->set_Overlay_text(mData.get_Text(Break::txt_Victory));
			mData.Play_Sound(Break::snd_Player_Win);
		}
		else
		{
			pUI_Manager->set_Overlay_text(mData.get_Text(Break::txt_Defeat));
			mData.Play_Sound(Break::snd_Game_Over);
		}
		is_set = true;
	}
}

void BrkTr_SubSt_End::handle_Events(sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
		mData.Exit();
}

void BrkTr_SubSt_End::handle_RealTimeInput()
{
	//
}