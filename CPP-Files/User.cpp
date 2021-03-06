#include "stdafx.h"
#include "User.h"
#include "StateManager.h"
#include "DataStorage.h"
#include "State.h"
#include <cassert>

User::User(sf::RenderWindow& win, Data& data)
	: mWindow(win)
	, mData(data)
{
	Screenshot = true;
}

void User::passPtr(State* ptr)
{
	ptrStateUser = ptr;
}

void User::handleEvents(sf::Event& Event)
{
	GlobalActions(Event);
	assert(ptrStateUser != NULL);
	ptrStateUser->handleEvents(Event);
}

void User::handleRealTimeInputs()
{
	mData.mMouseCoordinates = sf::Mouse::getPosition(mWindow);

//	Thanks to Hapax I managed learn how to use "PrintScreen" button to use it to make screenshot. :D
#ifdef SFML_SYSTEM_WINDOWS
	if (GetAsyncKeyState(VK_SNAPSHOT))
	{
		if (Screenshot)
		{
			sf::Image image = mWindow.capture();
			image.saveToFile("slike/test.jpg");
			Screenshot = false;
		}
	}
	else
		Screenshot = true;
#else
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12))
	{
		if (Screenshot)
		{
			sf::Image image = mWindow.capture();
			image.saveToFile("slike/test.jpg");
			Screenshot = false;
		}
	}
	else
		Screenshot = true;
	}
#endif // !SFML_SYSTEM_WINDOWS
	assert(ptrStateUser != NULL);
	ptrStateUser->handleRealTimeInput();
}

void User::GlobalActions(sf::Event& Event)
{
	if (Event.type == sf::Event::Closed)
	{
		mWindow.close();
	}
	else if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Tilde)
			mData.toggleDebug();
	}
	else if (Event.type == sf::Event::MouseButtonPressed && !mData.lock_cursor)
	{
		if (!mData.is_mouse_pressed )
		{
			mData.change_Cursor(sf::IntRect(20,0,13,20));
			mData.is_mouse_pressed = true;
		}
	}
	else if (Event.type == sf::Event::MouseButtonReleased  && !mData.lock_cursor)
	{
		mData.change_Cursor(sf::IntRect(0, 0, 13, 20));
		mData.is_mouse_pressed = false;
	}
}



