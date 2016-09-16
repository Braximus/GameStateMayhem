#ifndef COMETWARS_ENUMERATIONS_H
#define COMETWARS_ENUMERATIONS_H

namespace CW
{

	enum SubStates
	{
		sub_Play,
		sub_Pause,
		sub_Start,
		sub_End
	};

	enum End
	{
		eNone,
		eVictory,
		eDefeat
	};

	enum Objects
	{
		O_Asteroid,
		O_Mini_Asteroid,
		O_Ship,
		O_Projectiles
	};

	enum Distances
	{
		dis_Close,		//	3px
		dis_Near,		//	10px
		dis_Medium,		//	25px
		dis_Far			//	50px
	};

	enum Key_Positions
	{
		kp_TopLeft,		//	0,0
		kp_TopRight,		//	VM width, 0
		kp_BottomLeft,		//	0, VM height
		kp_BottomRight,		//	VM width, VM height
		kp_Center		//	VM width/2, VM height/2
	};

	enum Character_size
	{
		ch_Small,		//	18
		ch_Medium,		//	30
		ch_Large		//	48
	};

	enum Components_size
	{
		size_Ship,	
		size_Projectile,
		size_Shield,
		size_Comet,
		size_Mini_Comet,
		size_Rear_Comet,
		size_Rear_Mini_Comet,
		size_UI_Area,
		size_SplashScreen,
		size_Countdown,
		size_Pause_Area,
		size_Pause_Button,
		size_Battery
	};

	enum Texts
	{
		txt_Score,
		txt_Text_Flash,
		txt_Continue_Button,
		txt_NewGame_Button,
		txt_Exit_Button,
		txt_Loose,
		txt_Win
	};

	enum Object_Speed
	{
		speed_Ship,
		speed_Asteroid,
		speed_Mini_Asteroid,
		speed_Projectile,
		speed_Rear_Comet
	};

	enum AsteroidDamage
	{
		No_Damage,
		Light_Damage,
		Moderate_Damage,
		Heavy_Damage,
		Dead
	};

	enum ShipType
	{
		ship_Type1,
		ship_Type2,
		ship_Type3
	};

	enum AsteroidType
	{
		com_Type1_Major,
		com_Type2_Major,
		com_Type3_Major,
		com_Type4_Major,
		com_Type1_Minor,
		com_Type2_Minor,
		com_Type3_Minor,
		com_Type4_Minor,
		com_Type5_Minor,
		com_Type6_Minor,
		com_Type7_Minor,
		com_Type8_Minor,
		com_Rear_Type1_Major,
		com_Rear_Type2_Major,
		com_Rear_Type3_Major,
		com_Rear_Type4_Major,
		com_Rear_Type5_Major,
		com_Rear_Type6_Major,
		com_Rear_Type1_Minor,
		com_Rear_Type2_Minor,
		com_Rear_Type3_Minor,
		com_Rear_Type4_Minor,
		com_Rear_Type5_Minor,
		com_Rear_Type6_Minor,
		com_Rear_Type7_Minor,
		com_Rear_Type8_Minor,
		com_Rear_Type9_Minor,
		com_Rear_Type10_Minor,
		com_Rear_Type11_Minor,
		com_Rear_Type12_Minor
	};


	enum Misc_Tex_rects
	{
		msc_Battery
	};

	enum UI_Components
	{
		UI_None,
		UI_Area,
		UI_Score,
		UI_Text_Flash,
		UI_Lives
	};
	
	enum Button_Selection
	{
		bt_None,
		bt_Continue,
		bt_New,
		bt_Exit
	};

	enum Zones
	{
		z_Top,
		z_Left,
		z_Right,
		z_Bottom
	//	z_Level
	};

	enum Sounds
	{
		snd_Hover,
		snd_Select,
		snd_Escape,
		snd_CometBigDead,
		snd_Hit,
		snd_LaserFire,
		snd_PlayerShieldUp,
		snd_PlayerShieldDown,
		snd_PlayerShipDestroyed
	};

}

#endif
