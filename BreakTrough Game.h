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

//	Sledece sto trebam da uradim jeste:
//	1. Da laser kada se napravi, ne bude napravljen van nivoa.	GOTOVO!!!
//	2. Da lopte se odbiju samo jednom.							GOTOVO!!!
//	3. Napravim nove nivoe. (jos 2)								GOTOVO!!!
//	4. Konacno preuredim logiku.								GOTOVO KONACNO!!!! JEBOTE
//	5. Da dodam zvukove.										GOTOVO!!!
//	6. Napravim razlicite tipove blokova i njihovo ponasanje.	GOTOVO!!!
//	7. Popravim kraj igre										GOTOVO!!!
//	8. Da namestim rezultate.									GOTOVO!!!
//	9. Dodam jos par nivoa.										GOTOVO!!!
//	10. Prepravim sudare										GOTOVO!!!
//	11. Da napravim animacije za pedalu							GOTOVO!!!
//	12. Da dodam neku muziku (opciono) i jos zvukova			GOTOVO!!!
//	13.	Da Igrac dobije zivot na svakih 1000 poena.				GOTOVO!!!
//	14. Da preuredim citavu igru.								GOTOVO!!!
//	15. To bi bilo to... baciti se na sredjivanje menija posle

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