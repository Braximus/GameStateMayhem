#include "stdafx.h"
#include "Comet Wars SubSt End.h"
#include "Comet Wars UI Manager.h"
#include "Comet Wars Logic.h"
#include "Comet Manager.h"
#include "Comet Wars Decorations Manager.h"

CometWars_SubState_End::CometWars_SubState_End(CometWarsData& data, CometWars_UI_Manager* ui, Comet_Manager* comet, CometWarsLogic* logic, CometWars_Deco_Manager* deco)
	:mData(data)
	, pUI_Manager(ui)
	, pComet_Manager(comet)
	, pLogic(logic)
	, pDeco_Manager(deco)
{
	is_it_created = false;
}

void CometWars_SubState_End::update_Substate(sf::Time& time)
{
	if (mData.mEndType == CW::eVictory)
	{
		if (!is_it_created)
		{
			pUI_Manager->create_SplashScreen(mData.getText(CW::txt_Win));
			is_it_created = true;
		}
	}
	else if (mData.mEndType == CW::eDefeat)
	{
		if (!is_it_created)
		{	
			pUI_Manager->create_SplashScreen(mData.getText(CW::txt_Loose));
			is_it_created = true;
		}
	}
	pDeco_Manager->update(time);
	pComet_Manager->update(time);
	pLogic->LogicFunction();

}

void CometWars_SubState_End::handle_Events(sf::Event& mEvent)
{
	if (mEvent.type == sf::Event::KeyPressed)
	{
		if (mEvent.key.code == sf::Keyboard::Escape || mEvent.key.code == sf::Keyboard::Return)
		{
			mData.Exit();
		}
	}
}