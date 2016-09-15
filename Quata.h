#ifndef QUATA_H
#define QUATA_H


#include "Debug.h"
#include "Quata Data.h"
#include "Quata Enumerations.h"
#include "Quata Objects.h"
#include "Quata UI Manager.h"
#include "Quata Logic.h"
#include "Quata SubSt Pause.h"
#include "Quata SubSt Start.h"
#include "Quata SubSt Play.h"
#include "Quata SubSt End.h"
#include "Quata AI.h"
#include "Quata Player.h"
#include "Quata Level.h"

//		Moram da napravim da Quata bude vise nalik BreakTrough:		GOTOVO

//		Da napravim da svi njeni fajlovi imaju Quata predznak:

class Quata
{
private:
	typedef QuataObjects*		PtrObj;
	typedef Quata_UI_Objects*	PtrUIObj;

	QuataData									mData;
	std::unique_ptr<QuataSubState>	pSubState;

	Qua::SubState				mSubStateCheck;
	QuataAI						mAI;
	Quata_Player				mPlayer;
	Quata_Level					mLevel;
	Quata_UI_Manager			mUI_Manager;
	std::deque<PtrObj>			Objects_for_draw;
	std::deque<PtrUIObj>		UI_for_draw;	

	void				loadQuata();
	void				Change_SubState(Qua::SubState);
public:
	Quata(Data& data);
	~Quata();
	void				draw(sf::RenderWindow&) const;
	void				handleEvents(sf::Event&);
	void				handleRealTimeInput();
	void				update(sf::Time&);
	
	void				winCondition();
	void				AI_turn(sf::Time& time);
	void				sendDebugInfo();

};





#endif
