#include "stdafx.h"
#include "Comet Wars Game.h"
#include "DataStorage.h"
#include "StateCategory.h"

CometWarsGame::CometWarsGame(Data& data)
	:mData(data)
	, mPlayer(mData, &mUImanager)
	, mCometManager(mData)
	, mUImanager(mData)
	, mLogic(mData, &mUImanager, &mPlayer, &mCometManager)
	, mDecorationManager(mData)
{
	LoadGame();
	LoadSubStates(mData.getCurrentSubState());	
}

void CometWarsGame::get_pointers()
{
	std::deque<CometWars_Game_Objects*> temp_cont;
	std::deque<CometWars_UI_Objects*>	second_temc_cont;

	mDecoration_object_pointers_for_draw.clear();
	mGame_object_pointers_for_draw.clear();
	mUI_object_pointers_for_draw.clear();
	mDecoration_object_pointers_for_draw = mDecorationManager.pass_pointers();

	temp_cont = mCometManager.pass_pointers();
	mGame_object_pointers_for_draw.insert(mGame_object_pointers_for_draw.end(), temp_cont.begin(), temp_cont.end());
	
	temp_cont = mPlayer.pass_pointers();
	mGame_object_pointers_for_draw.insert(mGame_object_pointers_for_draw.end(), temp_cont.begin(), temp_cont.end());
	
	second_temc_cont = mUImanager.pass_pointers();
	mUI_object_pointers_for_draw.insert(mUI_object_pointers_for_draw.end(), second_temc_cont.begin(), second_temc_cont.end());
}

void CometWarsGame::draw(sf::RenderWindow& window) const
{	
	for (const auto& it : mDecoration_object_pointers_for_draw)
	{
		window.draw(*it);
	}
	for (const auto& it : mGame_object_pointers_for_draw)
	{
		window.draw(*it);
	}
	for (const auto& it : mUI_object_pointers_for_draw)
	{
		window.draw(*it);
	}

}

void CometWarsGame::update(sf::Time& time)
{
	mData.getMusicPlayer().Music_function(ID_CometWars);
	mPlayer.delete_projectile();
	mCometManager.delete_comet();
	
	get_pointers();

	CW::SubStates state = mData.getCurrentSubState();

	if (mSubStateCheck != state)
	{
		LoadSubStates(state);
	}

	EndGame(mData.setEnd());

	mDecorationManager.update(time);

	pSubState->update_Substate(time);
}

void CometWarsGame::handleEvents(sf::Event& mEvent)
{
	pSubState->handle_Events(mEvent);
};

void CometWarsGame::handleRealTimeInput()
{
	mData.update_mouse();
	pSubState->handle_RealTimeInput();
}

void CometWarsGame::LoadGame()
{
	sf::Vector2f kp_center = mData.getKey_Position(CW::kp_Center);
	sf::Vector2f position = kp_center + sf::Vector2f(0, 5 * mData.getDistance(CW::dis_Far));
	mPlayer.setShip_Position(position);

	std::uniform_int_distribution<int>	distributor1(3,10);
	UINT asteroid_Numbers = distributor1(mData.get_random_engine());
	
	sf::Vector2i begin_pos = sf::Vector2i((kp_center.x / 2) - 3 * mData.getDistance(CW::dis_Far), (kp_center.y / 2) -3 * mData.getDistance(CW::dis_Far));
	sf::Vector2i end_pos = static_cast<sf::Vector2i>(kp_center)+sf::Vector2i((kp_center.x / 2) + 3 * mData.getDistance(CW::dis_Far), (kp_center.y / 2) - 3 * mData.getDistance(CW::dis_Far));	// yes, minus

	std::uniform_int_distribution<int>	distributor2(begin_pos.x, end_pos.x);
	std::uniform_int_distribution<int>	distributor3(begin_pos.y, end_pos.y);
	
	for (UINT i = 0; i <= asteroid_Numbers; ++i)
	{
		mCometManager.create_comet(false);
		UINT x = distributor2(mData.get_random_engine());
		UINT y = distributor3(mData.get_random_engine());
		mCometManager.setComet_Position(mCometManager.getNumber_of_comets() - 1, sf::Vector2f(x, y));
	}

	mData.change_Score(0);
	mData.setNumber_of_Comets(mCometManager.getNumber_of_comets());
}

void CometWarsGame::LoadSubStates(CW::SubStates param)
{
	CometWars_Player*		player = &mPlayer;
	Comet_Manager*			comet_man = &mCometManager;
	CometWars_UI_Manager*	ui_man = &mUImanager;
	CometWars_Deco_Manager* deco_man = &mDecorationManager;
	CometWarsLogic*			logic = &mLogic;

	if (param == CW::sub_Play)
	{
		pSubState.reset(new CometWars_SubState_Play(mData, player, comet_man, ui_man, logic, deco_man));
	}
	else if (param == CW::sub_Pause)
	{
		pSubState.reset(new CometWars_SubState_Pause(mData, ui_man, this));
	}
	else if (param == CW::sub_Start)
	{
		pSubState.reset(new CometWars_SubState_Start(mData, ui_man, deco_man));
	}
	else if (param == CW::sub_End)
	{
		pSubState.reset(new CometWars_SubState_End(mData, ui_man, comet_man, logic, deco_man));
	}

	mSubStateCheck = param;
}

void CometWarsGame::RestartGame()
{
	mData.Restart();
	mPlayer.restart();
	mCometManager.restart();
	mUImanager.refresh_lives();
	mUImanager.refresh_score();
	LoadGame();
}

void CometWarsGame::EndGame(bool param)
{
	if (param)
	{
		mData.ChangeSubState(CW::sub_End);
	}
}
