#include "stdafx.h"
#include "BreakTrough Start SubState.h"
#include "BreakTrough Data.h"
#include "BreakTrough UI Manager.h"


BrkTr_SubSt_Start::BrkTr_SubSt_Start(BreakTrough_Data& data, BreakTrough_UI_Manager* pUI)
	: mData(data)
{
	pUI_Manager = pUI;
	mDelay = sf::seconds(0);
	was_sound_played = false;
}

void BrkTr_SubSt_Start::update_Substate(sf::Time& time)
{
	mDelay += time;
	if (!was_sound_played)
	{
		mData.Play_Sound(Break::snd_Start);
		was_sound_played = true;
	}
	if (mDelay >= sf::seconds(2))
	{
		pUI_Manager->show_or_hide_Overlay(false);
		mData.Change_SubState(Break::SubSt_Play);
		mDelay = sf::seconds(0);
		was_sound_played = false;
	}
	else
	{
		pUI_Manager->show_or_hide_Overlay(true);
	}
}

void BrkTr_SubSt_Start::handle_Events(sf::Event& Event)
{
	//
}

void BrkTr_SubSt_Start::handle_RealTimeInput()
{
	//
}
