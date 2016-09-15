#include "stdafx.h"
#include "Options_Menu.h"
#include "DataStorage.h"

Options::Options(MenuData& data)
	:mMenu_Data(data)
{
	mCurrentSelection = s_None;
	
	mSoundVolume = mMenu_Data.getResources().getSoundVolume();

	mVsync = mMenu_Data.mData.get_Vsync();
	mVM_Index = mMenu_Data.mData.getCurrent_VM_Index();
	mOld_VM_Index = mVM_Index;
	mAA_Index = mMenu_Data.mData.get_AA_Index();
	mOld_AA_Index = mAA_Index;
	mFullScreen = mMenu_Data.mData.IsFullScreen();
	mOldFullScreen = mFullScreen;

	mApplyButton = false;

	refresh();
}

void Options::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = NULL;
	for (const auto& it : mButtons)
	{
		target.draw(it.second, states);
	}
	for (const auto& it : mLabels)
	{
		target.draw(it.second, states);
	}
	for (const auto& it : mTexts)
	{
		target.draw(it.second, states);
	}
	for (const auto& it : mChecks)
	{
		target.draw(it.second, states);
	}
	for (const auto& it : mDropDownMenus)
	{
		target.draw(it.second, states);
	}

}

void Options::update(sf::Time& time)
{
	if (!mMenu_Data.mRefreshed)
	{
		refresh();
	}
	if (mApplyButton)
	{
		mButtons.at(s_Apply).toggle_DimText(false);
	}
	else
	{
		mButtons.at(s_Apply).toggle_DimText(true);
	}
	mDropDownMenus.at(s_Resolution).get_Bounds();
	mDropDownMenus.at(s_AntiAliasing).get_Bounds();
	if (mPreviousSelection != mCurrentSelection)
	{
		if (mCurrentSelection != s_None)
		{
			mMenu_Data.Play_Sound(Menus::snd_Hover);
		}
		mPreviousSelection = mCurrentSelection;
	}
}

void Options::handleEvents(sf::Event& Event)
{
	KeyboardEvents(Event);
	MouseEvents(Event);
}

void Options::handleRealTimeInput()
{
	bool da_li_je_van = true;
	sf::Vector2f mouse = static_cast<sf::Vector2f>(mMenu_Data.MouseCoord());

	if (da_li_je_van)
	{
		for (auto& it : mDropDownMenus)
		{
			if (it.second.hover(mouse))
			{
				da_li_je_van = false;
				mCurrentSelection = it.first;
			}
		}
	}

	if (da_li_je_van)	//	Ako nije van, onda NEMOJ da radis sledece
	{
		for (auto& it : mButtons)
		{
			if (it.second.check_Bounds(mouse))
			{
				da_li_je_van = false;
				mCurrentSelection = it.first;	// Postavljamo selekciju na odgovarajuce dugme!
				it.second.ToggleSelection_ByColor(true);
			}
			else
			{
				it.second.ToggleSelection_ByColor(false);
			}
		}
	}
	else
	{
		for (auto& it : mButtons)
		{
			it.second.ToggleSelection_ByColor(false);
		}
	}

	if (da_li_je_van)
	{	
		for (auto& it : mChecks)
		{
			if (it.second.onHover(mouse))
			{
				da_li_je_van = false;
				mCurrentSelection = it.first;
			}
		}
	}

	if (da_li_je_van)
	{
		mCurrentSelection = s_None;
	}
}

void Options::KeyboardEvents(sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
		{
			mMenu_Data.ChangeSubState(Menus::Main_Menu);
		}
	}
}

void Options::MouseEvents(sf::Event& Event)
{
	if (Event.type == sf::Event::MouseButtonPressed)
	{
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (mCurrentSelection == s_Resolution)
			{
				mDropDownMenus.at(mCurrentSelection).choose(static_cast<sf::Vector2f>(mMenu_Data.MouseCoord()));
				SetResolutionChanges();
				mDropDownMenus.at(s_AntiAliasing).force_close();
				mMenu_Data.Play_Sound(Menus::snd_Hover);
			}
			else if (mCurrentSelection == s_AntiAliasing)
			{
				mDropDownMenus.at(mCurrentSelection).choose(static_cast<sf::Vector2f>(mMenu_Data.MouseCoord()));
				SetAntiAliasing();
				mDropDownMenus.at(s_Resolution).force_close();
				mMenu_Data.Play_Sound(Menus::snd_Hover);
				
			}
			else if (mCurrentSelection == s_FullScreen)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				SetFullScreenChanges();
			}
			else if (mCurrentSelection == s_Vsync)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				SetVsync();
			}
			else if (mCurrentSelection == s_Music_switch)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				SetMusic();
			}
			else if (mCurrentSelection == s_Sound_switch)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				SetSound();
			}
			else if (mCurrentSelection == s_Sound_left)
			{
				if (mMenu_Data.getResources().IsSoundOn())
				{

					mMenu_Data.Play_Sound(Menus::snd_Select);
					SetSoundVolumeChanges(false);
				}
			}
			else if (mCurrentSelection == s_Sound_right)
			{
				if (mMenu_Data.getResources().IsSoundOn())
				{
					mMenu_Data.Play_Sound(Menus::snd_Select);
					SetSoundVolumeChanges(true);
				}
			}
			else if (mCurrentSelection == s_Music_left)
			{
				if (mMenu_Data.getMusicPlayer().is_Music_Playing())
				{
					mMenu_Data.Play_Sound(Menus::snd_Select);
					SetMusicVolumeChanges(false);
				}
			}
			else if (mCurrentSelection == s_Music_right)
			{
				if (mMenu_Data.getMusicPlayer().is_Music_Playing())
				{
					mMenu_Data.Play_Sound(Menus::snd_Select);
					SetMusicVolumeChanges(true);
				}
			}
			else if (mCurrentSelection == s_None)
			{
				mDropDownMenus.at(s_Resolution).force_close();
				mDropDownMenus.at(s_AntiAliasing).force_close();
			}
		}
	}
	if (Event.type == sf::Event::MouseButtonReleased)
	{
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (mCurrentSelection == s_Back)
			{
				CancelChanges();
				mMenu_Data.Play_Sound(Menus::snd_Escape);
				mMenu_Data.ChangeSubState(Menus::Main_Menu);
			}
			else if (mCurrentSelection == s_Apply)
			{
				if (mApplyButton)
				{
					mMenu_Data.Play_Sound(Menus::snd_Select);
					ApplyChanges();
				}
				else
				{
					mMenu_Data.Play_Sound(Menus::snd_Escape);
				}
			}

			mDropDownMenus.at(s_Resolution).release();
			mDropDownMenus.at(s_AntiAliasing).release();
		}

	}
	
}

// Podesavanja koja zahtevajuu novi prozor:

void Options::SetResolutionChanges()
{
	mVM_Index = mDropDownMenus.at(s_Resolution).return_value();
	CheckChanges();
}

void Options::SetAntiAliasing()
{
	mAA_Index = mDropDownMenus.at(s_AntiAliasing).return_value();
	CheckChanges();
}

void Options::SetFullScreenChanges()
{
	mFullScreen = mChecks.at(s_FullScreen).onClick();
	CheckChanges();
}

void Options::SetVsync()
{
	mVsync = mChecks.at(s_Vsync).onClick();
	mMenu_Data.mData.set_Vsync(mVsync);
}

void Options::SetMusic()
{
	mMenu_Data.getMusicPlayer().Change_Music_status(mChecks.at(s_Music_switch).onClick());
	bool temp_bool = mMenu_Data.getMusicPlayer().is_Music_Playing();
	mLabels.at(l_Music_volume).set_Availability(temp_bool);
	mButtons.at(s_Music_left).toggle_DimText(!temp_bool);
	mButtons.at(s_Music_right).toggle_DimText(!temp_bool);
	if (!temp_bool)
	{
		mTexts.at(l_Music_volume).setColor(sf::Color(32, 128, 128, 128));
	}
	else
	{
		mTexts.at(l_Music_volume).setColor(sf::Color::Cyan);
	}
}

void Options::SetSound()
{
	mMenu_Data.getResources().SoundSwitch(mChecks.at(s_Sound_switch).onClick());
	bool temp_bool = mMenu_Data.getResources().IsSoundOn();
	mLabels.at(l_Sound_volume).set_Availability(temp_bool);	
	mLabels.at(l_Sound_volume).set_Availability(temp_bool);
	mButtons.at(s_Sound_left).toggle_DimText(!temp_bool);
	mButtons.at(s_Sound_right).toggle_DimText(!temp_bool);
	if (!temp_bool)
	{
		mTexts.at(l_Sound_volume).setColor(sf::Color(32, 128, 128, 128));
	}
	else
	{
		mTexts.at(l_Sound_volume).setColor(sf::Color::Cyan);
	}

}

void Options::SetMusicVolumeChanges(bool increase)
{
	float tempVolume = mMenu_Data.mData.getResources().getMusicVolume();

	if (increase)
	{
		if (tempVolume < 100)
		{
			tempVolume += 5;
			mMenu_Data.getResources().setMusicVolume(std::round(tempVolume) + 0.1);
		}
	}
	else
	{
		if (tempVolume > 1)
		{
			tempVolume -= 5;
			mMenu_Data.getResources().setMusicVolume(std::round(tempVolume) + 0.1);
		}
	}
	mTexts.at(l_Music_volume).setString(std::to_string(static_cast<UINT>(tempVolume)));
	//	Zelim da tekst bude na sredini.
	sf::FloatRect Bounds = mTexts.at(l_Music_volume).getLocalBounds();
	mTexts.at(l_Music_volume).setOrigin(Bounds.width / 2.0f, Bounds.top + Bounds.height / 2.0f);
	mMenu_Data.getMusicPlayer().Refresh_volume();
}


void Options::SetSoundVolumeChanges(bool increase)
{
	if (increase)
	{
		if (mSoundVolume < 100)
		{
			mSoundVolume += 5;
			mMenu_Data.getResources().setSoundVolume(std::round(mSoundVolume) + 0.1);
		}
	}
	else
	{
		if (mSoundVolume > 1)
		{
			mSoundVolume -= 5;
			mMenu_Data.getResources().setSoundVolume(std::round(mSoundVolume) + 0.1);
		
		}
	}

	for (auto& it : mMenu_Data.mSounds)
	{
		it.second.setVolume(mSoundVolume);
	}

	mTexts.at(l_Sound_volume).setString(std::to_string(static_cast<UINT>(mSoundVolume)));
	sf::FloatRect Bounds = mTexts.at(l_Sound_volume).getLocalBounds();
	mTexts.at(l_Sound_volume).setOrigin(Bounds.width / 2.0f, Bounds.top + Bounds.height / 2.0f);
}

void Options::ApplyChanges()
{
	mOld_VM_Index = mVM_Index;
	mOld_AA_Index = mAA_Index;
	mOldFullScreen = mFullScreen;
	mMenu_Data.mData.set_Fullscreen_mode(mFullScreen);
	mMenu_Data.mData.set_AA_Level(mAA_Index);
	mMenu_Data.mData.Update_Window(mVM_Index);
	mMenu_Data.mRefreshed = false;
}

void Options::CancelChanges()
{
	mDropDownMenus.at(s_Resolution).change_Label(mOld_VM_Index);
	mDropDownMenus.at(s_AntiAliasing).change_Label(mOld_AA_Index);
	if (mFullScreen != mOldFullScreen)
	{
		mChecks.at(s_FullScreen).onClick();	//	Vracam na staru vrednost.
	}
	mFullScreen = mOldFullScreen;

	mVM_Index = mOld_VM_Index;
	mAA_Index = mOld_AA_Index;
	CheckChanges();
}

void Options::CheckChanges()
{
	if ((mVM_Index != mOld_VM_Index) || (mAA_Index != mOld_AA_Index) || (mFullScreen != mOldFullScreen))
	{
		mApplyButton = true;
	}
	else
	{
		mApplyButton = false;
	}
}


void Options::refresh()
{
	mButtons.erase(mButtons.begin(), mButtons.end());
	mLabels.erase(mLabels.begin(), mLabels.end());
	mTexts.clear();
	mChecks.clear();
	mDropDownMenus.clear();

	bool			music_play = mMenu_Data.getMusicPlayer().is_Music_Playing();
	bool			sound_play = mMenu_Data.getResources().IsSoundOn();
	const sf::Texture&	texture = mMenu_Data.getResources().getTexture(ID_Menu);
	float			ch_size		 = mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium);
	const sf::Font&	font		 = mMenu_Data.getResources().getFont(ID_Global);
	float			dis_xfar	 = mMenu_Data.getMenu_Distances(Menus::dis_ExtremlyFar);
	float			dis_vfar	 = mMenu_Data.getMenu_Distances(Menus::dis_VeryFar);
	float			dis_far		 = mMenu_Data.getMenu_Distances(Menus::dis_Far);
	float			dis_long     = mMenu_Data.getMenu_Distances(Menus::dis_Long);
	float			dis_med		 = mMenu_Data.getMenu_Distances(Menus::dis_Medium);
	float			dis_near	 = mMenu_Data.getMenu_Distances(Menus::dis_Near);
	sf::Vector2f	size_label	 = mMenu_Data.getMenu_Object_Sizes(Menus::size_Label);
	sf::Vector2f	size_button	 = mMenu_Data.getMenu_Object_Sizes(Menus::size_Button);
	sf::Vector2f	size_mini_button = mMenu_Data.getMenu_Object_Sizes(Menus::size_MiniButton);
	sf::Vector2f	size_dropdown = mMenu_Data.getMenu_Object_Sizes(Menus::size_Drop_Down_Menu);

	sf::Vector2f	kp_tr = mMenu_Data.getMenu_Key_Positions(Menus::kp_TopRight_Corner);
	sf::Vector2f	kp_br = mMenu_Data.getMenu_Key_Positions(Menus::kp_BottomRight_Corner);

	sf::Vector2f	position;
	sf::Text		tekst;
	sf::FloatRect	Bounds;
	Check			a_Check;
	Label			mLabel;
	Button			a_Button;
	tekst.setFont(font);
	sf::Color color = sf::Color(32, 128, 128, 128);

	//	Oznake

	//********************************//
	//			Prva Oznaka			  //
	//********************************//
	mLabel = Label(font, " Resolution", ch_size);
	mLabel.set_Size(size_label);
	position = sf::Vector2f(dis_far + (size_label.x / 2), dis_vfar + (size_button.y / 2));
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Resolution, mLabel));
	//********************************//
	//			Druga Oznaka		  //
	//********************************//
	mLabel = Label(font, " Music On", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_Resolution).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Music_switch, mLabel));
	//********************************//
	//			Treca Oznaka		  //
	//********************************//
	mLabel = Label(font, " Music Volume", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_Music_switch).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabel.set_Availability(music_play);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Music_volume, mLabel));
	//********************************//
	//	       Cetvrta Oznaka		  //
	//********************************//
	mLabel = Label(font, " Sound On", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_Music_volume).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Sound_switch, mLabel));

	//********************************//
	//	       Peta Oznaka			  //
	//********************************//
	mLabel = Label(font, " Sound volume", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_Sound_switch).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabel.set_Availability(sound_play);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Sound_volume, mLabel));
	//********************************//
	//	       Sesta Oznaka			  //
	//********************************//
	mLabel = Label(font, " AntiAliasing", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_Sound_volume).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_AntiAliasing, mLabel));
	//********************************//
	//	       Sedma Oznaka			  //
	//********************************//
	mLabel = Label(font, " Fullscreen", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_AntiAliasing).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Fullscreen, mLabel));

	//********************************//
	//	       Osma Oznaka			  //
	//********************************//
	mLabel = Label(font, " Vsync", ch_size);
	mLabel.set_Size(size_label);
	Bounds = mLabels.at(l_Fullscreen).get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2 + dis_med);
	mLabel.set_Position(position);
	mLabel.get_Bounds();
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan, color);
	mLabels.insert(std::pair<OptionsLabels, Label>(l_Vsync, mLabel));

	//	Padajuci meni
	DropDownMenu	a_DropDownMenu;

	position = sf::Vector2f(kp_tr.x - (dis_xfar + (5 * (size_dropdown.x / 6) / 2)), mLabels.at(l_Resolution).get_Bounds().top + mLabels.at(l_Resolution).get_Bounds().height / 2);
	a_DropDownMenu = DropDownMenu(font, texture, ch_size, sf::IntRect(0, 400, 107, 107), size_dropdown, position, mMenu_Data.get_Video_mode_names_cont());
	a_DropDownMenu.change_Label(mVM_Index);
	mDropDownMenus.insert(std::pair<OptionsSelections, DropDownMenu>(s_Resolution, a_DropDownMenu));

	// Dok ne napravim slajdere, ovako cu ih koristiti! :)

	//	Dugmad

	// Muzika
	a_Button = Button(" >", font, ch_size);
	a_Button.set_Size(size_mini_button);
	position = sf::Vector2f(kp_tr.x - (dis_xfar - (size_mini_button.x / 2)), mLabels.at(l_Music_volume).get_Bounds().top + mLabels.at(l_Music_volume).get_Bounds().height / 2);
	a_Button.set_Position(position);
	a_Button.set_Colors(color, sf::Color::Cyan, color);
	a_Button.toggle_DimText(!music_play);
	a_Button.set_Bounds();
	mButtons.insert(std::pair<OptionsSelections, Button>(s_Music_right, a_Button));
	
	//	Ovde treba da ide tekst za jacinu muzike
	UINT music_volume = static_cast<UINT>(mMenu_Data.getResources().getMusicVolume());
	tekst.setString(std::to_string(music_volume));
	tekst.setCharacterSize(ch_size);
	Bounds = tekst.getLocalBounds();
	tekst.setOrigin(Bounds.width / 2.0f,Bounds.top + Bounds.height / 2.0f);
	Bounds = a_Button.get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2 - ((5 * size_dropdown.x / 6) / 2), Bounds.top + Bounds.height / 2);	
	tekst.setPosition(position);
	if (!music_play)
	{
		tekst.setColor(color);
	}
	else
	{
		tekst.setColor(sf::Color::Cyan);
	}
	mTexts.insert(std::pair<OptionsLabels, sf::Text>(l_Music_volume, tekst));
	
	a_Button = Button("<", font, ch_size);
	a_Button.set_Size(size_mini_button);
	position = sf::Vector2f(Bounds.left + Bounds.width / 2 - ((5 * size_dropdown.x / 6)), Bounds.top + Bounds.height / 2);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan, color);
	a_Button.toggle_DimText(!music_play);
	mButtons.insert(std::pair<OptionsSelections, Button>(s_Music_left, a_Button));

	// Zvukovi
	a_Button = Button(" >", font, ch_size);
	a_Button.set_Size(size_mini_button);
	position = sf::Vector2f(kp_tr.x - (dis_xfar - (size_mini_button.x / 2)), mLabels.at(l_Sound_volume).get_Bounds().top + mLabels.at(l_Sound_volume).get_Bounds().height / 2);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan, color);
	a_Button.toggle_DimText(!sound_play);
	mButtons.insert(std::pair<OptionsSelections, Button>(s_Sound_right, a_Button));

	//	Ovde treba da ide tekst za jacinu zvuka
	UINT sound_volume = static_cast<UINT>(mSoundVolume); // Za sada ;)
	tekst.setString(std::to_string(sound_volume));
	tekst.setCharacterSize(ch_size);
	Bounds = tekst.getLocalBounds();
	tekst.setOrigin(Bounds.width / 2.0f, Bounds.top + Bounds.height / 2.0f);
	Bounds = a_Button.get_Bounds();
	position = sf::Vector2f(Bounds.left + Bounds.width / 2 - ((5 * size_dropdown.x / 6) / 2), Bounds.top + Bounds.height / 2);	
	tekst.setPosition(position);
	if (!sound_play)
	{
		tekst.setColor(color);
	}
	else
	{
		tekst.setColor(sf::Color::Cyan);
	}
	mTexts.insert(std::pair<OptionsLabels, sf::Text>(l_Sound_volume, tekst));
	
	a_Button = Button("<", font, ch_size);
	a_Button.set_Size(size_mini_button);
	position = sf::Vector2f(Bounds.left + Bounds.width / 2 - ((5 * size_dropdown.x / 6)), Bounds.top + Bounds.height / 2);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan, color);
	a_Button.toggle_DimText(!sound_play);
	mButtons.insert(std::pair<OptionsSelections, Button>(s_Sound_left, a_Button));

	//	Drugi padajuci meni

	position = sf::Vector2f(kp_tr.x - (dis_xfar + (5 * (size_dropdown.x / 6) / 2)), mLabels.at(l_AntiAliasing).get_Bounds().top + mLabels.at(l_AntiAliasing).get_Bounds().height / 2);
	a_DropDownMenu = DropDownMenu(font, texture, ch_size, sf::IntRect(0, 400, 107, 107), size_dropdown, position, mMenu_Data.get_AA_levels_cont());
	a_DropDownMenu.change_Label(mAA_Index);
	mDropDownMenus.insert(std::pair<OptionsSelections, DropDownMenu>(s_AntiAliasing, a_DropDownMenu));
	//	Stikliranje! :)
	//	Rezolucija
	a_Check = Check(texture, mMenu_Data.get_Check_tex_rects());
	a_Check.set_Size(size_mini_button);
	Bounds = mLabels.at(l_Fullscreen).get_Bounds();
	position = sf::Vector2f(kp_tr.x - (dis_xfar + size_mini_button.x / 2), Bounds.top + Bounds.height / 2);
	a_Check.set_Position(position);
	a_Check.get_Bounds();
	a_Check.initValue(mMenu_Data.mData.IsFullScreen());
	mChecks.insert(std::pair<OptionsSelections, Check>(s_FullScreen, a_Check));
	//	Muzika NIJE GOTOVO
	a_Check = Check(texture, mMenu_Data.get_Check_tex_rects());
	a_Check.set_Size(size_mini_button);
	Bounds = mLabels.at(l_Music_switch).get_Bounds();
	position = sf::Vector2f(kp_tr.x - (dis_xfar + size_mini_button.x / 2), Bounds.top + Bounds.height / 2);
	a_Check.set_Position(position);
	a_Check.get_Bounds();
	a_Check.initValue(mMenu_Data.getMusicPlayer().is_Music_Playing());
	mChecks.insert(std::pair<OptionsSelections, Check>(s_Music_switch, a_Check));
	//	Zvukovi NIJE GOTOVO
	a_Check = Check(texture, mMenu_Data.get_Check_tex_rects());
	a_Check.set_Size(size_mini_button);
	Bounds = mLabels.at(l_Sound_switch).get_Bounds();
	position = sf::Vector2f(kp_tr.x - (dis_xfar + size_mini_button.x / 2), Bounds.top + Bounds.height / 2);
	a_Check.set_Position(position);
	a_Check.get_Bounds();
	a_Check.initValue(mMenu_Data.getResources().IsSoundOn());
	mChecks.insert(std::pair<OptionsSelections, Check>(s_Sound_switch, a_Check));
	//	Vsync
	a_Check = Check(texture, mMenu_Data.get_Check_tex_rects());
	a_Check.set_Size(size_mini_button);
	Bounds = mLabels.at(l_Vsync).get_Bounds();
	position = sf::Vector2f(kp_tr.x - (dis_xfar + size_mini_button.x / 2), Bounds.top + Bounds.height / 2);
	a_Check.set_Position(position);
	a_Check.get_Bounds();
	a_Check.initValue(mMenu_Data.mData.get_Vsync());
	mChecks.insert(std::pair<OptionsSelections, Check>(s_Vsync, a_Check));

	// Donja dugmad

	a_Button = Button(" Apply", font, ch_size);
	a_Button.set_Colors(color, sf::Color::Cyan, color);
	a_Button.toggle_DimText(true);
	a_Button.set_Size(size_button);
	Bounds = a_Button.get_Bounds();
	a_Button.set_Position(sf::Vector2f((size_button.x / 2) + dis_long, mMenu_Data.getMenu_Key_Positions(Menus::kp_BottomLeft_Corner).y - (dis_long + dis_near + (size_button.y / 2))));
	a_Button.set_Bounds();
	mButtons.insert(std::pair<OptionsSelections, Button>(s_Apply, a_Button));

	mApplyButton = false;

	a_Button = Button(" Back", font, ch_size);
	a_Button.set_Colors(color, sf::Color::Cyan, color);
	a_Button.set_Size(size_button);
	Bounds = a_Button.get_Bounds();
	a_Button.set_Position(sf::Vector2f(kp_br.x - (dis_long + (size_button.x / 2)), kp_br.y - (dis_long + dis_near + (size_button.y / 2))));
	a_Button.set_Bounds();
	mButtons.insert(std::pair<OptionsSelections, Button>(s_Back, a_Button));

	//------------------------------------------------------------------------//

	mMenu_Data.mRefreshed = true;	//	Zapravo, svako ce da ima sopstveni...
}