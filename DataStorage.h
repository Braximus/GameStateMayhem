#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H


#include "Resources.h"
#include "StateCategory.h"
#include "MusicPlayer.h"
class Data
{
	//--------------------------//
	//-------Global_Data--------//
	//--------------------------//
	eState						mStateID;					//	Labels current state of the application;
	float						mScaleCoefficient;			//	It is applied to the sizes of objects;
	bool						DebugOnOff;					
	bool						setHardwareCursorOnOff;		
	sf::Sprite					mMouse_Cursor;
	//--------------------------//
	//-------Window_Data--------//
	//--------------------------//	
	sf::RenderWindow&			mWindow;					
	sf::ContextSettings			mSettings;					//	OpenGL context settings, used solely for changing AntiAliasing;
	std::vector<UINT>			mAntiAliasing;
	UINT						mAA_Index;
	bool						mVsync;						
	bool						mIsFullscreen;				
	//--------------------------//
	//--------Video Mode--------//
	//--------------------------//
	UINT						mVideoModeIndex;			//	This number determens which resolution is used;
	std::vector<sf::VideoMode>	mVideo_Modes;					
	void						updateVideoModes();			
	//--------------------------//
	//--------Resources---------//
	//--------------------------//
	Resources					mResources;					
	MusicPlayer					mMusic_Player;
public:
	explicit					Data(sf::RenderWindow& win);
	bool						CursorVisibility;			
	~Data();
	//--------------------------//
	//-------Window_Data--------//
	//--------------------------//
	void						set_AA_Level(UINT param);	
	const UINT					get_Current_AA_Level() const;
	const UINT					get_AA_Levels(UINT param) const;		
	const UINT					get_AA_Index() const;
	void						set_Vsync(bool);					
	const bool					get_Vsync() const;
	void						set_Fullscreen_mode(bool);
	const bool					IsFullScreen() const;
	//--------------------------//
	//--------Video Mode--------//
	//--------------------------//
	const sf::VideoMode			getVideo_Mode() const;
	const sf::VideoMode			getVideo_Mode(UINT) const;
	const UINT					getNumber_of_Video_Modes() const;
	const UINT					getCurrent_VM_Index() const;
	void						Update_Window(UINT num = 0);
	//--------------------------//
	//--------Resources---------//
	//--------------------------//
	Resources&					getResources(); 
	MusicPlayer&				getMusic_Player();
	//--------------------------//
	//-------Global_Data--------//
	//--------------------------//
	sf::Vector2i				mMouseCoordinates;
	const eState				getStateID() const;
	void						ChangeState(eState);
	void						Close();
	void						toggleDebug();
	const bool					checkDebug() const;
	const float					getScaleCoefficient() const;
	//	Cursor
	void						update_cursor();
	bool						is_mouse_pressed;
	bool						lock_cursor;
	const sf::Sprite&			getMouse_Cursor() const;
	void						center_Cursor_Origin(bool);
	void						change_Cursor(sf::IntRect);
};

#endif