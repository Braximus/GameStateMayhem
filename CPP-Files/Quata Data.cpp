#include "stdafx.h"
#include "Quata Data.h"

QuataData::QuataData(Data& data)
	:mData(data)
{
	seed = std::chrono::system_clock::now().time_since_epoch().count();
	random_generator.seed(seed);
	float scale_coef = mData.getScaleCoefficient();
	mData.getResources().LoadTexture("Teksture/Quata_Teksture.bmp", ID_Quata);
	mData.getResources().LoadTexture("Teksture/Quata Table Texture.png", ID_Quata_table);
	mData.getResources().LoadSound("Sounds/Quata/OpponentBallbounce.wav");
	mData.getResources().LoadSound("Sounds/Quata/OpponentScore.wav");
	mData.getResources().LoadSound("Sounds/Quata/PlayerBall bounce.wav");
	mData.getResources().LoadSound("Sounds/Quata/PlayerLose.wav");
	mData.getResources().LoadSound("Sounds/Quata/PlayerScore.wav");
	mData.getResources().LoadSound("Sounds/Quata/WallBallbounce.wav");
	mData.getResources().LoadSound("Sounds/Menu/Hover.wav");
	mData.getResources().LoadSound("Sounds/Menu/Select.wav");
	mData.getResources().LoadSound("Sounds/Menu/Escape.wav");
	sf::Sound snd;
	snd.setVolume(mData.getResources().getSoundVolume());

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Quata/OpponentBallbounce.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Opponent_Ball_bounce, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Quata/OpponentScore.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Opponent_Score, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Quata/PlayerBall bounce.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Player_Ball_bounce, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Quata/PlayerLose.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Player_Loose, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Quata/PlayerScore.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Player_Score, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Quata/WallBallbounce.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Wall_Ball_bounce, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Menu/Hover.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Hover, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Menu/Select.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Select, snd));

	snd.setBuffer(mData.getResources().getSoundBuffer("Sounds/Menu/Escape.wav"));
	mSounds.insert(std::pair<Qua::Sounds, sf::Sound>(Qua::snd_Escape, snd));

	float x = mData.getVideo_Mode().width;
	float y = mData.getVideo_Mode().height;
	//	Key positions:
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_TopLeft_Corner, sf::Vector2f(0, 0)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_TopRight_Corner, sf::Vector2f(x, 0)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_BottomLeft_Corner, sf::Vector2f(0, y)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_BottomRight_Corner, sf::Vector2f(x, y)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_Center_Screen, sf::Vector2f(x / 2, y / 2)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_LeftCenter_Screen, sf::Vector2f(0, y / 2)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_RightCenter_Screen, sf::Vector2f(x, y / 2)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_UpperCenter_Screen, sf::Vector2f(x / 2, 0)));
	Key_Positions.insert(std::pair<Qua::Quata_Key_Positions, sf::Vector2f>(Qua::kp_BottomCenter_Screen, sf::Vector2f(x / 2, y)));
	//	Character sizes:
	Character_Sizes.insert(std::pair<Qua::Quata_Char_Sizes, float>(Qua::ch_Small, 16 * scale_coef));
	Character_Sizes.insert(std::pair<Qua::Quata_Char_Sizes, float>(Qua::ch_Medium, 32 * scale_coef));
	Character_Sizes.insert(std::pair<Qua::Quata_Char_Sizes, float>(Qua::ch_Large, 48 * scale_coef));
	//	Object sizes:
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_Paddle, sf::Vector2f(15, 75) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_Ball, sf::Vector2f(12, 0) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_Playground, sf::Vector2f(1150, 700) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_SplashScreen, sf::Vector2f(300, 150) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_Button, sf::Vector2f(315, 40) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_Pause_Area, sf::Vector2f(500, 300) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_LineThickness, sf::Vector2f(5, 5) * scale_coef));
	Object_Sizes.insert(std::pair<Qua::Quata_Obj_Sizes, sf::Vector2f>(Qua::size_Playground_texture, sf::Vector2f(100, 50) * scale_coef));
	//	Distances:
	Distances.insert(std::pair<Qua::Quata_Distances, float>(Qua::dis_VeryNear, 10 * scale_coef));
	Distances.insert(std::pair<Qua::Quata_Distances, float>(Qua::dis_Near, 30 * scale_coef));
	Distances.insert(std::pair<Qua::Quata_Distances, float>(Qua::dis_Medium, 50 * scale_coef));
	Distances.insert(std::pair<Qua::Quata_Distances, float>(Qua::dis_Far, 100 * scale_coef));
	Distances.insert(std::pair<Qua::Quata_Distances, float>(Qua::dis_VeryFar, 200 * scale_coef));
	//	Temporary vectors:
	sf::Vector2f centar = Key_Positions.at(Qua::kp_Center_Screen);
	sf::Vector2f nivo = Object_Sizes.at(Qua::size_Playground);
	sf::Vector2f polovina_nivoa = sf::Vector2f(Object_Sizes.at(Qua::size_Playground).x / 2, Object_Sizes.at(Qua::size_Playground).y / 2);
	sf::Vector2f debljina_linije = Object_Sizes.at(Qua::size_LineThickness);
	//	Zones
	Zones.insert(std::pair<Qua::Quata_Zones, sf::FloatRect>(Qua::z_UpperPlayField, sf::FloatRect(centar.x - polovina_nivoa.x, centar.y - polovina_nivoa.y, nivo.x, debljina_linije.y )));
	Zones.insert(std::pair<Qua::Quata_Zones, sf::FloatRect>(Qua::z_BottomPlayField, sf::FloatRect(centar.x - polovina_nivoa.x, centar.y + polovina_nivoa.y, nivo.x, -debljina_linije.y)));
	Zones.insert(std::pair<Qua::Quata_Zones, sf::FloatRect>(Qua::z_LeftPlayField, sf::FloatRect(centar.x - polovina_nivoa.x - debljina_linije.x, centar.y - polovina_nivoa.y, debljina_linije.x, nivo.y)));
	Zones.insert(std::pair<Qua::Quata_Zones, sf::FloatRect>(Qua::z_RightPlayField, sf::FloatRect(centar.x + polovina_nivoa.x + debljina_linije.x, centar.y - polovina_nivoa.y, -debljina_linije.x, nivo.y)));
	//	Speeds
	Speeds.insert(std::pair<Qua::Quata_Speeds, float>(Qua::speed_Ball_nominal, 350*scale_coef));
	Speeds.insert(std::pair<Qua::Quata_Speeds, float>(Qua::speed_Ball_increase, 50 * scale_coef));
	Speeds.insert(std::pair<Qua::Quata_Speeds, float>(Qua::speed_Ball_max, 1000 * scale_coef));
	Speeds.insert(std::pair<Qua::Quata_Speeds, float>(Qua::speed_Paddle, 400 * scale_coef));
	//	Texts
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Start, " Press 'Enter' \n\tto start!"));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Win, "\t\tYou Won!!! \n Congratulations! "));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Loose, "\t\t\tYou Lost... \n Better luck \n next time! "));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Player1_name, "Player"));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Player2_name, "Computer"));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Continue_button, " Continue"));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_Exit_button, " Exit"));
	Texts.insert(std::pair<Qua::Quata_Texts, std::string>(Qua::txt_New_button, " New Game"));
	//	Texture coordinates
	Texture_rects.insert(std::pair<Qua::Quata_Texture_rects, sf::IntRect>(Qua::intrect_Player, sf::IntRect(0, 0, 15, 100)));
	Texture_rects.insert(std::pair<Qua::Quata_Texture_rects, sf::IntRect>(Qua::intrect_AI, sf::IntRect(16, 0, 15, 100)));
	Texture_rects.insert(std::pair<Qua::Quata_Texture_rects, sf::IntRect>(Qua::intrect_Ball, sf::IntRect(281, 0, 39, 35)));
	Texture_rects.insert(std::pair<Qua::Quata_Texture_rects, sf::IntRect>(Qua::intrect_Background1, sf::IntRect(40, 0, 100, 50)));
	//	Score
	Scores.insert(std::pair<Qua::Quata_UI_Components, UINT>(Qua::cu_Score1, 0));
	Scores.insert(std::pair<Qua::Quata_UI_Components, UINT>(Qua::cu_Score2, 0));
	//
	mCurrentSubState = Qua::Start;
}
//
QuataData::~QuataData()
{
	mData.getResources().UnloadTexture(ID_Quata);
	mSounds.clear();
	mData.getResources().UnloadSounds();
}
//
const sf::Vector2f QuataData::get_Mouse_Coordinates() const
{
	return Mouse_Coordinates;
}
//
void QuataData::update_mouse()
{
	Mouse_Coordinates = static_cast<sf::Vector2f>(mData.mMouseCoordinates);
}
//
void QuataData::changeSubState(Qua::SubState sState)
{
	mCurrentSubState = sState;
}
//
void QuataData::Exit()
{
	mData.ChangeState(e_Menu);
}
//
void QuataData::set_Texts(const Qua::Quata_Texts param1, std::string param2)
{
	Texts.at(param1) = param2;
}
//
void QuataData::set_Score(const Qua::Quata_UI_Components param1, UINT param2)
{
	Scores.at(param1) = param2;
}
//
void QuataData::Play_Sound(Qua::Sounds param)
{
	if (mSounds.at(param).getStatus() != sf::Sound::Playing && mData.getResources().IsSoundOn())
	{
		mSounds.at(param).play();
	}
}
//
bool QuataData::victory()
{
	if (Scores.at(Qua::cu_Score1) == 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//
const sf::Vector2f QuataData::get_Object_Size(Qua::Quata_Obj_Sizes param) const
{
	return Object_Sizes.at(param);
}
//
const sf::Vector2f QuataData::get_Key_Position(Qua::Quata_Key_Positions param) const
{
	return Key_Positions.at(param);
}
//
const float QuataData::get_Character_Size(Qua::Quata_Char_Sizes param) const
{
	return Character_Sizes.at(param);
}
//
const float QuataData::get_Distance(Qua::Quata_Distances param) const
{
	return Distances.at(param);
}
//
const float QuataData::get_Speed(Qua::Quata_Speeds param) const
{
	return Speeds.at(param);
}
//
const sf::FloatRect QuataData::get_Zone(Qua::Quata_Zones param) const
{
	return Zones.at(param);
}
//
const std::string QuataData::get_Text(Qua::Quata_Texts param) const
{
	return Texts.at(param);
}
//
const sf::IntRect QuataData::get_Texture_rects(Qua::Quata_Texture_rects param) const
{
	return Texture_rects.at(param);
}
//
const UINT QuataData::get_Score(Qua::Quata_UI_Components param) const
{
	return Scores.at(param);
}
//
const Qua::SubState QuataData::getCurrentSubstate() const
{
	return mCurrentSubState;
}
//
Resources& QuataData::get_Resources()
{
	return mData.getResources();
}
//
std::default_random_engine& QuataData::get_Random_Engine()
{
	return random_generator;
}

MusicPlayer& QuataData::getMusicPlayer()
{
	return mData.getMusic_Player();
}
