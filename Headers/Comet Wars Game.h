#ifndef COMETWARS_GAME_H
#define COMETWARS_GAME_H

#include "Debug.h"
#include "Comet Wars UI Objects.h"
#include "Comet Wars Data.h"
#include "Comet Wars Logic.h"

#include "Comet Wars Player.h"
#include "Comet Manager.h"
#include "Comet Wars UI Manager.h"
#include "Comet Wars Decorations Manager.h"

#include "Comet Wars SubStates BaseClass.h"
#include "Comet Wars SubSt Play.h"
#include "Comet Wars SubSt Start.h"
#include "Comet Wars SubSt Pause.h"
#include "Comet Wars SubSt End.h"

class Data;

class CometWarsGame
{
	CometWarsData					mData;
	CW::SubStates					mSubStateCheck;
	CometWars_Player				mPlayer;
	Comet_Manager					mCometManager;
	CometWars_UI_Manager			mUImanager;
	CometWarsLogic				mLogic;
	CometWars_Deco_Manager			mDecorationManager;

	void							LoadGame();
	void							LoadSubStates(CW::SubStates);
	void							EndGame(bool);
	std::unique_ptr<CometWarsSubStates>		pSubState;

	std::deque<CometWars_Game_Objects*>		mGame_object_pointers_for_draw;
	std::deque<CometWars_UI_Objects*>		mUI_object_pointers_for_draw;
	std::deque<CometWars_Deco_Base_Class*>		mDecoration_object_pointers_for_draw;

	void			get_pointers();
public:
	explicit		CometWarsGame(Data&);

	void			draw(sf::RenderWindow&) const;
	void			update(sf::Time&);
	void			handleEvents(sf::Event&);
	void			handleRealTimeInput();
	void			RestartGame();
};
#endif
