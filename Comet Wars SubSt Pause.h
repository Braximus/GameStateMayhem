#ifndef COMETWARS_SUBSTATE_PAUSE_H
#define COMETWARS_SUBSTATE_PAUSE_H

#include "Comet Wars SubStates BaseClass.h"
#include "Comet Wars Data.h"

class CometWarsGame;
class CometWars_UI_Manager;


class CometWars_SubState_Pause : public CometWarsSubStates
{
	CometWarsData&				mData;
	CometWars_UI_Manager*		pUI_Manager;
	CometWarsGame*				game;
	bool						sound_block;
public:
	explicit		CometWars_SubState_Pause(CometWarsData& data, CometWars_UI_Manager* ui, CometWarsGame* g);
	void			update_Substate(sf::Time&);
	void			handle_Events(sf::Event&);
	void			handle_RealTimeInput();
};


#endif 
