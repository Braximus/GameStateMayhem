#ifndef BREAKTROUGH_END_SUBSTATE_H
#define BREAKTROUGH_END_SUBSTATE_H

#include "BreakTrough SubState Base Class.h"

class BreakTrough_Data;
class BreakTrough_UI_Manager;

class BrkTr_SubSt_End : public BreakTrough_SubStates
{
	BreakTrough_Data&			mData;
	BreakTrough_UI_Manager*		pUI_Manager;
	bool						is_set;
public:
	explicit	BrkTr_SubSt_End(BreakTrough_Data& data, BreakTrough_UI_Manager* pUI);
	void		update_Substate(sf::Time&);
	void		handle_Events(sf::Event&);
	void		handle_RealTimeInput();
};



#endif