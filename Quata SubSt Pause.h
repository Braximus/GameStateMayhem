#ifndef QUATA_PAUSE_SUBSTATE_H
#define QUATA_PAUSE_SUBSTATE_H

#include "Buttons.h"
#include "Quata SubState.h"
class QuataData;
class Quata_UI_Manager;

class QuataPauseSubState: public QuataSubState
{

	QuataData&					mData;
	Quata_UI_Manager*			pUI;
	bool						sound_block;
public:
	QuataPauseSubState(QuataData&, Quata_UI_Manager* pUI);
	void						update_SubState(sf::Time&);
	void						handle_Events(sf::Event&);
	void						handle_Realtime_Input();



};


#endif