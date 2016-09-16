#ifndef MENUSTATE_H
#define MENUSTATE_H


#include "User.h"
#include "State.h"
#include "Menu_Manager.h"

class Data;


class MenuState : virtual public State
{
	Data&					mData;
	Menu_Manager			mMenu;

public:
	explicit				MenuState(Data& data);
	
	void					draw(sf::RenderWindow& );
	void					update(sf::Time&);
	void					handleEvents(sf::Event&);
	void					handleRealTimeInput();
};

#endif
