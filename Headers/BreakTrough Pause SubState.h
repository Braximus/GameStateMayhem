#ifndef BREAKTROUGH_PAUSE_SUBSTATE_H
#define BREAKTROUGH_PAUSE_SUBSTATE_H

#include "BreakTrough SubState Base Class.h"
class BreakTrough_UI_Manager;
class BreakTrough_Data;

class BrkTr_SubSt_Pause : public BreakTrough_SubStates
{
	BreakTrough_UI_Manager*		pUI_Manager;
	BreakTrough_Data&		mData;
	bool				block;
public:
	explicit	BrkTr_SubSt_Pause(BreakTrough_Data& data, BreakTrough_UI_Manager* pUI);
	void		update_Substate(sf::Time&);
	void		handle_Events(sf::Event&);
	void		handle_RealTimeInput();
};

#endif
