#ifndef BREAKTROUGHSTATE_H
#define BREAKTROUGHSTATE_H

#include "State.h"
#include "BreakTrough Game.h"
class Data;


class BreakTroughState : public State
{
	Data&				mData;
	BreakTroughGame		mBreakTheGame;
public:
	explicit			BreakTroughState(Data&);

	void				draw(sf::RenderWindow&);
	void				update(sf::Time&);
	void				handleEvents(sf::Event&);
	void				handleRealTimeInput();
};
#endif
