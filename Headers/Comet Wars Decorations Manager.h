#ifndef COMET_WARS_DECORATION_MANAGER_H
#define COMET_WARS_DECORATION_MANAGER_H

#include "Comet Wars Deco Base Class.h"
#include "Comet Wars Background.h"
#include "Comet Wars Rear Comets.h"
class CometWarsData;

class CometWars_Deco_Manager
{
	CometWarsData&			mData;
	CometWars_Background	mBackground;
	CometWars_Rear_Comets	mRearComets;
public:
	CometWars_Deco_Manager(CometWarsData&);
	std::deque<CometWars_Deco_Base_Class*>			pass_pointers();

	void			update(sf::Time&);
};
#endif
