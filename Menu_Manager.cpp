#include "stdafx.h"
#include "Menu_Manager.h"
#include "DataStorage.h"

Menu_Manager::Menu_Manager(Data& data)
	:mData(data)
	, mMenu_Data(data)
{


	//	Ovde pravim sva potstanja!
	pSubStates		pointer = std::unique_ptr<MainMenu>(new MainMenu(mMenu_Data));
	cont_SubState_container.insert(std::pair<Menus::SubStates, pSubStates>(Menus::Main_Menu, std::move(pointer)));
	pointer = std::unique_ptr<Options>(new Options(mMenu_Data));
	cont_SubState_container.insert(std::pair<Menus::SubStates, pSubStates>(Menus::Options_Menu, std::move(pointer)));
	pointer = std::unique_ptr<ChooseMenu>(new ChooseMenu(mMenu_Data));
	cont_SubState_container.insert(std::pair<Menus::SubStates, pSubStates>(Menus::Choose_Game_Menu, std::move(pointer)));
	pointer = std::unique_ptr<Credits>(new Credits(mMenu_Data));
	cont_SubState_container.insert(std::pair<Menus::SubStates, pSubStates>(Menus::Credits_Menu, std::move(pointer)));

	mMenu_Data.ChangeSubState(Menus::Main_Menu);
}

void Menu_Manager::draw(sf::RenderWindow& window) const
{
	window.draw(*cont_SubState_container.at(mMenu_Data.getCurrentSubState()));
}

void Menu_Manager::update(sf::Time& time)
{
	mMenu_Data.getMusicPlayer().Music_function(ID_Menu);
	if (!mMenu_Data.mRefreshed)
	{
		mMenu_Data.refresh();
		for (std::map<Menus::SubStates, pSubStates>::iterator it = cont_SubState_container.begin(); it != cont_SubState_container.end(); ++it)
		{
			it->second->refresh();
		}
		mMenu_Data.mRefreshed = true;
	}

	cont_SubState_container.at(mMenu_Data.getCurrentSubState())->update(time);
}

void Menu_Manager::handleEvents(sf::Event& Event)
{
	cont_SubState_container.at(mMenu_Data.getCurrentSubState())->handleEvents(Event);
}

void Menu_Manager::handleRealTimeInput()
{
	cont_SubState_container.at(mMenu_Data.getCurrentSubState())->handleRealTimeInput();
}