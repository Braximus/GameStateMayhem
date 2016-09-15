#ifndef MAINMENU_H
#define MAINMENU_H


#include "Buttons.h"
#include "Title.h"
#include "Label.h"
#include "DropDownMenu.h"
#include "Menu_Substates_Base_Class.h"
class Data;

class MainMenu : public Menu_SubStates
{
	enum MenuSelection
	{
		None,
		Choose_Game,
		Options,
		Credits,
		Exit
		
	};
	MenuData&						mMenu_Data;
	sf::Text						mText;
	
	MenuSelection					mCurrentSelection;
	MenuSelection					mPreviousSelection;
	
	std::map<MenuSelection, Button>	mButtons;
	Title							mTitle;
	
	void					KeyboardEvents(sf::Event& Event);
	void					MouseEvents(sf::Event& Event);
public:	
	explicit				MainMenu(MenuData& data);

	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					update(sf::Time&);
	void					handleEvents(sf::Event&);
	void					handleRealTimeInput();
	void					refresh();
};



#endif