#include "stdafx.h"
#include "MenuState.h"
#include "DataStorage.h"

MenuState::MenuState(Data& Data)
	: mData(Data)
	, mMenu(Data)
{

}

void MenuState::draw(sf::RenderWindow& window)
{
	mMenu.draw(window);
}

void MenuState::update(sf::Time& mTime)
{
	mMenu.update(mTime);
}

void MenuState::handleEvents(sf::Event& mEvent)
{
	mMenu.handleEvents(mEvent);
}

void MenuState::handleRealTimeInput()
{
	mMenu.handleRealTimeInput();
}
