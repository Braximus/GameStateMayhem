#include "stdafx.h"
#include "BreakTroughState.h"
#include "DataStorage.h"


BreakTroughState::BreakTroughState(Data& data)
	:mData(data),
	mBreakTheGame(mData)
{
}

void BreakTroughState::draw(sf::RenderWindow& win)
{
	mBreakTheGame.draw(win);
}

void BreakTroughState::update(sf::Time& time)
{
	mBreakTheGame.update(time);
}

void BreakTroughState::handleEvents(sf::Event& mEvent)
{
	mBreakTheGame.handleEvents(mEvent);
}

void BreakTroughState::handleRealTimeInput()
{
	mBreakTheGame.handleRealTimeInput();
}
