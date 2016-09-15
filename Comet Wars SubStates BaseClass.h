#ifndef COMETWARS_SUBSTATES_H
#define COMETWARS_SUBSTATES_H

#include "stdafx.h"

class CometWarsSubStates
{
public:	
	virtual void		update_Substate(sf::Time&)=0;
	virtual void		handle_Events(sf::Event&)=0;
	virtual void		handle_RealTimeInput()=0;
};

//	Ovo je apstraktna bazna klasa za podstanja.
//	Sve klase podstanja bice nasledjene od nje.
//	Podstanja imaju sopstvene funckije za crtanje, osvezenje i rukovanjem dogadjajima.

#endif