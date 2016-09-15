#ifndef QUATA_UI_MANAGER_H
#define QUATA_UI_MANAGER_H

class QuataData;
#include "Quata UI Text.h"
#include "Quata UI SplashScreen.h"
#include "Quata Pause.h"

class Quata_UI_Manager
{
	QuataData&		mData;
	std::map<Qua::Quata_Texts, Quata_UI_Text>				mTexts;	//	 Oznake i skorovi!
	std::map<Qua::Quata_UI_Components, Quata_UI_Text>		mScores;
	std::unique_ptr<Quata_Pause>					pPause;
	std::unique_ptr<Quata_SplashScreen>					pSplashScreen;

	bool			is_pause_on, is_SplashScreen_on;
public:
	explicit	Quata_UI_Manager(QuataData&);
	std::deque<Quata_UI_Objects*>	pass_pointers();

	void		change_score(Qua::Quata_UI_Components type);

	void							create_Pause();
	void							pause_interact(sf::Vector2f mouse_pos);
	const bool						is_mouse_hovering_in_pause() const;
	const Qua::Button_Selection		pause_response() const;
	void							delete_Pause();
		
	void		create_SplashScreen(std::string);
	void		delete_SplashScreen();

};



#endif