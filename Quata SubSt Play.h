#ifndef QUATA_SUBSTATE_PLAY_H
#define QUATA_SUBSTATE_PLAY_H

#include "Quata SubState.h"
#include "Quata Logic.h"
class QuataData;
class QuataAI;
class Quata_Player;
class Quata_Level;
class Quata_UI_Manager;
class QuataPlaySubState : public QuataSubState
{
	QuataData&		mData;
	QuataLogic		mLogic;
	QuataAI*		pAI;
	Quata_Player*	pPlayer;
	Quata_Level*	pLevel;
	Quata_UI_Manager* pUI;
	void			AI_turn(sf::Time&);
public:
	QuataPlaySubState(QuataData& data, Quata_Player* player, QuataAI* ai, Quata_Level* level, Quata_UI_Manager* pUI);
	void						update_SubState(sf::Time&);
	void						handle_Events(sf::Event&);
	void						handle_Realtime_Input();
};



#endif