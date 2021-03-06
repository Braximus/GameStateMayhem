﻿#include "stdafx.h"
#include "DataStorage.h"


Data::Data(sf::RenderWindow& win)
	:mWindow(win)
	, mMusic_Player(this)
{
	DebugOnOff = false;
	updateVideoModes();
	mIsFullscreen = true;
	mVsync = true;
	setHardwareCursorOnOff = false;
	CursorVisibility = true;
	is_mouse_pressed = false;
	lock_cursor = false;
	mAA_Index = 0;

	for (UINT i = 0; i < 5; ++i)
	{
		if (std::pow(2, i) == 1)
			mAntiAliasing.push_back(0);
		else
		{
			UINT a = std::pow(2, i);
			mAntiAliasing.push_back(a);
		}
	}
	
}
Data::~Data() {};
//--------------------------//
//-------Global_Data--------//
//--------------------------//
//
void Data::toggleDebug()
{
	if (DebugOnOff)
	{
		DebugOnOff = false;
	}
	else
	{
		DebugOnOff = true;
	}
}
//--------------------------//
//--------------------------//
//
const bool Data::checkDebug() const
{
	return DebugOnOff;
}
//--------------------------//
//--------------------------//
//
void Data::Close()
{
	mWindow.close();
}
//--------------------------//
//--------------------------//
//
const float Data::getScaleCoefficient() const
{
	return mScaleCoefficient;
}
//--------------------------//
//--------------------------//
//
const eState Data::getStateID() const
{
	return mStateID;
}
//--------------------------//
//--------------------------//
//
void Data::ChangeState(eState state)
{
	mStateID = state;
}
//--------------------------//
//--------------------------//
//
void Data::set_Fullscreen_mode(bool param)
{
	mIsFullscreen = param;
}
//--------------------------//
//--------------------------//
//
const bool Data::IsFullScreen() const
{
	return mIsFullscreen;
}
//--------------------------//
//--------------------------//
//
void Data::set_AA_Level(UINT param)
{
	mAA_Index = param;
}
//--------------------------//
//--------------------------//
//
const UINT Data::get_Current_AA_Level() const
{
	return mAntiAliasing[mAA_Index];
}
//--------------------------//
//--------------------------//
//
const UINT Data::get_AA_Levels(UINT param) const
{
	return mAntiAliasing[param];
}
//--------------------------//
//--------------------------//
//
const UINT Data::get_AA_Index() const
{
	return mAA_Index;
}
//--------------------------//
//--------------------------//
//
void Data::set_Vsync(bool param)
{
	mVsync = param;
	mWindow.setVerticalSyncEnabled(mVsync);
	if (!mVsync)
	{
		mWindow.setFramerateLimit(0);
	}
	else
	{
		mWindow.setFramerateLimit(0);
	}
}
//--------------------------//
//--------------------------//
//
const bool Data::get_Vsync() const
{
	return mVsync;
}

//--------------------------//
//--------Resources---------//
//--------------------------//
//
Resources& Data::getResources()
{
	return mResources;
}
//--------------------------//
//--------------------------//
//
MusicPlayer& Data::getMusic_Player()
{
	return mMusic_Player;
}
//--------------------------//
//--------Video Mode--------//
//--------------------------//
//
void Data::updateVideoModes()
{
	//	Taking fullscreen resolutons;
	sf::VideoMode VM;
	mVideo_Modes = VM.getFullscreenModes();
	//	Deleting 8-bit and 16-bit resolutions, and modes with 720px width, because nobody uses that anymore;
	for (UINT i = 0; i < mVideo_Modes.size();)
	{
		if (mVideo_Modes[i].bitsPerPixel != 32 || mVideo_Modes[i].width == 720)
		{
			std::vector<sf::VideoMode>::iterator it = mVideo_Modes.end() - 1;	//	Indice must be on the last element;
			std::swap(*it, mVideo_Modes[i]);
			mVideo_Modes.pop_back();
		}
		else
			i++;	
	}
	mVideo_Modes.shrink_to_fit();
	//	Must sort!
	std::sort(mVideo_Modes.begin(), mVideo_Modes.end(), std::greater<sf::VideoMode>());
}
//--------------------------//
//--------------------------//
//
const sf::VideoMode Data::getVideo_Mode() const
{
	return mVideo_Modes[mVideoModeIndex];
}
//--------------------------//
//--------------------------//
//
const sf::VideoMode	Data::getVideo_Mode(UINT custom_index) const
{
	return mVideo_Modes[custom_index];
};
//--------------------------//
//--------------------------//
//
const UINT Data::getNumber_of_Video_Modes() const
{
	return mVideo_Modes.size() - 1;
}
//--------------------------//
//--------------------------//
//
const UINT Data::getCurrent_VM_Index() const
{
	return mVideoModeIndex;
}
//--------------------------//
//--------------------------//
//
void Data::Update_Window(UINT num)
{
	if (num > mVideo_Modes.size())
	{
		std::cerr << "Indice is bigger than the container size!\nSetting indice on the last element...";
		mVideoModeIndex = mVideo_Modes.size() - 1;		
	}
	else
		mVideoModeIndex = num;
	
	//	Refresh AA;
	mSettings.antialiasingLevel = mAntiAliasing[mAA_Index];


	if (mIsFullscreen)
	{
		mWindow.create(sf::VideoMode(mVideo_Modes[mVideoModeIndex]), "GSM", sf::Style::Fullscreen, mSettings);
	}
	else
	{
		mWindow.create(sf::VideoMode(mVideo_Modes[mVideoModeIndex]), "GSM", sf::Style::Close, mSettings);
	}
	mWindow.setVerticalSyncEnabled(mVsync);
	mWindow.setMouseCursorVisible(setHardwareCursorOnOff);

	mScaleCoefficient = mVideo_Modes[mVideoModeIndex].height / static_cast<float>(1024);

	mMouse_Cursor.setTexture(mResources.getTexture(ID_Global));
	mMouse_Cursor.setTextureRect(sf::IntRect(0, 0, 13, 20));
	mMouse_Cursor.setScale(mScaleCoefficient, mScaleCoefficient);
}

void Data::update_cursor()
{
	mMouse_Cursor.setPosition(static_cast<sf::Vector2f>(mMouseCoordinates));
}

const sf::Sprite& Data::getMouse_Cursor() const
{
	return mMouse_Cursor;
}

void Data::center_Cursor_Origin(bool param)
{
	if (param)
	{
		sf::FloatRect bounds = mMouse_Cursor.getLocalBounds();
		mMouse_Cursor.setOrigin(bounds.width / 2, bounds.height / 2);
	}
	else
	{
		mMouse_Cursor.setOrigin(0,0);
	}
}

void Data::change_Cursor(sf::IntRect param)
{
	mMouse_Cursor.setTextureRect(param);
}
