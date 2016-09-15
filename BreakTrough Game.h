#ifndef BREAKTROUGH_GAME_H
#define BREAKTROUGH_GAME_H

#include "Debug.h"

#include "BreakTrough Data.h"
#include "BreakTrough Game Objects.h"
#include "BreakTrough Player.h"
#include "BreakTrough Level Manager.h"
#include "BreakTrough Logic.h"
#include "BreakTrough UI Manager.h"

#include "BreakTrough SubState Base Class.h"
#include "BreakTrough Play SubState.h"
#include "BreakTrough End SubState.h"
#include "BreakTrough Pause SubState.h"
#include "BreakTrough Start SubState.h"

class BreakTroughGame 
{
	typedef BrkTr_Game_Objects*			pGameObjects;
	typedef BrkTr_UI_Objects*			pUIObjects;
	BreakTrough_Data				mData;
	
	std::deque<pGameObjects>		mObjects_for_draw;
	std::deque<pUIObjects>			mUI_for_draw;

	BreakTrough_Player				mPlayer;
	BreakTrough_Level_Manager		mLevel_Manager;
	BreakTrough_UI_Manager			mUI_Manager;
	BreakTrough_Logic				mLogic;


	std::unique_ptr<BreakTrough_SubStates>			pSubState;
	Break::SubStates				mSubStCheck;
	void				change_SubState(Break::SubStates);
	void				refresh_draw_pointers();
public:
	explicit			BreakTroughGame(Data& );

	void				draw(sf::RenderWindow&);
	void				update(sf::Time&);
	void				handleEvents(sf::Event&);
	void				handleRealTimeInput();
};

#endif
