#ifndef Quata_STATE_H
#define Quata_STATE_H


#include "State.h"
#include "User.h"
#include "Quata.h"

class Data;

class QuataState : virtual public State
{
	Data&				mData;
	Quata				mQuata;
public:
	explicit			QuataState(Data&);

	void				draw(sf::RenderWindow& );
	void				update(sf::Time&);
	void				handleEvents(sf::Event&);
	void				handleRealTimeInput();
};
#endif
