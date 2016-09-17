#include "stdafx.h"
#include "Main_Menu.h"
#include "DataStorage.h"

MainMenu::MainMenu(MenuData& data)
	:mMenu_Data(data)
{
	refresh();
	mCurrentSelection = None;
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mTitle);
	for (const auto& it : mButtons)
	{
		target.draw(it.second, state);
	}
}

void MainMenu::update(sf::Time& time)
{
	if (!mMenu_Data.mRefreshed)
	{
		refresh();
	}

	if (mPreviousSelection != mCurrentSelection)
	{
		if (mCurrentSelection != None)
		{
			mMenu_Data.Play_Sound(Menus::snd_Hover);
		}
		mPreviousSelection = mCurrentSelection;
	}

}

void MainMenu::handleEvents(sf::Event& Event)
{
	KeyboardEvents(Event);
	MouseEvents(Event);

}

void MainMenu::KeyboardEvents(sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
	
		if (Event.key.code == sf::Keyboard::Up)
		{
			if (mCurrentSelection == Choose_Game)
				mCurrentSelection = Exit;
			else if (mCurrentSelection == Exit)
				mCurrentSelection = Options;
			else if (mCurrentSelection == Options)
				mCurrentSelection = Credits;
			else if (mCurrentSelection == Credits)
				mCurrentSelection = Choose_Game;
		}
		if (Event.key.code == sf::Keyboard::Down || (Event.key.code == sf::Keyboard::Tab))
		{
			if (mCurrentSelection == Choose_Game)
				mCurrentSelection = Options;
			else if (mCurrentSelection == Options)
				mCurrentSelection = Credits;
			else if (mCurrentSelection == Credits)
				mCurrentSelection = Exit;
			else if (mCurrentSelection == Exit)
				mCurrentSelection = Choose_Game;
		}
		if (Event.key.code == sf::Keyboard::Return)
		{
			if (mCurrentSelection == Options)
			{
				mMenu_Data.ChangeSubState(Menus::Options_Menu);			
			}
			else if (mCurrentSelection == Choose_Game)
				mMenu_Data.ChangeSubState(Menus::Choose_Game_Menu);
			else if (mCurrentSelection == Exit)
				mMenu_Data.Close();
			else if (mCurrentSelection == Credits)
				mMenu_Data.ChangeSubState(Menus::Credits_Menu);
		}
	}
}

void MainMenu::MouseEvents(sf::Event& Event)
{
	if (Event.type == sf::Event::MouseButtonReleased)
	{
		
		if (Event.mouseButton.button == sf::Mouse::Left) 
		{
			
			if (mCurrentSelection == Exit)
				mMenu_Data.Close();
			else if (mCurrentSelection == Options)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				mMenu_Data.ChangeSubState(Menus::Options_Menu);
				
			}
			else if (mCurrentSelection == Choose_Game)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				mMenu_Data.ChangeSubState(Menus::Choose_Game_Menu);
			}
			else if (mCurrentSelection == Credits)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				mMenu_Data.ChangeSubState(Menus::Credits_Menu);
			}
	
		}
	}

}

void MainMenu::handleRealTimeInput()
{
	bool da_li_je_van = true;

	for (auto& it : mButtons)
	{
		if (it.second.check_Bounds(static_cast<sf::Vector2f>(mMenu_Data.MouseCoord())))
		{
			da_li_je_van = false;
			mCurrentSelection = it.first;
	
			it.second.ToggleSelection_ByColor(true);
		}
		else
		{
			it.second.ToggleSelection_ByColor(false);
		}
		
	}
	if (da_li_je_van)
	{
		mCurrentSelection = None;
	}

}

void MainMenu::refresh()
{
	if (!mButtons.empty())
	{
		mButtons.erase(mButtons.begin(), mButtons.end());
	
	}
	sf::Color color = sf::Color(32, 128, 128, 128);

	mTitle = Title(mMenu_Data.getResources().getTexture(ID_Menu), sf::IntRect(100, 0, 800, 366), mMenu_Data.getMenu_Object_Sizes(Menus::size_Title), mMenu_Data.getMenu_Key_Positions(Menus::kp_Center_UpperHalf_Screen));
	
	sf::Vector2f	position;
	Button			a_Button;
	sf::FloatRect	temp_bounds;

	//	First Button
	a_Button = Button("Choose Game", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	position = sf::Vector2f(mTitle.get_Borders().left + mTitle.get_Borders().width / 2, mTitle.get_Borders().top + mTitle.get_Borders().height + mMenu_Data.getMenu_Distances(Menus::dis_VeryFar)/**sc_coef*/);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	temp_bounds = a_Button.get_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	mButtons.insert(std::pair<MenuSelection, Button>(Choose_Game, a_Button));
	//	Second Button
	a_Button = Button("Options", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	position = sf::Vector2f(temp_bounds.left + temp_bounds.width / 2, temp_bounds.top + 3 * temp_bounds.height / 2 + mMenu_Data.getMenu_Distances(Menus::dis_VeryNear)/**sc_coef*/);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	temp_bounds = a_Button.get_Bounds();
	mButtons.insert(std::pair<MenuSelection, Button>(Options, a_Button));
	//	Third Button
	a_Button = Button("Credits", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	position = sf::Vector2f(temp_bounds.left + temp_bounds.width / 2, temp_bounds.top + 3 * temp_bounds.height / 2 + mMenu_Data.getMenu_Distances(Menus::dis_VeryNear)/**sc_coef*/);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	temp_bounds = a_Button.get_Bounds();
	mButtons.insert(std::pair<MenuSelection, Button>(Credits, a_Button));
	//	Fourth Button
	a_Button = Button("Exit", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	position = sf::Vector2f(temp_bounds.left + temp_bounds.width / 2, temp_bounds.top + 3 * temp_bounds.height / 2 + mMenu_Data.getMenu_Distances(Menus::dis_VeryNear)/**sc_coef*/);
	a_Button.set_Position(position);
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	mButtons.insert(std::pair<MenuSelection, Button>(Exit, a_Button));
}
