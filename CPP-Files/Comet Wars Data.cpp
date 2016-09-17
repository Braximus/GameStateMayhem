#include "stdafx.h"
#include "Comet Wars Data.h"

CometWarsData::CometWarsData(Data& dat)
	:mData(dat)
{
	mData.getResources().LoadTexture("Teksture/Comets.png", ID_CometWars);
	
	mData.getResources().LoadSound("Sounds/Menu/Hover.wav");
	mData.getResources().LoadSound("Sounds/Menu/Select.wav");
	mData.getResources().LoadSound("Sounds/Menu/Escape.wav");
	
	mData.getResources().LoadSound("Sounds/Comet Wars/CometBigDead.wav");
	mData.getResources().LoadSound("Sounds/Comet Wars/Hit.wav");
	mData.getResources().LoadSound("Sounds/Comet Wars/LaserFire.wav");
	mData.getResources().LoadSound("Sounds/Comet Wars/PlayerShieldUp.wav");
	mData.getResources().LoadSound("Sounds/Comet Wars/PlayerShieldDown.wav");
	mData.getResources().LoadSound("Sounds/Comet Wars/PlayerShipDestroyed.wav");

	sf::Sound	snd;
	snd.setVolume(mData.getResources().getSoundVolume());	

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Menu/Hover.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_Hover, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Menu/Select.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_Select, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Menu/Escape.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_Escape, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Comet Wars/CometBigDead.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_CometBigDead, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Comet Wars/Hit.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_Hit, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Comet Wars/LaserFire.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_LaserFire, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Comet Wars/PlayerShieldUp.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_PlayerShieldUp, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Comet Wars/PlayerShieldDown.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_PlayerShieldDown, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Comet Wars/PlayerShipDestroyed.wav"));
	mSounds.insert(std::pair<CW::Sounds, sf::Sound>(CW::snd_PlayerShipDestroyed, snd));
	
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	random_generator.seed(seed);

	mScale_coefficient = mData.getScaleCoefficient();

	mScore = 0;
	
	float Screen_width = mData.getVideo_Mode().width;		
	float Screen_height = mData.getVideo_Mode().height;		
	//		Key positions:
	mKey_Positions.insert(std::pair<CW::Key_Positions, sf::Vector2f>(CW::kp_TopLeft, sf::Vector2f(0, 0)));
	mKey_Positions.insert(std::pair<CW::Key_Positions, sf::Vector2f>(CW::kp_TopRight, sf::Vector2f(Screen_width, 0)));
	mKey_Positions.insert(std::pair<CW::Key_Positions, sf::Vector2f>(CW::kp_BottomLeft, sf::Vector2f(0, Screen_height)));
	mKey_Positions.insert(std::pair<CW::Key_Positions, sf::Vector2f>(CW::kp_BottomRight, sf::Vector2f(Screen_width, Screen_height)));
	mKey_Positions.insert(std::pair<CW::Key_Positions, sf::Vector2f>(CW::kp_Center, sf::Vector2f(Screen_width/2, Screen_height / 2)));
	//		Distances:
	mDistances.insert(std::pair<CW::Distances, float>(CW::dis_Close, 3 * mScale_coefficient));
	mDistances.insert(std::pair<CW::Distances, float>(CW::dis_Near, 10 * mScale_coefficient));
	mDistances.insert(std::pair<CW::Distances, float>(CW::dis_Medium, 25 * mScale_coefficient));
	mDistances.insert(std::pair<CW::Distances, float>(CW::dis_Far, 50 * mScale_coefficient));
	//		Character sizes:
	mCharacter_sizes.insert(std::pair<CW::Character_size, float>(CW::ch_Small, 18 * mScale_coefficient));
	mCharacter_sizes.insert(std::pair<CW::Character_size, float>(CW::ch_Medium, 30 * mScale_coefficient));
	mCharacter_sizes.insert(std::pair<CW::Character_size, float>(CW::ch_Large, 72 * mScale_coefficient));
	//		
	float UI_Area_height = 50 * mScale_coefficient;
	float border_depth = 50 * mScale_coefficient;

	float y_offset = 5 * mScale_coefficient;
	float lives_offset = 2 * mScale_coefficient;
	//	Object sizes:
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Ship, sf::Vector2f(24, 30) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Comet, sf::Vector2f(50, 50) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Mini_Comet, sf::Vector2f(25, 25) * mScale_coefficient));

	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Rear_Comet, sf::Vector2f(70, 70) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Rear_Mini_Comet, sf::Vector2f(25, 25) * mScale_coefficient));

	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Projectile, sf::Vector2f(2.5,2.5) * mScale_coefficient));		
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Shield, sf::Vector2f(24, 24) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_UI_Area, sf::Vector2f(Screen_width, UI_Area_height)));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Countdown, sf::Vector2f(300, 600) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_SplashScreen, sf::Vector2f(400, 200) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Pause_Area, sf::Vector2f(350, 250) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Pause_Button, sf::Vector2f(315, 50) * mScale_coefficient));
	mSizes.insert(std::pair<CW::Components_size, sf::Vector2f>(CW::size_Battery, sf::Vector2f(20, 30) * mScale_coefficient));
	
	//	Interface position:
	mUI_Positions.insert(std::pair<CW::UI_Components, sf::Vector2f>(CW::UI_Area, sf::Vector2f(0, Screen_height - UI_Area_height)));
	//	Rest of interface objects are taking the position in relation to the area!
	mUI_Positions.insert(std::pair<CW::UI_Components, sf::Vector2f>(CW::UI_Score, sf::Vector2f(0 + y_offset, mUI_Positions.at(CW::UI_Area).y + y_offset)));
	mUI_Positions.insert(std::pair<CW::UI_Components, sf::Vector2f>(CW::UI_Lives, sf::Vector2f(mSizes.at(CW::size_UI_Area).x - (mSizes.at(CW::size_Ship).x + lives_offset), mUI_Positions.at(CW::UI_Area).y + 2 * y_offset)));
	mUI_Positions.insert(std::pair<CW::UI_Components, sf::Vector2f>(CW::UI_Text_Flash, sf::Vector2f(mSizes.at(CW::size_UI_Area).x / 2, mUI_Positions.at(CW::UI_Area).y + y_offset)));

	//	Borders (I could just put one sf::FloatRect over the window, but I like to complicate things :P 
	mZones.insert(std::pair<CW::Zones, sf::FloatRect>(CW::z_Top, sf::FloatRect(-border_depth, 0, Screen_width + border_depth, -border_depth)));
	mZones.insert(std::pair<CW::Zones, sf::FloatRect>(CW::z_Right, sf::FloatRect(Screen_width, -border_depth, border_depth, Screen_height - mSizes.at(CW::size_UI_Area).y + border_depth)));
	mZones.insert(std::pair<CW::Zones, sf::FloatRect>(CW::z_Bottom, sf::FloatRect(Screen_width + border_depth, Screen_height -mSizes.at(CW::size_UI_Area).y, -1 * (Screen_width + border_depth), border_depth)));
	mZones.insert(std::pair<CW::Zones, sf::FloatRect>(CW::z_Left, sf::FloatRect(0, Screen_height + border_depth -mSizes.at(CW::size_UI_Area).y, -border_depth, -1 * (Screen_height -mSizes.at(CW::size_UI_Area).y + border_depth))));
	//-------------------------------------------------------------------------------------//

	//	Speeds:
	mSpeed.insert(std::pair<CW::Object_Speed, float>(CW::speed_Ship, 300 * mScale_coefficient));
	mSpeed.insert(std::pair<CW::Object_Speed, float>(CW::speed_Asteroid, 250 * mScale_coefficient));
	mSpeed.insert(std::pair<CW::Object_Speed, float>(CW::speed_Mini_Asteroid, 400 * mScale_coefficient));
	mSpeed.insert(std::pair<CW::Object_Speed, float>(CW::speed_Projectile, 1200 * mScale_coefficient));
	mSpeed.insert(std::pair<CW::Object_Speed, float>(CW::speed_Rear_Comet, 50 * mScale_coefficient));
	//	Texts:
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_Score, "Score: "));
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_Win, " You Won!!!\n Press any key to\n exit "));
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_Loose, "You Lost...\n Better luck\n next time "));
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_Text_Flash, "Shields active! Can not fire! "));
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_Continue_Button, " Continue "));
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_NewGame_Button, " New Game "));
	mTexts.insert(std::pair<CW::Texts, std::string>(CW::txt_Exit_Button, " Exit "));
	//--------------------------------------------------------------------------------//
	//	Texture coordinates for big comets:
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type1_Major, sf::IntRect(0, 0, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type2_Major, sf::IntRect(0, 50, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type3_Major, sf::IntRect(0, 100, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type4_Major, sf::IntRect(0, 150, 50, 50)));
	//	Texture coordinates for small comets:
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type1_Minor, sf::IntRect(200, 150, 25, 25)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type2_Minor, sf::IntRect(225, 150, 25, 25)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type3_Minor, sf::IntRect(250, 150, 25, 25)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type4_Minor, sf::IntRect(275, 150, 25, 25)));		// Poslednji u prvom redu teksture
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type5_Minor, sf::IntRect(200, 175, 25, 25)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type6_Minor, sf::IntRect(225, 175, 25, 25)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type7_Minor, sf::IntRect(250, 175, 25, 25)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Type8_Minor, sf::IntRect(275, 175, 25, 25)));		// Poslednji u drugom redu teksture
	//	Texture coordinates for background comets:
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type1_Major, sf::IntRect(0, 200, 100, 100)));		
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type2_Major, sf::IntRect(0, 300, 100, 100)));		
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type3_Major, sf::IntRect(0, 400, 100, 100)));		
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type4_Major, sf::IntRect(100, 200, 100, 100)));		
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type5_Major, sf::IntRect(100, 300, 100, 100)));	
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type6_Major, sf::IntRect(100, 400, 100, 100)));		
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type1_Minor, sf::IntRect(200, 200, 50, 50)));		
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type2_Minor, sf::IntRect(200, 250, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type3_Minor, sf::IntRect(200, 300, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type4_Minor, sf::IntRect(200, 350, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type5_Minor, sf::IntRect(200, 400, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type6_Minor, sf::IntRect(200, 450, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type7_Minor, sf::IntRect(250, 200, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type8_Minor, sf::IntRect(250, 250, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type9_Minor, sf::IntRect(250, 300, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type10_Minor, sf::IntRect(250, 350, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type11_Minor, sf::IntRect(250, 400, 50, 50)));
	mComet_Texture_rects.insert(std::pair<CW::AsteroidType, sf::IntRect>(CW::com_Rear_Type12_Minor, sf::IntRect(250, 450, 50, 50)));
	//	Texture coordinates for player ship:
	mShip_Texture_rects.insert(std::pair<CW::ShipType, sf::IntRect>(CW::ship_Type1, sf::IntRect(210, 50, 24, 30)));
	mShip_Texture_rects.insert(std::pair<CW::ShipType, sf::IntRect>(CW::ship_Type2, sf::IntRect(240, 50, 24, 30)));
	mShip_Texture_rects.insert(std::pair<CW::ShipType, sf::IntRect>(CW::ship_Type3, sf::IntRect(270, 50, 24, 30)));
	//	Texture coordinates for miscelaneous objects:
	mMisc_Texture_rects.insert(std::pair<CW::Misc_Tex_rects, sf::IntRect>(CW::msc_Battery, sf::IntRect(210, 90, 20, 30)));

	mCurrentSubState = CW::sub_Start;
	mLives = 3;
}
//
CometWarsData::~CometWarsData()
{
	mData.getResources().UnloadTexture(ID_CometWars);
	mSounds.clear();
	mData.getResources().UnloadSounds();
}
//
//	Operations:
//
void CometWarsData::update_mouse()
{
	mMouse_Coordinates = static_cast<sf::Vector2f>(mData.mMouseCoordinates);
}
//
void CometWarsData::change_Cursor(sf::IntRect param)
{
	mData.change_Cursor(param);
}
//
bool CometWarsData::setEnd()
{
	if (mNumber_of_Ast == 0)
	{
		mEndType = CW::eVictory;
		return true;
	}
	else if (mLives == 0)
	{
		mEndType = CW::eDefeat;
		return true;
	}
	else
	{
		mEndType = CW::eNone;
		return false;
	}
}
//
void CometWarsData::ChangeSubState(CW::SubStates new_State)
{
	mCurrentSubState = new_State;

	if (mCurrentSubState == CW::sub_Play)
	{
		mData.lock_cursor = true;
		change_Cursor(sf::IntRect(0, 21, 20, 20));
		mData.center_Cursor_Origin(true);
	}
	else
	{
		mData.lock_cursor = false;
		change_Cursor(sf::IntRect(0, 0, 13, 20));
		mData.center_Cursor_Origin(false);
	}


}
//
void CometWarsData::setNumber_of_Comets(UINT param)
{
	mNumber_of_Ast = param;
}
//
void CometWarsData::change_Score(UINT param)
{
	mScore += param;
}
//
void CometWarsData::remove_life()
{
	mLives--;
	if (mLives <= 0)
	{
		mLives = 0;
	}
}
//
void CometWarsData::Exit()
{
	mData.ChangeState(e_Menu);
}
//
void CometWarsData::Restart()
{
	mScore = 0;
	mLives = 3;
	mEndType = CW::eNone;
}
//
void CometWarsData::Play_Sound(CW::Sounds param)
{
	if (mData.getResources().IsSoundOn())
	{
		mSounds.at(param).play();
	}
}
//
//	Getter Functions:
//
const CW::SubStates CometWarsData::getCurrentSubState() const
{
	return mCurrentSubState;
}
//
Resources& CometWarsData::getResources()
{
	return mData.getResources();
}
//
const sf::Vector2f CometWarsData::getMouse_position() const
{
	return mMouse_Coordinates;
}
//
std::default_random_engine& CometWarsData::get_random_engine()
{
	return random_generator;
}
//
const sf::Vector2f CometWarsData::getKey_Position(CW::Key_Positions param)
{
	return mKey_Positions.at(param);
}
//
const float CometWarsData::getCharacter_Size(CW::Character_size param)
{
	return mCharacter_sizes.at(param);
}
//
const float CometWarsData::getDistance(CW::Distances param)
{
	return mDistances.at(param);
}
//
const float CometWarsData::getScale_Coefficient()
{
	return mScale_coefficient;
}
//
const std::string CometWarsData::getText(CW::Texts param)
{
	return mTexts.at(param);
}
//
const sf::Vector2f CometWarsData::getUI_Position(CW::UI_Components param) const
{
	return mUI_Positions.at(param);
}
//
const sf::FloatRect CometWarsData::getZone(CW::Zones param)
{
	return mZones.at(param);
}
//
const UINT CometWarsData::getScore() const
{
	return mScore;
}
//
const std::map<CW::Zones, sf::FloatRect>& CometWarsData::getZone_map()
{
	return mZones;
}
//
const sf::Vector2f CometWarsData::getObj_Sizes(CW::Components_size param) const
{
	return mSizes.at(param);
}
//
const sf::IntRect CometWarsData::getComet_Texture_rect(CW::AsteroidType param) const
{
	return mComet_Texture_rects.at(param);
}
//
const sf::IntRect CometWarsData::getShip_Texture_rect(CW::ShipType param) const
{
	return mShip_Texture_rects.at(param);
}
//
const sf::IntRect CometWarsData::getMisc_Texture_rect(CW::Misc_Tex_rects param) const
{
	return mMisc_Texture_rects.at(param);
}
//
const UINT CometWarsData::getNumber_of_Comets() const
{
	return mNumber_of_Ast;
}
//
const int CometWarsData::getNumber_of_Lives() const
{
	return mLives;
}
//
const float CometWarsData::getSpeed(CW::Object_Speed param) const
{
	return mSpeed.at(param);
}
//
MusicPlayer& CometWarsData::getMusicPlayer()
{
	return mData.getMusic_Player();
}
