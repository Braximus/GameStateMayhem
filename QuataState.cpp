#include "stdafx.h"
#include "QuataState.h"
#include "DataStorage.h"

QuataState::QuataState(Data& data)
	: mData(data)
	, mQuata(mData)
{

}

void QuataState::draw(sf::RenderWindow& window)
{
	mQuata.draw(window);
}

void QuataState::handleEvents(sf::Event& mEvent)
{
	mQuata.handleEvents(mEvent);
}

void QuataState::update(sf::Time& time)
{
	mQuata.update(time);
}

void QuataState::handleRealTimeInput()
{
	mQuata.handleRealTimeInput();
}