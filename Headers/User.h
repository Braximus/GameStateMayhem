#ifndef USER_H
#define USER_H


#include "StateCategory.h"

class State;
class Data;

class User
{
	State*				ptrStateUser;
	sf::RenderWindow&	mWindow;
	Data&				mData;

	bool				Malukah;
public:
	User(sf::RenderWindow&, Data&);

	void				passPtr(State*);	// Mora da postoji odvojena funkcija za premestanje pokazivaca!

	void				handleEvents(sf::Event&);
	void				handleRealTimeInputs();

	void				GlobalActions(sf::Event&);

};

//
// Treba da se:
// ---	naprave akcije u skladu sa etapama igre!
// ---	povezu akcije sa odredjenim tasterima!
// ---	da mogucnost da se tasteri promene!
// ---	da program prepozna kada koja akcija da se preduzme u zavisnosti od trenutne etape igre!
//


#endif
