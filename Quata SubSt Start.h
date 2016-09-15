#ifndef QUATA_SUBSTATE_START_H
#define QUATA_SUBSTATE_START_H


#include "Quata SubState.h"
#include "Quata UI SplashScreen.h"
class QuataData;
class Quata_Level;
class Quata_Player;
class QuataAI;
class Quata_UI_Manager;

class QuataStartSubState : public QuataSubState
{
	std::unique_ptr<Quata_SplashScreen>		mSplashScreen;
	QuataData&			mData;
	Quata_Level*		pLevel;
	Quata_Player*		pPlayer;
	QuataAI*			pAI;
	Quata_UI_Manager*	pUI;
	bool				initialised;
public:
	QuataStartSubState(QuataData& data, Quata_Player* player, QuataAI* ai, Quata_Level* level, Quata_UI_Manager* pUI);
	void				update_SubState(sf::Time&);
	void				handle_Events(sf::Event&);
	void				handle_Realtime_Input();
	void				reset_init();
};


#endif