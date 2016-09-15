#ifndef QUATA_SUBSTATE_END_H
#define QUATA_SUBSTATE_END_H

#include "Quata SubState.h"

class QuataData;
class Quata_UI_Manager;
class QuataEndSubState : public QuataSubState
{
	Quata_UI_Manager*	pUI;
	QuataData&			mData;
	bool				is_created;
public:
	QuataEndSubState(QuataData&, Quata_UI_Manager* pUI);
	void		update_SubState(sf::Time&);
	void		handle_Events(sf::Event&);
	void		handle_Realtime_Input();
};



#endif