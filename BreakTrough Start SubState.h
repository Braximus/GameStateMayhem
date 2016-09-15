#ifndef BREAKTROUGH_START_SUBSTATE_H
#define BREAKTROUGH_START_SUBSTATE_H

#include "BreakTrough SubState Base Class.h"

class BreakTrough_Data;
class BreakTrough_UI_Manager;

class BrkTr_SubSt_Start : public BreakTrough_SubStates
{
	BreakTrough_Data&			mData;
	BreakTrough_UI_Manager*		pUI_Manager;
	sf::Time					mDelay;
	bool		was_sound_played;
public:
	explicit	BrkTr_SubSt_Start(BreakTrough_Data& data, BreakTrough_UI_Manager* pUI);
	void		update_Substate(sf::Time&);
	void		handle_Events(sf::Event&);
	void		handle_RealTimeInput();
};


#endif