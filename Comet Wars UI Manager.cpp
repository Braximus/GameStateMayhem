#include "stdafx.h"
#include "Comet Wars UI Manager.h"
#include "Comet Wars Data.h"


CometWars_UI_Manager::CometWars_UI_Manager(CometWarsData& data)
	: mData(data)
	, mArea(data)
	, mLives(data)
	, mScore(data)
{
	is_Pause_active = false;
	is_TextFlash_active = false;
	is_SplashScreen_active = false;
	is_CountDown_active = false;
}

std::deque<CometWars_UI_Objects*> CometWars_UI_Manager::pass_pointers()
{
	std::deque<CometWars_UI_Objects*>	temp_deque;

	temp_deque.push_back(&mArea);
	temp_deque.push_back(&mLives);
	temp_deque.push_back(&mScore);


	if (is_CountDown_active)
	{
		temp_deque.push_back(pCountDown.get());
	}
	if (is_SplashScreen_active)
	{
		temp_deque.push_back(pSplashScreen.get());
	}
	if (is_TextFlash_active)
	{
		temp_deque.push_back(pTextFlash.get());
	}
	if (is_Pause_active)
	{
		temp_deque.push_back(pPause.get());
	}
	
	return temp_deque;
}

void CometWars_UI_Manager::update(sf::Time& time)
{
	mLives.update(time);

	if (is_TextFlash_active)
	{
		pTextFlash->update(time);
		if (!pTextFlash->fade_in && !pTextFlash->fade_out)
		{
			delete_TextFlash();
		}
	}
	if (is_CountDown_active)
	{
		pCountDown->update(time);
	}
	if (is_SplashScreen_active)
	{
		pSplashScreen->update(time);
	}
	if (is_Pause_active)
	{
		pPause->update(time);
	}
}

void CometWars_UI_Manager::delete_life()
{
	mLives.delete_life();
}

void CometWars_UI_Manager::refresh_lives()
{
	//	Za sada samo brise zivot.
	mLives.reset(mData.getNumber_of_Lives());
}

void CometWars_UI_Manager::refresh_score()
{
	mScore.refresh_score(mData.getScore());
}

void CometWars_UI_Manager::create_TextFlash()
{
	if (!is_TextFlash_active)
	{
		pTextFlash.reset(new CometWars_UI_Text_Flash(mData));
		is_TextFlash_active = true;
	}
}

void CometWars_UI_Manager::delete_TextFlash()
{
	pTextFlash.release();
	is_TextFlash_active = false;
}

void CometWars_UI_Manager::create_SplashScreen(std::string param)
{
	if (!is_SplashScreen_active)
	{
		pSplashScreen.reset(new CometWars_UI_SplashScreen(mData));
		pSplashScreen->setText(param);
		is_SplashScreen_active = true;
	}
}

void CometWars_UI_Manager::delete_SplashScreen()
{
	pSplashScreen.release();
	is_SplashScreen_active = false;
}

void CometWars_UI_Manager::create_CountDown()
{
	if (!is_CountDown_active)
	{
		pCountDown.reset(new CometWars_UI_Countdown(mData));
		is_CountDown_active = true;
	}
}

const float CometWars_UI_Manager::getCountDown_time() const
{
	float i = 0;
	if (is_CountDown_active)
	{
		i = pCountDown->getTimer();
	}
	return i;
}

void CometWars_UI_Manager::delete_CountDown()
{
	pCountDown.release();
	is_CountDown_active = false;
}

void CometWars_UI_Manager::create_Pause()
{
	if (!is_Pause_active)
	{
		pPause.reset(new CometWars_UI_Pause(mData));
		is_Pause_active = true;
	}
}

void CometWars_UI_Manager::interact_Pause()
{
	if (is_Pause_active)
	{
		pPause->interact(mData.getMouse_position());
	}
}

const bool CometWars_UI_Manager::is_mouse_hovering_in_Pause() const
{
	if (is_Pause_active)
	{
		return pPause->is_hovering();
	}
	return false;
}

const CW::Button_Selection CometWars_UI_Manager::response_Pause() const
{
	if (is_Pause_active)
	{
		return pPause->response();
	}
	return CW::bt_None;
}

void CometWars_UI_Manager::delete_Pause()
{
	pPause.release();
	is_Pause_active = false;
}
