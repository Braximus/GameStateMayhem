#ifndef QUATA_SUB_STATE_H
#define QUATA_SUB_STATE_H

#include "stdafx.h"

class QuataSubState
{
public:
	virtual void				update_SubState(sf::Time&) =0;
	virtual void				handle_Events(sf::Event&) = 0;
	virtual void				handle_Realtime_Input() =0;
};





#endif