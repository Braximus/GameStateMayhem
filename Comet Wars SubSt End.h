#ifndef COMETWARS_SUBSTATE_END_H
#define COMETWARS_SUBSTATE_END_H

#include "Comet Wars SubStates BaseClass.h"
#include "Comet Wars Data.h"

class CometWars_UI_Manager;
class Comet_Manager;
class CometWarsLogic;
class CometWars_Deco_Manager;

class CometWars_SubState_End : public CometWarsSubStates
{
	CometWarsData&			mData;
	CometWars_UI_Manager*	pUI_Manager;
	Comet_Manager*			pComet_Manager;
	CometWarsLogic*			pLogic;
	CometWars_Deco_Manager* pDeco_Manager;

	CW::End					mEndType;
	bool					is_it_created;
public:
	explicit	CometWars_SubState_End(CometWarsData& data, CometWars_UI_Manager* ui, Comet_Manager* comets, CometWarsLogic* logic, CometWars_Deco_Manager* deco);
	void		update_Substate(sf::Time&);
	void		handle_Events(sf::Event&);
	void		handle_RealTimeInput(){};

};


#endif 
