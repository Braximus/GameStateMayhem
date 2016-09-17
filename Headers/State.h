#ifndef STATE_H
#define STATE_H
#include "stdafx.h"
#include "StateCategory.h"

class StateManager;

class State
{

public:
	virtual ~State() {};

	virtual void			draw(sf::RenderWindow& ) = 0;
	virtual void			update(sf::Time&) =0;
	virtual void			handleEvents(sf::Event&) = 0;
	virtual void			handleRealTimeInput() = 0;
};

#endif
