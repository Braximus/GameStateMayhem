#ifndef STATE_CONTAINER_H
#define STATE_CONTAINER_H

#include <memory>
#include <map>
#include <algorithm>
#include <cassert>
#include "MenuState.h"
#include "QuataState.h"
#include "CometWarsState.h"
#include "BreakTroughState.h"

class State;
class Data;

class StateManager
{
	Data&					mData;
	//
	std::unique_ptr<State>			pAppState;
	//
	eState					mOldState;
	//
	const eState				getStateID() const;
public:
	StateManager(Data&);
	void					ChangeState(eState);
	State*							getCurrentState(); 
	void							draw(sf::RenderWindow&);
	void							update(sf::Time&);
};
#endif
