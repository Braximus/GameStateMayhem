#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "Menu_Enumerations.h"
#include "Menu_Data.h"
#include "Menu_Substates_Base_Class.h"
#include "Main_Menu.h"
#include "Options_Menu.h"
#include "Choose_Game_Menu.h"
#include "Credits.h"

class Data;
//	Ova klasa inicijalizuje i manipulise svim menijima, koji postoje kao podstanja.

class Menu_Manager 
{

	Data&										mData;
	MenuData									mMenu_Data;
	typedef	std::unique_ptr<Menu_SubStates>		pSubStates;
	Menus::SubStates							mCurrentSubState;
	std::map<Menus::SubStates, pSubStates>		cont_SubState_container;
	
public:
	Menu_Manager(Data&);

	void			draw(sf::RenderWindow&) const;
	void			update(sf::Time&);
	void			handleEvents(sf::Event& mEvent);
	void			handleRealTimeInput();

};



#endif