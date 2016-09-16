#ifndef CometWars_STATE_H
#define CometWars_STATE_H

#include "State.h"
#include "Comet Wars Game.h"

class Data;

class CometWarsState : virtual public State
{
	Data&				mData;
	CometWarsGame		mCometWarsTheGame;
public:
	explicit			CometWarsState(Data&);

	void				draw(sf::RenderWindow&);
	void				update(sf::Time& );
	void				handleEvents(sf::Event&);
	void				handleRealTimeInput();
		
};




#endif
