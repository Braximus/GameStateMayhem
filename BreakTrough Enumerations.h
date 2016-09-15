#ifndef BREAKTROUGH_ENUMERATIONS_H
#define BREAKTROUGH_ENUMERATIONS_H

namespace Break
{
	enum SubStates
	{
		SubSt_StartMission,			
		SubSt_Play,
		SubSt_Pause,
		SubSt_End
	};

	enum Character_sizes
	{
		ch_Small,
		ch_Medium_Small,
		ch_Medium,
		ch_Large
	};

	enum Components
	{
		c_Ball,
		c_Paddle,
		c_PowerUp,
		c_Blocks,
		c_Level_Area,
		c_Laser_Beam
	};

	enum UI_Components
	{
		cUI_Lives,
		cUI_Score,
		cUI_Level_Number,
		cUI_PowerUp_Timers,
	};

	enum Distances
	{
		dis_Close,		//	1 px
		dis_Near,		//	5 px
		dis_Medium,		//	15 px
		dis_Far,		//	30 px
		dis_Very_Far	//	50 px
	};
	
	enum Key_Positions
	{
		kp_TopLeft,
		kp_TopRight,
		kp_BottomLeft,
		kp_BottomRight,
		kp_Center
	};

	enum Sizes
	{
		size_Ball,
		size_Paddle_Default,
		size_Paddle_Large,
		size_Paddle_Small,
		size_PowerUp,
		size_Block,
		size_Level,
		size_Laser_Beam,
		size_Timer,
		size_ActivePowerUp_Block,
		size_Pause_Area,
		size_Pause_Button,
		size_Overlay,
		size_Vertical_Outline,
		size_Horizontal_Outline,
		size_Corner_Outline,
		size_Deco_Bolt,
		size_Deco_Vertical_border,
		size_Deco_Horizontal_border,
		size_Deco_Background_slab

	};

	enum Speeds
	{
		speed_Ball_Default,
		speed_Ball_Fast,
		speed_Ball_Slow,
		speed_PowerUp,
		speed_Laser_Beam
	};

	enum Bool_Switches
	{
		sw_Victory,
		sw_Defeat,
	};

	enum Paddle_Type
	{
		Paddle_Default,
		Paddle_Laser,
		Paddle_Sticky,
		Paddle_Big,
		Paddle_Small
	};

	enum Block_ID
	{
		bID_None = -1,
		bID_Red,
		bID_Orange,
		bID_Yellow,
		bID_Green,
		bID_Cyan,
		bID_Blue,
		bID_OceanBlue,
		bID_Brown,
		bID_Pink,
		bID_Purple,
		bID_Grey,		//	Tough
		bID_Gold		//	Invulnerable
	};

	enum PowerUp_ID
	{
		pID_Slow_Ball,		//	Braon
		pID_Fast_Ball,		//	Narandzasta
		pID_Triple_Ball,	//	Svetlo plava
		pID_Stretch_Paddle,	//	Tamno Plava
		pID_Shrink_Paddle,	//	Ljubicasta
		pID_Laser_Paddle,	//	Crvena
		pID_Extra_Life,		//	Crna/Siva
		pID_Sticky_Paddle	//	Zelena
	};

	enum UINT_Numbers
	{
		Number_of_Lives,
		Score_Number,
		Current_Level
	};

	enum Score_increase
	{
		score_small,		//	5
		score_medium,		//	10
		score_large,		//	20
		score_badpowerup	//	100
	};

	enum Texts
	{
		txt_Level,
		txt_Score,
		txt_Lives,
		txt_Defeat,
		txt_Victory,
		txt_Mission_Start,
		txt_pow_Slow_Ball,
		txt_pow_Fast_Ball,
		txt_pow_Big_Paddle,
		txt_pow_Small_Paddle,
		txt_pow_Sticky_Paddle,
		txt_pow_Laser_Paddle,
		txt_pau_Continue,
		txt_pau_Exit,
		txt_ActivePows
	};

	enum Misc_Textures
	{
		t_Ball,
		t_Level_TopLeft,
		t_Level_TopRight,
		t_Level_Horizontal,
		t_Level_Vertical,
		t_Background_Deco1,
		t_Background_Deco2,
		t_Background_Deco3,
		t_Background_Deco4,
		t_Decoration_Feature_Vertical1,
		t_Decoration_Feature_Vertical2,
		t_Decoration_Feature_Horizontal1,
		t_Decoration_Feature_Horizontal2,
		t_Decoration_Feature_Corner1,
		t_Decoration_Feature_Corner2
	};

	enum Button_Selection
	{
		None,
		Continue,
		Exit
	};

	enum Sounds
	{
		snd_Hover,
		snd_Select,
		snd_Escape,
		snd_Block_hit,
		snd_Paddle_hit,
		snd_Player_loose,
		snd_Game_Over,
		snd_Player_Win,
		snd_Start,
		snd_Wall_hit,
		snd_PowerUp_lost,
		snd_PowerUp_taken,
		snd_Laser_fire
	};

}
#endif