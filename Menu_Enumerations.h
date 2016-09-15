#ifndef MENU_ENUMERATIONS_H
#define MENU_ENUMERATIONS_H

namespace Menus
{

	enum SubStates
	{
		Main_Menu,
		Choose_Game_Menu,
		Options_Menu,
		Credits_Menu
	};

	enum Char_sizes
	{
		ch_Small,		//	16 
		ch_Medium,		//	32 
		ch_Large		//	48 
	};

	enum Objects_sizes
	{
		size_Button,
		size_MiniButton,
		size_Label,
		size_HugeLabel,
		size_Title,
		size_Drop_Down_Menu
	};

	enum Distances
	{
		dis_VeryNear,		//	5	px
		dis_Near,			//	15	px
		dis_Medium,			//	50	px
		dis_Long,			//	75	px
		dis_Far,			//	100	px
		dis_VeryFar,		//	200	px
		dis_ExtremlyFar		//	300 px
	};

	enum Key_positions
	{
		kp_TopLeft_Corner,
		kp_TopRight_Corner,
		kp_BottomLeft_Corner,
		kp_BottomRight_Corner,
		kp_Center_Screen,
		kp_Center_LeftHalf_Screen,
		kp_Center_RightHalf_Screen,
		kp_Center_UpperHalf_Screen,
		kp_Center_BottomHalf_Screen,
		kp_Center_TopLeft_Quarter,
		kp_Center_TopRight_Quarter,
		kp_Center_BottomLeft_Quarter,
		kp_Center_BottomRight_Quarter
	};


	enum Sounds
	{
		snd_Select,
		snd_Escape,
		snd_Hover
	};

}
#endif