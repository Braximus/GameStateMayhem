#include "stdafx.h"
#include "Quata.h"
#include "Quata Logic.h"
#include "Quata Enumerations.h"

Quata::Quata(Data& data)
	: mData(data)
	, mUI_Manager(mData)
	, mAI(mData)
	, mPlayer(mData)
	, mLevel(mData)
{
	Change_SubState(mData.getCurrentSubstate());
}

Quata::~Quata()
{
	//
}

void Quata::draw(sf::RenderWindow& window) const
{
	for (const auto& it : Objects_for_draw)
	{
		window.draw(*it);
	}
	for (const auto& it : UI_for_draw)
	{
		window.draw(*it);
	}
}
void Quata::loadQuata()
{
	Objects_for_draw.clear();
	UI_for_draw.clear();

	std::deque<PtrObj> temp_deque = mLevel.pass_pointers();
	Objects_for_draw.insert(Objects_for_draw.end(), temp_deque.begin(), temp_deque.end());
	Objects_for_draw.push_back(mPlayer.pass_pointer());
	Objects_for_draw.push_back(mAI.pass_pointer());

	std::deque<PtrUIObj> temp_deque2 = mUI_Manager.pass_pointers();
	UI_for_draw.insert(UI_for_draw.end(), temp_deque2.begin(), temp_deque2.end());
}

void Quata::Change_SubState(Qua::SubState param)
{
	Quata_Player*		pPlayer = &mPlayer;
	QuataAI*			pAI = &mAI;
	Quata_Level*		pLevel = &mLevel;
	Quata_UI_Manager*	pUI = &mUI_Manager;
	
	if (param == Qua::Play)
	{
		//	Play
		pSubState.reset(new QuataPlaySubState(mData, pPlayer, pAI, pLevel, pUI));
	}
	else if (param == Qua::End)
	{
		//	Finish
		pSubState.reset(new QuataEndSubState(mData, pUI));
	}
	else if (param == Qua::Start)
	{
		//	Begin
		pSubState.reset(new QuataStartSubState(mData, pPlayer, pAI, pLevel, pUI));
	}
	else if (param == Qua::Pause)
	{
		//	Pause
		pSubState.reset(new QuataPauseSubState(mData, pUI));
	}

	mSubStateCheck = param;


	//std::unique_ptr<QuataSubState> PtrObj;
	//// Start
	//PtrObj = std::unique_ptr<QuataStartSubState>(new QuataStartSubState(mData, &mPlayer, &mAI, &mLevel, &mUI_Manager));
	//subStates.insert(std::pair<Qua::SubState, std::unique_ptr<QuataSubState>>(Qua::Start, std::move(PtrObj)));
	//// Win
	//PtrObj = std::unique_ptr<QuataPlaySubState>(new QuataPlaySubState(mData, &mPlayer, &mAI, &mLevel, &mUI_Manager));
	//subStates.insert(std::pair<Qua::SubState, std::unique_ptr<QuataSubState>>(Qua::Play, std::move(PtrObj)));
	//// Loose
	//PtrObj = std::unique_ptr<QuataEndSubState>(new QuataEndSubState(mData, &mUI_Manager));
	//subStates.insert(std::pair<Qua::SubState, std::unique_ptr<QuataSubState>>(Qua::End, std::move(PtrObj)));
	////	Pause
	//PtrObj = std::unique_ptr<QuataPauseSubState>(new QuataPauseSubState(mData, &mUI_Manager));
	//subStates.insert(std::pair<Qua::SubState, std::unique_ptr<QuataSubState>>(Qua::Pause, std::move(PtrObj)));
}

void Quata::sendDebugInfo()
{
	DebugClass::nums[0] = sf::Vector2i(mPlayer.get_Paddle_Position());
	DebugClass::nums[1] = sf::Vector2i(mAI.get_Paddle_Position());
}
//
void Quata::update(sf::Time& time)
{
	loadQuata();
	Qua::SubState state = mData.getCurrentSubstate();
	if (state != mSubStateCheck)
	{
		Change_SubState(state);
	}

	mData.getMusicPlayer().Music_function(ID_Quata);
	pSubState->update_SubState(time);

	if (state != Qua::End)
	{
		winCondition();
	}
	sendDebugInfo();

}

void Quata::handleEvents(sf::Event& Event)
{
	pSubState->handle_Events(Event);
}

void Quata::handleRealTimeInput()
{
	mData.update_mouse();
	pSubState->handle_Realtime_Input();
}

void Quata::winCondition()
{
	if (mData.get_Score(Qua::cu_Score1) == 5)
	{
		//mData.Play_Sound(Qua::snd_Player_Win);	--	Dok ne nadjem odgovarajuci zvuk, ovo ce da bude iskomentarisano!!!!
		mData.changeSubState(Qua::End);
	}
	else if (mData.get_Score(Qua::cu_Score2) == 5)
	{
		mData.Play_Sound(Qua::snd_Player_Loose);
		mData.changeSubState(Qua::End);
	}
}