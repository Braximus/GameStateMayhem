#ifndef QUATA_ENUMERATIONS_H
#define QUATA_ENUMERATIONS_H

namespace Qua
{
	enum SubState
	{
		Start,
		Play,
		Pause,
		End,
	};

	enum Quata_Object_Components
	{
		co_Playground,
		co_Player_Paddle,
		co_AI_Paddle,
		co_Ball
	};
	enum Quata_UI_Components
	{
		cu_Pause,
		cu_Score1,
		cu_Score2,
		cu_Player1_name,
		cu_Player2_name,
		cu_SplashScreen_Start,
		cu_SplashScreen_Win,
		cu_SplashScreen_Loose
	};

	enum Quata_Obj_Sizes
	{
		size_Paddle,
		size_Ball,
		size_Playground,
		size_SplashScreen,
		size_Button,
		size_Pause_Area,
		size_LineThickness,
		size_Playground_texture
	};

	enum Quata_Texts
	{
		txt_Start,
		txt_Win,
		txt_Loose,
		txt_Player1_name,
		txt_Player2_name,
		txt_Continue_button,
		txt_New_button,
		txt_Exit_button
	};

	enum Quata_Texture_rects
	{
		intrect_Player,
		intrect_AI,
		intrect_Ball,
		intrect_Background1,
	};

	enum Quata_Speeds
	{
		speed_Ball_nominal,
		speed_Ball_increase,
		speed_Ball_max,
		speed_Paddle
	};

	enum Quata_Char_Sizes
	{
		ch_Small,	//	16px
		ch_Medium,	//	32px
		ch_Large	//	48px
	};

	enum Quata_Zones
	{
		z_UpperPlayField,
		z_BottomPlayField,
		z_RightPlayField,
		z_LeftPlayField
	};

	enum Quata_Key_Positions
	{
		kp_TopLeft_Corner,
		kp_TopRight_Corner,
		kp_BottomLeft_Corner,
		kp_BottomRight_Corner,
		kp_Center_Screen,
		kp_LeftCenter_Screen,
		kp_RightCenter_Screen,
		kp_UpperCenter_Screen,
		kp_BottomCenter_Screen
	};

	enum Quata_Distances
	{
		dis_VeryNear,		//	10px
		dis_Near,		//	30px
		dis_Medium,		//	50px
		dis_Far,		//	100px
		dis_VeryFar		//	200px
	};

	enum Sounds
	{
		snd_Wall_Ball_bounce,
		snd_Player_Ball_bounce,
		snd_Opponent_Ball_bounce,
		snd_Opponent_Score,
		snd_Player_Score,
		snd_Player_Win,	
		snd_Player_Loose,
		snd_Hover,
		snd_Select,
		snd_Escape
	};
	
	enum Button_Selection
	{
		None,
		New,
		Continue,
		Exit
	};

}
#endif
