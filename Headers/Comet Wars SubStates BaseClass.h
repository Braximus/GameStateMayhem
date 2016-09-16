#ifndef COMETWARS_SUBSTATES_H
#define COMETWARS_SUBSTATES_H

#include "stdafx.h"

//	This is the abstract class for substates.
class CometWarsSubStates
{
public:	
	virtual void		update_Substate(sf::Time&)=0;
	virtual void		handle_Events(sf::Event&)=0;
	virtual void		handle_RealTimeInput()=0;
};
#endif
