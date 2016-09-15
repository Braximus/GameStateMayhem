#include "stdafx.h"
#include "StateManager.h"
#include "StateCategory.h"
#include "DataStorage.h"


StateManager::StateManager(Data& data)
	: mData(data)
{
}

State* StateManager::getCurrentState() 
{
	return pAppState.get();
}

void StateManager::ChangeState(eState state)
{
	if (mOldState != state)
	{
		pAppState.reset();
		if (state == e_Menu)
			pAppState = std::unique_ptr<State>(new MenuState(mData));
		else if (state == e_Quata)
			pAppState = std::unique_ptr<State>(new QuataState(mData));
		else if (state == e_CometWars)
			pAppState = std::unique_ptr<State>(new CometWarsState(mData));
		else if (state == e_BreakTrough)
			pAppState = std::unique_ptr<State>(new BreakTroughState(mData));
		mData.ChangeState(state);
		mOldState = state;
	}
}

const eState StateManager::getStateID() const
{
	return mData.getStateID();
}

void StateManager::draw(sf::RenderWindow& win)
{
	pAppState->draw(win);
}

void StateManager::update(sf::Time& time)
{
	pAppState->update(time);
}