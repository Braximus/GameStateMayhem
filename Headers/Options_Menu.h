#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Buttons.h"
#include "Label.h"
#include "Menu_Substates_Base_Class.h"
#include "DropDownMenu.h"
#include "Check.h"
class Data;

class Options : public Menu_SubStates
{
	enum OptionsLabels
	{
		l_Resolution,
		l_Music_switch,
		l_Music_volume,
		l_Sound_switch,
		l_Sound_volume,
		l_AntiAliasing,
		l_Fullscreen,
		l_Vsync
	};
	enum OptionsSelections
	{
		s_None,
		s_AntiAliasing,
		s_Resolution,
		s_FullScreen,
		s_Vsync,
		s_Music_switch,
		s_Music_left,
		s_Music_right,
		s_Sound_switch,
		s_Sound_left,
		s_Sound_right,
		s_Apply,
		s_Back
	};

	MenuData&				mMenu_Data;
	sf::Text				debag;
	
	OptionsSelections		mCurrentSelection;
	OptionsSelections		mPreviousSelection;

	std::map<OptionsSelections, Button>						mButtons;
	std::map<OptionsLabels, sf::Text>						mTexts;
	std::map<OptionsLabels, Label>							mLabels;
	std::map<OptionsSelections, Check>						mChecks;
	std::map<OptionsSelections, DropDownMenu>				mDropDownMenus;
	//
	float					mSoundVolume;
	//
	UINT					mVM_Index, mOld_VM_Index;
	UINT					mAA_Index, mOld_AA_Index;
	bool					mFullScreen, mOldFullScreen, mVsync;
	// 	changes that require new window;
	bool					mApplyButton;
	void					ApplyChanges();
	void					CheckChanges();
	void					CancelChanges();
	void					SetResolutionChanges();
	void					SetFullScreenChanges();
	void					SetAntiAliasing();
	//	Changes that don't require new window;
	void					SetVsync();
	void					SetMusic();
	void					SetSound();
	void					SetMusicVolumeChanges(bool);
	void					SetSoundVolumeChanges(bool);
	//
	void					KeyboardEvents(sf::Event& Event);
	void					MouseEvents(sf::Event& Event);

public:
	explicit				Options(MenuData& data);

	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					update(sf::Time& time);
	void					handleEvents(sf::Event& Event);
	void					handleRealTimeInput();
	void					refresh();

	



};


#endif
