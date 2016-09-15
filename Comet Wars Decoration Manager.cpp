#include "stdafx.h"
#include "Comet Wars Decorations Manager.h"
#include "Comet Wars Data.h"

CometWars_Deco_Manager::CometWars_Deco_Manager(CometWarsData& data)
	:mData(data)
	, mBackground(data)
	, mRearComets(data)
{

}

std::deque<CometWars_Deco_Base_Class*>	CometWars_Deco_Manager::pass_pointers()
{
	std::deque<CometWars_Deco_Base_Class*>	temp_ptr;
	temp_ptr.push_back(&mBackground);

	temp_ptr.push_back(&mRearComets);

	return temp_ptr;
	//	Mozda kasnije bude vise;
}

void CometWars_Deco_Manager::update(sf::Time& time)
{
	mBackground.update(time);
	mRearComets.update(time);
}