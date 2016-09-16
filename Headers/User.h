#ifndef USER_H
#define USER_H


#include "StateCategory.h"

class State;
class Data;

class User
{
	State*				ptrStateUser;
	sf::RenderWindow&		mWindow;
	Data&				mData;

	bool				Screenshot;
public:
	User(sf::RenderWindow&, Data&);

	void				passPtr(State*);

	void				handleEvents(sf::Event&);
	void				handleRealTimeInputs();

	void				GlobalActions(sf::Event&);

};

#endif
