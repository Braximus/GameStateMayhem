#ifndef CHOOSE_GAME_MENU_H
#define CHOOSE_GAME_MENU_H


#include "Buttons.h"
#include "Label.h"
#include "Menu_Substates_Base_Class.h"

class Data;

class ChooseMenu: public Menu_SubStates
{
	enum GameChoice
	{
		None,
		Quata,
		CometWars,
		BreakTrough,
		Back
	};

	MenuData&						mMenu_Data;
	sf::Text						mDescription, debag;
	GameChoice						mCurrentSelection, mPreviousSelection;
	Label							mLabel;
	
	std::map<GameChoice, Button>		mButtons;
	std::map<GameChoice, std::string>	mDescriptionName;

	void					KeyboardEvents(sf::Event& Event);
	void					MouseEvents(sf::Event& Event);
	void					Change_Description(std::string);
public:
	explicit				ChooseMenu(MenuData& data);

	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					update(sf::Time&);
	void					handleEvents(sf::Event&);
	void					handleRealTimeInput();
	void					refresh();
};
#endif
