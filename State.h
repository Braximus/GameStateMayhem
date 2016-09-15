#ifndef STATE_H
#define STATE_H


#include "StateCategory.h"

class StateManager;

class State
{

public:
//	State() {};
	virtual ~State() {};

	virtual void			draw(sf::RenderWindow& ) = 0;
	virtual void			update(sf::Time&) =0;
	virtual void			handleEvents(sf::Event&) = 0;
	virtual void			handleRealTimeInput() = 0;


//	void					ChangeState(StateManager& state_cont, eState new_state);
//	const eState			CheckStateID(Data& data) const;


};



#endif