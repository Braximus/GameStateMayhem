#include "stdafx.h"
#include "CometWarsState.h"
#include "DataStorage.h"

CometWarsState::CometWarsState(Data& data)
	:mData(data)
	, mCometWarsTheGame(mData)
{
}

void CometWarsState::draw(sf::RenderWindow& win)
{
	mCometWarsTheGame.draw(win);
}

void CometWarsState::update(sf::Time& time)
{
	mCometWarsTheGame.update(time);
}

void CometWarsState::handleEvents(sf::Event& mEvent)
{
	mCometWarsTheGame.handleEvents(mEvent);
}

void CometWarsState::handleRealTimeInput()
{
	mCometWarsTheGame.handleRealTimeInput();
}