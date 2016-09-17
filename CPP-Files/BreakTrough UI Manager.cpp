#include "stdafx.h"
#include "BreakTrough UI Manager.h"
#include "BreakTrough Data.h"

BreakTrough_UI_Manager::BreakTrough_UI_Manager(BreakTrough_Data& data)
	: mData(data)
	, mLives(mData)
	, mActivePower_Ups(mData)
	, mScore(mData)
{
	show_overlay = false;
}

std::deque<BrkTr_UI_Objects*> BreakTrough_UI_Manager::pass_pointers()
{
	std::deque<BrkTr_UI_Objects*>	temp_deque;
	BrkTr_UI_Objects*				ptr;

	ptr = &mLives;
	temp_deque.push_back(std::move(ptr));
	ptr = &mScore;
	temp_deque.push_back(std::move(ptr));
	ptr = &mActivePower_Ups;
	temp_deque.push_back(std::move(ptr));
	if (show_overlay)
	{
		ptr = pOverlay.get();
		temp_deque.push_back(std::move(ptr));
	}
	if (show_pause)
	{
		ptr = pPause.get();
		temp_deque.push_back(std::move(ptr));
	}
	return temp_deque;
}

void BreakTrough_UI_Manager::show_or_hide_Overlay(bool param)
{
	if (param)
	{
		if (!show_overlay)
			pOverlay = std::unique_ptr<BrkTr_Overlay>(new BrkTr_Overlay(mData));
	}
	else
	{
		if (show_overlay)
			pOverlay.release();
	}
	show_overlay = param;
}

void BreakTrough_UI_Manager::set_Overlay_text(std::string param)
{
	pOverlay->game_over_text(param);
}

void BreakTrough_UI_Manager::update(sf::Time& time)
{
	mActivePower_Ups.update(time);
}

void BreakTrough_UI_Manager::add_life()
{
	mLives.add_life();
}

void BreakTrough_UI_Manager::remove_life()
{
	mLives.delete_life();
}

void BreakTrough_UI_Manager::show_or_hide_Pause(bool param)
{
	if (param)
	{
		if (!show_pause)
			pPause = std::unique_ptr<BreakTrough_Pause>(new BreakTrough_Pause(mData));
	}
	else
	{
		if (show_pause)
			pPause.release();
	}
	show_pause = param;
}

void BreakTrough_UI_Manager::interact_pause(sf::Vector2f param)
{
	if (show_pause)
		pPause->interact(param);
}

const bool BreakTrough_UI_Manager::is_mouse_hovering_in_pause_menu() const
{
	if (show_pause)
		return pPause->is_hovering();
	else
		return false;
}

const Break::Button_Selection BreakTrough_UI_Manager::Pause_response() const
{
	return pPause->response();
}

void BreakTrough_UI_Manager::add_PowerUp(Break::PowerUp_ID id)
{
	mActivePower_Ups.add_PowerUp(id);
}

void BreakTrough_UI_Manager::remove_all_PowerUps()
{
	mActivePower_Ups.remove_all_PowerUps();
}

const float BreakTrough_UI_Manager::get_remaining_PowerUp_time(Break::PowerUp_ID param) const
{
	return mActivePower_Ups.get_remaining_time(param);
}

void BreakTrough_UI_Manager::change_score(UINT param)
{
	mScore.update_text(std::to_string(param));
}

