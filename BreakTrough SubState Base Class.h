#ifndef BREAKTROUGH_SUBSTATE_BASE_CLASS_H
#define BREAKTROUGH_SUBSTATE_BASE_CLASS_H

#include "stdafx.h"

class BreakTrough_SubStates 
{
public:
	virtual void		update_Substate(sf::Time&) = 0;
	virtual void		handle_Events(sf::Event&) = 0;
	virtual void		handle_RealTimeInput() = 0;
};

#endif