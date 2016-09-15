#include "stdafx.h"
#include "Application.h"

const sf::Time App::mFixedTime = sf::seconds(1.0f / 60.0f);

App::App()
	: mData(mWindow)
	, mState(mData)
	, mUser(mWindow, mData)
	, mDebug(mData)
{
	mCurrentTime = sf::seconds(0);
	mTimeSinceLastUpdate = sf::seconds(0);

	mData.Update_Window(0);		//	TODO: Da napravim 'initialize' funkciju koja ce biti pozvana samo na pocetku programa.
	mData.ChangeState(e_Menu);
	mState.ChangeState(mData.getStateID());
	mUser.passPtr(mState.getCurrentState());
}

void App::run()
{
	while (mWindow.isOpen())
	{
		sf::Time new_time = Clock.getElapsedTime();
		sf::Time  ElapsedTime = new_time - mCurrentTime;
		mCurrentTime = new_time;
		
		if (ElapsedTime.asSeconds() > 0.2)
		{
			ElapsedTime = sf::seconds(0.2);
		}
		mTimeSinceLastUpdate += ElapsedTime;

		if (mTimeSinceLastUpdate >= mFixedTime)
		{
			mTimeSinceLastUpdate -= mFixedTime;
			eventProcess();
			update(mFixedTime);
		}
		if (mData.checkDebug())
		{
			mDebug.DebugText(ElapsedTime);
		}

		render();
	}
}

void App::eventProcess()
{

	while (mWindow.pollEvent(mEvent))
	{
		mUser.handleEvents(mEvent);
	}
	mUser.handleRealTimeInputs();
}

void App::update(sf::Time mFixedTime)
{
	mState.ChangeState(mData.getStateID());
	mUser.passPtr(mState.getCurrentState());
	mData.update_cursor();
	mState.update(mFixedTime);

}

void App::render()
{
	mWindow.clear();
	mState.draw(mWindow);
	if (mData.CursorVisibility)
	{
		mWindow.draw(mData.getMouse_Cursor());
	}
	if (mData.checkDebug())
	{
		mWindow.draw(mDebug.drawFPS());
		mWindow.draw(mDebug.drawTxt());
	}
	mWindow.display();
}

//mTimeSinceLastUpdate = sf::seconds(0);
//
//while (mWindow.isOpen())
//{
//	sf::Time ElapsedTime = Clock.restart();
//	mTimeSinceLastUpdate += ElapsedTime;
//	if (mTimeSinceLastUpdate > mFixedTime)
//	{
//		mTimeSinceLastUpdate -= mFixedTime;
//		eventProcess();
//		update(mFixedTime);
//	}
//	if (mData.checkDebug())
//	{
//		mDebug.DebugText(ElapsedTime);
//	}
//
//	render();
//}
//
//while (mWindow.isOpen())
//{
//	sf::Time new_time = Clock.getElapsedTime();
//
//	sf::Time  ElapsedTime = new_time - mCurrentTime;
//	mCurrentTime = new_time;
//	if (ElapsedTime.asSeconds() > 0.25)
//	{
//		ElapsedTime = sf::seconds(0.25);
//	}
//	mTimeSinceLastUpdate += ElapsedTime;
//
//	if (mTimeSinceLastUpdate >= mFixedTime)
//	{
//		mTimeSinceLastUpdate -= mFixedTime;
//		eventProcess();
//		update(mFixedTime);
//	}
//	if (mData.checkDebug())
//	{
//		mDebug.DebugText(ElapsedTime);
//	}
//
//	render();
//}