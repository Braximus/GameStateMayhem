#include "stdafx.h"
#include "Menu_Data.h"
#include "DataStorage.h"

MenuData::MenuData(Data& param)
	: mData(param)
	, mRes(param.getResources())
{
	
	//	Ucitaj Resorse:
	mRes.LoadTexture("Teksture/Meni_Teksture.png", ID_Menu);
	mRes.LoadSound("Sounds/Menu/Hover.wav");
	mRes.LoadSound("Sounds/Menu/Select.wav");
	mRes.LoadSound("Sounds/Menu/Escape.wav");

	sf::Sound snd;
	snd.setVolume(mRes.getSoundVolume());
	
	snd.setBuffer(mRes.getSoundBuffer("Sounds/Menu/Hover.wav"));
	mSounds.insert(std::pair<Menus::Sounds, sf::Sound>(Menus::snd_Hover, snd));

	snd.setBuffer(mRes.getSoundBuffer("Sounds/Menu/Select.wav"));
	mSounds.insert(std::pair<Menus::Sounds, sf::Sound>(Menus::snd_Select, snd));

	snd.setBuffer(mRes.getSoundBuffer("Sounds/Menu/Escape.wav"));
	mSounds.insert(std::pair<Menus::Sounds, sf::Sound>(Menus::snd_Escape, snd));

	refresh();
	mRefreshed = true;
}


MenuData::~MenuData()
{
	mRes.UnloadTexture(ID_Menu);
	mSounds.clear();
	mRes.UnloadSounds();
}


void MenuData::refresh()
{
	mChar_Sizes.clear();
	mObject_Sizes.clear();
	mDistances.clear();
	mKeyPositions.clear();
	mVideo_mode_names.clear();

	//	Namesti kopije razmera, radi lakse distribucije:
	mScale_coef = mData.getScaleCoefficient();
	//	Namesti velicine slova:
	mChar_Sizes.insert(std::pair<Menus::Char_sizes, float>(Menus::ch_Small, 16 * mScale_coef));
	mChar_Sizes.insert(std::pair<Menus::Char_sizes, float>(Menus::ch_Medium, 32 * mScale_coef));
	mChar_Sizes.insert(std::pair<Menus::Char_sizes, float>(Menus::ch_Large, 48 * mScale_coef));
	//	Namesti velicine objekata:
	float line_spacing_sml = mData.getResources().getFont(ID_Global).getLineSpacing(mChar_Sizes.at(Menus::ch_Small));
	float line_spacing_med = mData.getResources().getFont(ID_Global).getLineSpacing(mChar_Sizes.at(Menus::ch_Medium));
	float line_spacing_lrg = mData.getResources().getFont(ID_Global).getLineSpacing(mChar_Sizes.at(Menus::ch_Large));

	mObject_Sizes.insert(std::pair<Menus::Objects_sizes, sf::Vector2f>(Menus::size_Button, sf::Vector2f(315 * mScale_coef, line_spacing_med)));
	mObject_Sizes.insert(std::pair<Menus::Objects_sizes, sf::Vector2f>(Menus::size_MiniButton, sf::Vector2f(35 * mScale_coef, line_spacing_med)));
	mObject_Sizes.insert(std::pair<Menus::Objects_sizes, sf::Vector2f>(Menus::size_Label, sf::Vector2f(315 * mScale_coef, line_spacing_med)));
	mObject_Sizes.insert(std::pair<Menus::Objects_sizes, sf::Vector2f>(Menus::size_HugeLabel, sf::Vector2f(400, 400)* mScale_coef));	//	Ovde ce eventualno trebati prepravke.
	mObject_Sizes.insert(std::pair<Menus::Objects_sizes, sf::Vector2f>(Menus::size_Title, sf::Vector2f(500, 200)* mScale_coef));
	mObject_Sizes.insert(std::pair<Menus::Objects_sizes, sf::Vector2f>(Menus::size_Drop_Down_Menu, sf::Vector2f(250 * mScale_coef, line_spacing_med)));
	//	Namesti rastojanja:
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_VeryNear, 5 * mScale_coef));
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_Near, 15 * mScale_coef));
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_Medium, 50 * mScale_coef));
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_Long, 75 * mScale_coef));
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_Far, 100 * mScale_coef));
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_VeryFar, 200 * mScale_coef));
	mDistances.insert(std::pair<Menus::Distances, float>(Menus::dis_ExtremlyFar, 300 * mScale_coef));
	//	Namesti kljucne pozicije:
	float	width = mData.getVideo_Mode().width;
	float	height = mData.getVideo_Mode().height;

	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_TopLeft_Corner, sf::Vector2f(0, 0)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_TopRight_Corner, sf::Vector2f(width, 0)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_BottomLeft_Corner, sf::Vector2f(0, height)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_BottomRight_Corner, sf::Vector2f(width, height)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_Screen, sf::Vector2f(width / 2, height / 2)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_LeftHalf_Screen, sf::Vector2f(width / 4, height / 2)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_RightHalf_Screen, sf::Vector2f(3 * width / 4, height / 2)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_UpperHalf_Screen, sf::Vector2f(width / 2, height / 4)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_BottomHalf_Screen, sf::Vector2f(width / 2, 3 * height / 4)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_TopLeft_Quarter, sf::Vector2f(width / 4, height / 4)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_TopRight_Quarter, sf::Vector2f(3 * width / 4, height / 4)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_BottomLeft_Quarter, sf::Vector2f(width / 4, 3 * height / 4)));
	mKeyPositions.insert(std::pair<Menus::Key_positions, sf::Vector2f>(Menus::kp_Center_BottomRight_Quarter, sf::Vector2f(3 * width / 4, 3 * height / 4)));
	//	
	for (UINT i = 0; i <= mData.getNumber_of_Video_Modes(); ++i)
	{
		mVideo_mode_names.push_back(" " + std::to_string(mData.getVideo_Mode(i).width) + "x" + std::to_string(mData.getVideo_Mode(i).height));
	}
	for (UINT i = 0; i < 5; ++i)
	{
		UINT a = std::pow(2, i);
		if (a == 1)
			mAA_levels.push_back(" 0");
		else
		{
			mAA_levels.push_back(" " + std::to_string(a));
		}

	}
	mCheck_tex_rects.push_back(sf::IntRect(500, 400, 115, 115));
	mCheck_tex_rects.push_back(sf::IntRect(620, 400, 115, 115));
	mCheck_tex_rects.push_back(sf::IntRect(500, 520, 115, 115));
	mCheck_tex_rects.push_back(sf::IntRect(620, 520, 115, 115));

}

void MenuData::Play_Sound(Menus::Sounds param)
{
	if (mSounds.at(param).getStatus() != sf::Sound::Playing && mData.getResources().IsSoundOn())
	{
		mSounds.at(param).play();
	}
}

MusicPlayer& MenuData::getMusicPlayer()
{
	return mData.getMusic_Player();
}

void MenuData::ChangeSubState(Menus::SubStates	param)
{
	mCurrentSubState = param;
}

void MenuData::ChangeState(eState param)
{
	mData.ChangeState(param);
}

void MenuData::Close()
{
	mData.Close();
}

const sf::Vector2i MenuData::MouseCoord() const
{
	return mData.mMouseCoordinates;
}

Resources& MenuData::getResources()
{
	return mRes;
}

const Menus::SubStates MenuData::getCurrentSubState() const
{
	return mCurrentSubState;
}

const float MenuData::getScale_coef() const
{
	return mScale_coef;
}

//const sf::Vector2f MenuData::getScaled_positions() const
//{
//	return mScaled_positions;
//}

const float MenuData::getMenu_Char_Sizes(Menus::Char_sizes param) const
{
	return mChar_Sizes.at(param);
}

const sf::Vector2f MenuData::getMenu_Object_Sizes(Menus::Objects_sizes param) const
{
	return mObject_Sizes.at(param);
}

const float MenuData::getMenu_Distances(Menus::Distances param) const
{
	return mDistances.at(param);
}

const sf::Vector2f MenuData::getMenu_Key_Positions(Menus::Key_positions param) const
{
	return mKeyPositions.at(param);
}

const std::vector<std::string>& MenuData::get_Video_mode_names_cont() const
{
	return mVideo_mode_names;
}

const std::vector<std::string>& MenuData::get_AA_levels_cont() const
{
	return mAA_levels;
}

const std::vector<sf::IntRect>& MenuData::get_Check_tex_rects() const
{
	return mCheck_tex_rects;
}