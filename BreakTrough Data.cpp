#include "stdafx.h"
#include "BreakTrough Data.h"

BreakTrough_Data::BreakTrough_Data(Data& data)
	:m_Data(data)
{
	m_Data.getResources().LoadTexture("Texture/BreakTrough.png", ID_BreakTrough);

	m_Data.getResources().LoadSound("Sounds/Menu/Hover.wav");
	m_Data.getResources().LoadSound("Sounds/Menu/Select.wav");
	m_Data.getResources().LoadSound("Sounds/Menu/Escape.wav");

	m_Data.getResources().LoadSound("Sounds/BreakTrough/Block hit.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Paddle hit.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Player loose.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/PowerUp lost.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/PowerUp taken.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Wall hit.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Laser Fire.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Victory.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Game Over.wav");
	m_Data.getResources().LoadSound("Sounds/BreakTrough/Level Start.wav");

	m_CurrentSubState = Break::SubSt_StartMission;

	float m_Scale_Coefficient = data.getScaleCoefficient();
	float x = data.getVideo_Mode().width;
	float y = data.getVideo_Mode().height;

	//	Key positions
	m_Key_Positions.insert(std::pair<Break::Key_Positions, sf::Vector2f>(Break::kp_TopLeft, sf::Vector2f(0, 0)));
	m_Key_Positions.insert(std::pair<Break::Key_Positions, sf::Vector2f>(Break::kp_TopRight, sf::Vector2f(x, 0)));
	m_Key_Positions.insert(std::pair<Break::Key_Positions, sf::Vector2f>(Break::kp_BottomLeft, sf::Vector2f(0, y)));
	m_Key_Positions.insert(std::pair<Break::Key_Positions, sf::Vector2f>(Break::kp_BottomRight, sf::Vector2f(x, y)));
	m_Key_Positions.insert(std::pair<Break::Key_Positions, sf::Vector2f>(Break::kp_Center, sf::Vector2f(x/2, y/2)));
	//	Character sizes
	m_Character_Sizes.insert(std::pair<Break::Character_sizes, float>(Break::ch_Small, 18 * m_Scale_Coefficient));
	m_Character_Sizes.insert(std::pair<Break::Character_sizes, float>(Break::ch_Medium_Small, 24 * m_Scale_Coefficient));
	m_Character_Sizes.insert(std::pair<Break::Character_sizes, float>(Break::ch_Medium, 32 * m_Scale_Coefficient));
	m_Character_Sizes.insert(std::pair<Break::Character_sizes, float>(Break::ch_Large, 40 * m_Scale_Coefficient));
	//	Object sizes
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Ball, sf::Vector2f(7, 7) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Paddle_Default, sf::Vector2f(80, 16) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Paddle_Large, sf::Vector2f(160, 16) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Paddle_Small, sf::Vector2f(40, 16) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_PowerUp, sf::Vector2f(40, 20) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Block, sf::Vector2f(70, 35) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Level, sf::Vector2f(700, 950) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Laser_Beam, sf::Vector2f(3, 11) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Timer, sf::Vector2f(100, 5) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_ActivePowerUp_Block, sf::Vector2f(175, 50) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Overlay, sf::Vector2f(300, 125) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Pause_Area, sf::Vector2f(350, 150) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Pause_Button, sf::Vector2f(315, 50) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Vertical_Outline, sf::Vector2f(20, 160) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Horizontal_Outline, sf::Vector2f(140, 20) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Corner_Outline, sf::Vector2f(20, 20) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Deco_Bolt, sf::Vector2f(15, 15) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Deco_Vertical_border, sf::Vector2f(15, 50) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Deco_Horizontal_border, sf::Vector2f(50, 15) * m_Scale_Coefficient));
	m_Component_Sizes.insert(std::pair<Break::Sizes, sf::Vector2f>(Break::size_Deco_Background_slab, sf::Vector2f(70, 40) * m_Scale_Coefficient));
	//	Distances
	m_Distances.insert(std::pair<Break::Distances, float>(Break::dis_Close, 1 * m_Scale_Coefficient));
	m_Distances.insert(std::pair<Break::Distances, float>(Break::dis_Near, 5 * m_Scale_Coefficient));
	m_Distances.insert(std::pair<Break::Distances, float>(Break::dis_Medium, 15 * m_Scale_Coefficient));
	m_Distances.insert(std::pair<Break::Distances, float>(Break::dis_Far, 50 * m_Scale_Coefficient));
	m_Distances.insert(std::pair<Break::Distances, float>(Break::dis_Very_Far, 100 * m_Scale_Coefficient));
	//	Fixed positions
	m_Component_Positions.insert(std::pair<Break::Components, sf::Vector2f>(Break::c_Level_Area, sf::Vector2f(m_Key_Positions.at(Break::kp_Center).x, m_Key_Positions.at(Break::kp_Center).y + 1.5*m_Distances.at(Break::dis_Medium))));
	m_Component_Positions.insert(std::pair<Break::Components, sf::Vector2f>(Break::c_Blocks, sf::Vector2f(m_Component_Positions.at(Break::c_Level_Area).x - m_Component_Sizes.at(Break::size_Level).x / 2, m_Component_Positions.at(Break::c_Level_Area).y - m_Component_Sizes.at(Break::size_Level).y / 2 + 2*m_Distances.at(Break::dis_Far))));
	m_Component_Positions.insert(std::pair<Break::Components, sf::Vector2f>(Break::c_Paddle, sf::Vector2f(m_Component_Positions.at(Break::c_Level_Area).x, m_Component_Positions.at(Break::c_Level_Area).y + m_Component_Sizes.at(Break::size_Level).y / 2 - m_Component_Sizes.at(Break::size_Paddle_Default).y)));
	m_Component_Positions.insert(std::pair<Break::Components, sf::Vector2f>(Break::c_Ball, sf::Vector2f(m_Component_Positions.at(Break::c_Paddle).x, m_Component_Positions.at(Break::c_Paddle).y - 2*m_Component_Sizes.at(Break::size_Ball).x)));
	//	Interface positions
	m_UI_Component_Positions.insert(std::pair<Break::UI_Components, sf::Vector2f>(Break::cUI_Lives, sf::Vector2f(m_Component_Positions.at(Break::c_Level_Area).x + m_Component_Sizes.at(Break::size_Level).x / 2 + m_Distances.at(Break::dis_Very_Far), m_Component_Sizes.at(Break::size_Level).y / 2)));	
	m_UI_Component_Positions.insert(std::pair<Break::UI_Components, sf::Vector2f>(Break::cUI_Score, sf::Vector2f(m_Component_Positions.at(Break::c_Level_Area).x - m_Component_Sizes.at(Break::size_Level).x / 2 - 2*m_Distances.at(Break::dis_Very_Far), m_Component_Sizes.at(Break::size_Level).y / 3)));	
	m_UI_Component_Positions.insert(std::pair<Break::UI_Components, sf::Vector2f>(Break::cUI_Level_Number, sf::Vector2f(0, 0)));
	m_UI_Component_Positions.insert(std::pair<Break::UI_Components, sf::Vector2f>(Break::cUI_PowerUp_Timers, sf::Vector2f(m_Key_Positions.at(Break::kp_Center).x + m_Component_Sizes.at(Break::size_Level).x / 2 + m_Distances.at(Break::dis_Far), m_Distances.at(Break::dis_Very_Far))));
	//	Switches
	m_Switches.insert(std::pair<Break::Bool_Switches, bool>(Break::sw_Victory, false));
	m_Switches.insert(std::pair<Break::Bool_Switches, bool>(Break::sw_Defeat, false));
	//	Speeds
	m_Speeds.insert(std::pair<Break::Speeds, float>(Break::speed_Ball_Default, 800 * m_Scale_Coefficient));
	m_Speeds.insert(std::pair<Break::Speeds, float>(Break::speed_Ball_Fast, 900 * m_Scale_Coefficient));
	m_Speeds.insert(std::pair<Break::Speeds, float>(Break::speed_Ball_Slow, 600 * m_Scale_Coefficient));
	m_Speeds.insert(std::pair<Break::Speeds, float>(Break::speed_PowerUp, 500 * m_Scale_Coefficient));
	m_Speeds.insert(std::pair<Break::Speeds, float>(Break::speed_Laser_Beam, 2000 * m_Scale_Coefficient));
	//	Texts
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_Level, "Level: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_Score, "Score: \n"));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_Defeat, "Game Over "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_Victory, "All levels are beaten! "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_Mission_Start, "Level number: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pow_Slow_Ball, "Slow Ball: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pow_Fast_Ball, "Fast Ball: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pow_Big_Paddle, "Streched Paddle: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pow_Small_Paddle, "Shrinked Paddle: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pow_Sticky_Paddle, "Sticky Paddle: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pow_Laser_Paddle, "Laser Paddle: "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pau_Continue, " Continue Game "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_pau_Exit, " Exit "));
	m_Texts.insert(std::pair<Break::Texts, std::string>(Break::txt_ActivePows, "Active PowerUps:"));
	//	Score increase when ball hits
	m_Score_Increase.insert(std::pair<Break::Score_increase, UINT>(Break::score_small, 5));
	m_Score_Increase.insert(std::pair<Break::Score_increase, UINT>(Break::score_medium, 10));
	m_Score_Increase.insert(std::pair<Break::Score_increase, UINT>(Break::score_large, 20));
	m_Score_Increase.insert(std::pair<Break::Score_increase, UINT>(Break::score_badpowerup, 50));
	//	Textures - general
	m_Paddle_TextureRect.insert(std::pair<Break::Paddle_Type, sf::IntRect>(Break::Paddle_Default, sf::IntRect(80, 110, 80, 16)));
	m_Paddle_TextureRect.insert(std::pair<Break::Paddle_Type, sf::IntRect>(Break::Paddle_Big, sf::IntRect(80, 130, 120, 16)));
	m_Paddle_TextureRect.insert(std::pair<Break::Paddle_Type, sf::IntRect>(Break::Paddle_Small, sf::IntRect(80, 90, 40, 16)));
	m_Paddle_TextureRect.insert(std::pair<Break::Paddle_Type, sf::IntRect>(Break::Paddle_Sticky, sf::IntRect(80, 170, 80, 16)));
	m_Paddle_TextureRect.insert(std::pair<Break::Paddle_Type, sf::IntRect>(Break::Paddle_Laser, sf::IntRect(80, 150, 80, 16)));
	//	Textures - blocks
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_None, sf::IntRect(0, 0, 0, 0)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Red, sf::IntRect(0, 0, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Orange, sf::IntRect(0, 35, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Yellow, sf::IntRect(0, 70, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Green, sf::IntRect(0, 105, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Cyan, sf::IntRect(0, 140, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Blue, sf::IntRect(0, 175, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_OceanBlue, sf::IntRect(0, 210, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Brown, sf::IntRect(0, 245, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Pink, sf::IntRect(0, 280, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Purple, sf::IntRect(0, 315, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Grey, sf::IntRect(80, 0, 70, 35)));
	m_Block_TextureRect.insert(std::pair<Break::Block_ID, sf::IntRect>(Break::bID_Gold, sf::IntRect(80, 35, 70, 35)));
	//	Textures - power ups
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Laser_Paddle, sf::IntRect(280, 10, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Fast_Ball, sf::IntRect(280, 30, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Shrink_Paddle, sf::IntRect(280, 50, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Sticky_Paddle, sf::IntRect(280, 70, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Triple_Ball, sf::IntRect(280, 90, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Stretch_Paddle, sf::IntRect(280, 110, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Slow_Ball, sf::IntRect(280, 130, 40, 20)));
	m_PowerUp_TextureRect.insert(std::pair<Break::PowerUp_ID, sf::IntRect>(Break::pID_Extra_Life, sf::IntRect(280, 150, 40, 20)));
	//	Textures - misc.
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Ball, sf::IntRect(250, 0, 14, 14)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Level_TopLeft, sf::IntRect(380, 10, 41, 41)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Level_TopRight, sf::IntRect(424, 10, 41, 41)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Level_Horizontal, sf::IntRect(330, 177, 160, 43)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Level_Vertical, sf::IntRect(329, 10, 42, 160)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Background_Deco1, sf::IntRect(360, 240, 70, 40)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Background_Deco2, sf::IntRect(440, 240, 70, 40)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Background_Deco3, sf::IntRect(360, 290, 70, 40)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Background_Deco4, sf::IntRect(440, 290, 70, 40)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Decoration_Feature_Vertical1, sf::IntRect(380, 100, 20, 50)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Decoration_Feature_Vertical2, sf::IntRect(470, 100, 20, 50)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Decoration_Feature_Horizontal1, sf::IntRect(410, 100, 50, 20)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Decoration_Feature_Horizontal2, sf::IntRect(410, 130, 50, 20)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Decoration_Feature_Corner1, sf::IntRect(380, 60, 30, 30)));
	m_Miscellaneous_TextrureRect.insert(std::pair<Break::Misc_Textures, sf::IntRect>(Break::t_Decoration_Feature_Corner2, sf::IntRect(420, 60, 30, 30)));


	//	Quantities of elements.

	m_Quantities.insert(std::pair<Break::UINT_Numbers, UINT>(Break::Number_of_Lives, 3));
	m_Quantities.insert(std::pair<Break::UINT_Numbers, UINT>(Break::Score_Number, 0));
	m_Quantities.insert(std::pair<Break::UINT_Numbers, UINT>(Break::Current_Level, 1));

	//	seed set;
	UINT seed = std::chrono::system_clock::now().time_since_epoch().count();
	m_Random_engine.seed(seed);


	sf::Sound snd;
	snd.setVolume(m_Data.getResources().getSoundVolume());

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/Menu/Hover.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Hover, snd));
	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/Menu/Select.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Select, snd));
	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/Menu/Escape.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Escape, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Block hit.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Block_hit, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Paddle hit.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Paddle_hit, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Player loose.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Player_loose, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/PowerUp lost.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_PowerUp_lost, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/PowerUp taken.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_PowerUp_taken, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Wall hit.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Wall_hit, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Laser Fire.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Laser_fire, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Game Over.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Game_Over, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Level Start.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Start, snd));

	snd.setBuffer(m_Data.getResources().getSoundBuffer("Sounds/BreakTrough/Victory.wav"));
	m_Sounds.insert(std::pair<Break::Sounds, sf::Sound>(Break::snd_Player_Win, snd));

}

BreakTrough_Data::~BreakTrough_Data()
{
	m_Data.getResources().UnloadTexture(ID_BreakTrough);
	m_Sounds.clear();
	m_Data.getResources().UnloadSounds();
}

void BreakTrough_Data::Exit()
{
	m_Data.ChangeState(e_Menu);
}

void BreakTrough_Data::Change_SubState(Break::SubStates param)
{
	m_CurrentSubState = param;

	if (m_CurrentSubState == Break::SubSt_Play)
	{
		m_Data.CursorVisibility = false;
	}
	else
	{
		m_Data.CursorVisibility = true;
	}
}

bool BreakTrough_Data::Set_TheEnd()
{
	if (m_Quantities.at(Break::Number_of_Lives) == 0)
	{
		return m_Switches.at(Break::sw_Defeat) = true;
	}
	else if ( !(m_Quantities.at(Break::Current_Level) < 7))	
	{
		return m_Switches.at(Break::sw_Victory) = true;
	}
	else
	{
		return false;
	}
}

void BreakTrough_Data::Change_Level(UINT param)
{
	m_Quantities.at(Break::Current_Level) = param;
}

Resources& BreakTrough_Data::get_Resources()
{
	return m_Data.getResources();
}

void BreakTrough_Data::update_Mouse()
{
	m_Mouse_Coordinates = m_Data.mMouseCoordinates;
}

const sf::Vector2i BreakTrough_Data::get_Mouse_Coordinates() const
{
	return m_Mouse_Coordinates;
}

std::default_random_engine& BreakTrough_Data::get_Random_Engine()
{
	return m_Random_engine;
}

const sf::Vector2f BreakTrough_Data::get_Key_Position(Break::Key_Positions param) const
{
	return m_Key_Positions.at(param);
}

const sf::Vector2f BreakTrough_Data::get_Component_Sizes(Break::Sizes param) const
{
	return m_Component_Sizes.at(param);
}

const UINT BreakTrough_Data::get_Character_Sizes(Break::Character_sizes param) const
{
	return m_Character_Sizes.at(param);
}

const float BreakTrough_Data::get_Distances(Break::Distances param) const
{
	return m_Distances.at(param);
}

const sf::Vector2f BreakTrough_Data::get_Components_Positions(Break::Components param) const
{
	return m_Component_Positions.at(param);
}

const sf::Vector2f BreakTrough_Data::get_UI_Components_Positions(Break::UI_Components param) const
{
	return m_UI_Component_Positions.at(param);
}

const bool BreakTrough_Data::get_Switches(Break::Bool_Switches param) const
{
	return m_Switches.at(param);
}

const float BreakTrough_Data::get_Speed(Break::Speeds param) const
{
	return m_Speeds.at(param);
}

const std::string BreakTrough_Data::get_Text(Break::Texts param) const
{
	return m_Texts.at(param);
}

const UINT BreakTrough_Data::get_Score_increase(Break::Score_increase param) const
{
	return m_Score_Increase.at(param);
}

const sf::IntRect BreakTrough_Data::get_TextureRect(Break::Block_ID param) const
{
	return m_Block_TextureRect.at(param);
}

const sf::IntRect BreakTrough_Data::get_TextureRect(Break::Paddle_Type param) const
{
	return m_Paddle_TextureRect.at(param);
}

const sf::IntRect BreakTrough_Data::get_TextureRect(Break::PowerUp_ID param) const
{
	return m_PowerUp_TextureRect.at(param);
}

const sf::IntRect BreakTrough_Data::get_TextureRect(Break::Misc_Textures param) const
{
	return m_Miscellaneous_TextrureRect.at(param);
}

const Break::SubStates BreakTrough_Data::get_Current_Substate() const
{
	return m_CurrentSubState;
}

const UINT BreakTrough_Data::get_Object_Quantities(Break::UINT_Numbers param) const
{
	return m_Quantities.at(param);
}

void BreakTrough_Data::set_Object_Quantities(Break::UINT_Numbers param1, UINT param2)
{
	m_Quantities.at(param1) = param2;
}

void BreakTrough_Data::Play_Sound(Break::Sounds param)
{
	if (m_Data.getResources().IsSoundOn())
	{
		m_Sounds.at(param).play();
	}
}

MusicPlayer& BreakTrough_Data::getMusicPlayer()
{
	return m_Data.getMusic_Player();
}
