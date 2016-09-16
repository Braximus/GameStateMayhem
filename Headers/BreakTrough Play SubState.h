#ifndef BREAKTROUGH_PLAY_SUBSTATE_H
#define BREAKTROUGH_PLAY_SUBSTATE_H

#include "BreakTrough SubState Base Class.h"
#include "BreakTrough Logic.h"

class BreakTrough_Player;
class BreakTrough_Level_Manager;
class BreakTrough_UI_Manager;
class BreakTrough_Data;

class BrkTr_SubSt_Play : public BreakTrough_SubStates
{
	BreakTrough_Player*			pPlayer;
	BreakTrough_Level_Manager*		pLevel_Manager;
	BreakTrough_UI_Manager*			pUI_Manager;
	BreakTrough_Data&			mData;
	BreakTrough_Logic			mLogic;
public:
	explicit	BrkTr_SubSt_Play(BreakTrough_Data& data ,BreakTrough_Player* pPlay, BreakTrough_Level_Manager* pLevel, BreakTrough_UI_Manager* pUI);
	void		update_Substate(sf::Time&);
	void		handle_Events(sf::Event&);
	void		handle_RealTimeInput();

};


#endif
