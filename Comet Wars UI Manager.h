#ifndef COMETWARS_UI_MANAGER_H
#define COMETWARS_UI_MANAGER_H

#include "Comet Wars UI Objects.h"
#include "Comet Wars UI Lives.h"
#include "Comet Wars UI Area.h"
#include "Comet Wars UI Score.h"
#include "Comet Wars UI Text Flash.h"
#include "Comet Wars UI Countdown.h"
#include "Comet Wars UI Splashscreen.h"
#include "Comet Wars UI Pause.h"
class CometWarsData;

class CometWars_UI_Manager
{
	CometWarsData&			mData;
	
	CometWars_UI_Area		mArea;
	CometWars_UI_Lives		mLives;
	CometWars_UI_Score		mScore;
	
	std::unique_ptr<CometWars_UI_Text_Flash>	pTextFlash;
	std::unique_ptr<CometWars_UI_SplashScreen>	pSplashScreen;
	std::unique_ptr<CometWars_UI_Countdown>		pCountDown;
	std::unique_ptr<CometWars_UI_Pause>			pPause;

	bool	is_Pause_active, is_TextFlash_active, is_SplashScreen_active, is_CountDown_active;
public:
	CometWars_UI_Manager(CometWarsData& data);
	std::deque<CometWars_UI_Objects*>	pass_pointers();
	void		update(sf::Time&);

	void		delete_life();
	void		refresh_lives();
	void		refresh_score();

	void		create_TextFlash();
	void		delete_TextFlash();

	void		create_SplashScreen(std::string);
	void		delete_SplashScreen();

	void		create_CountDown();
	const float getCountDown_time() const;
	void		delete_CountDown();

	void						create_Pause();
	void						interact_Pause();
	const bool					is_mouse_hovering_in_Pause() const;
	const CW::Button_Selection	response_Pause() const;
	void						delete_Pause();
};




#endif