#include "stdafx.h"
#include "BreakTrough Game.h"
#include "DataStorage.h"

BreakTroughGame::BreakTroughGame(Data& data)
	:mData(data)
	, mPlayer(mData)
	, mLevel_Manager(mData)
	, mUI_Manager(mData)
	, mLogic(mData)
{
	mData.update_Mouse();
	pGameObjects					ptr;

	BreakTrough_Player*		p1 = &mPlayer;
	BreakTrough_Level_Manager*	p2 = &mLevel_Manager;
	BreakTrough_UI_Manager*		p3 = &mUI_Manager;

	mLogic.pass_Pointers(p1, p2, p3);
	std::deque<pGameObjects>	temp_deque;

	temp_deque = mLevel_Manager.pass_Pointers();
	mObjects_for_draw.insert(mObjects_for_draw.end(), temp_deque.begin(), temp_deque.end());

	temp_deque.clear();
	temp_deque = mPlayer.pass_Pointers();
	mObjects_for_draw.insert(mObjects_for_draw.end(), temp_deque.begin(), temp_deque.end());

	mLevel_Manager.Load_Level(mData.get_Object_Quantities(Break::Current_Level));

	std::deque<pUIObjects>	 temp_UI_deque = mUI_Manager.pass_pointers();
	mUI_for_draw.insert(mUI_for_draw.end(), temp_UI_deque.begin(), temp_UI_deque.end());

	change_SubState(mData.get_Current_Substate());
}

void BreakTroughGame::draw(sf::RenderWindow& window) 
{
	for (const auto it : mObjects_for_draw)
	{
		window.draw(*it);
	}
	for (const auto it : mUI_for_draw)
	{
		window.draw(*it);
	}


}

void BreakTroughGame::update(sf::Time& time)
{
	Break::SubStates state = mData.get_Current_Substate();
	if (mSubStCheck != state)
	{
		change_SubState(state);
	}
	mData.getMusicPlayer().Music_function(ID_BreakTrough);
	pSubState->update_Substate(time);
	refresh_draw_pointers();
}

void BreakTroughGame::change_SubState(Break::SubStates param)
{
	BreakTrough_Player*			p1 = &mPlayer;
	BreakTrough_Level_Manager*	p2 = &mLevel_Manager;
	BreakTrough_UI_Manager*		p3 = &mUI_Manager;

	if (param == Break::SubSt_Play)
	{
		pSubState.reset(new BrkTr_SubSt_Play(mData, p1, p2, p3));
	}
	else if (param == Break::SubSt_Pause)
	{
		pSubState.reset(new BrkTr_SubSt_Pause(mData, p3));
	}
	else if (param == Break::SubSt_StartMission)
	{
		pSubState.reset(new BrkTr_SubSt_Start(mData, p3));
	}
	else if (param == Break::SubSt_End)
	{
		pSubState.reset(new BrkTr_SubSt_End(mData, p3));
	}

	mSubStCheck = param;
}

void BreakTroughGame::handleEvents(sf::Event& mEvent)
{
	pSubState->handle_Events(mEvent);
}

void BreakTroughGame::handleRealTimeInput()
{
	mData.update_Mouse();
	pSubState->handle_RealTimeInput();
}

void BreakTroughGame::refresh_draw_pointers()
{
	//	Here I have to erase all and insert new pointers every frame, since the pointers are no longer valid when
	//	object they point to get deleted inside their respective container.

	mObjects_for_draw.clear();
	pGameObjects			ptr;
	std::deque<pGameObjects>	temp_deque;

	temp_deque = mLevel_Manager.pass_Pointers();
	mObjects_for_draw.insert(mObjects_for_draw.end(), temp_deque.begin(), temp_deque.end());

	temp_deque.clear();
	temp_deque = mPlayer.pass_Pointers();
	mObjects_for_draw.insert(mObjects_for_draw.end(), temp_deque.begin(), temp_deque.end());

	mUI_for_draw.clear();
	std::deque<pUIObjects>	 temp_UI_deque = mUI_Manager.pass_pointers();
	mUI_for_draw.insert(mUI_for_draw.end(), temp_UI_deque.begin(), temp_UI_deque.end());
}
