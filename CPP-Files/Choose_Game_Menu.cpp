#include "stdafx.h"
#include "Choose_Game_Menu.h"
#include "DataStorage.h"


ChooseMenu::ChooseMenu(MenuData& data)
	:mMenu_Data(data)
{
	mDescriptionName.insert(std::pair<GameChoice, std::string>(None, "tekstovi/NoDescription.txt"));
	mDescriptionName.insert(std::pair<GameChoice, std::string>(Back, "tekstovi/NoDescription.txt"));
	mDescriptionName.insert(std::pair<GameChoice, std::string>(CometWars, "tekstovi/CometWars.txt"));
	mDescriptionName.insert(std::pair<GameChoice, std::string>(Quata, "tekstovi/Quata.txt"));
	mDescriptionName.insert(std::pair<GameChoice, std::string>(BreakTrough, "tekstovi/BreakTrough.txt"));
	refresh();

	mCurrentSelection = None;
}

void ChooseMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mDescription, state);
	for (const auto& it : mButtons)
		target.draw(it.second, state);
	target.draw(mLabel, state);
}

void ChooseMenu::update(sf::Time& time)
{
	if (!mMenu_Data.mRefreshed)
	{
		refresh();
	}
	if (mCurrentSelection != mPreviousSelection)
	{
		if (mCurrentSelection != None)
		{
			mMenu_Data.Play_Sound(Menus::snd_Hover);
		}
		mPreviousSelection = mCurrentSelection;
	}	
}

void ChooseMenu::handleEvents(sf::Event& Event)
{
	KeyboardEvents(Event);
	MouseEvents(Event);
}

void ChooseMenu::KeyboardEvents(sf::Event& Event)
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Up)
		{
			if (mCurrentSelection == Quata)
			{
				mCurrentSelection = Back;
			}
			else if (mCurrentSelection == Back)
			{
				mCurrentSelection = BreakTrough;
			}
			else if (mCurrentSelection == BreakTrough)
			{
				mCurrentSelection = CometWars;
			}
			else if (mCurrentSelection == CometWars)
			{
				mCurrentSelection = Quata;
			}
		}
		if (Event.key.code == sf::Keyboard::Down || (Event.key.code == sf::Keyboard::Tab))
		{
			if (mCurrentSelection == Quata)
			{
				mCurrentSelection = CometWars;
			}
			else if (mCurrentSelection == CometWars)
			{
				mCurrentSelection = BreakTrough;
			}
			else if (mCurrentSelection == BreakTrough)
			{
				mCurrentSelection = Back;
			}
			else if (mCurrentSelection == Back)
			{
				mCurrentSelection = Quata;
			}
		}
		if (Event.key.code == sf::Keyboard::Return)
		{
			if (mCurrentSelection == Back)
			{
				mMenu_Data.ChangeSubState(Menus::Main_Menu);
			}
			else if (mCurrentSelection == Quata)
			{
				mMenu_Data.ChangeState(e_Quata);
			}
		}
	}
}

void ChooseMenu::MouseEvents(sf::Event& Event)
{
	if (Event.type == sf::Event::MouseButtonReleased)
	{
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (mCurrentSelection == Back)
			{
				mMenu_Data.Play_Sound(Menus::snd_Escape);
				mMenu_Data.ChangeSubState(Menus::Main_Menu);
			}
			else if (mCurrentSelection == Quata)		
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				mMenu_Data.ChangeState(e_Quata);
			}
			else if (mCurrentSelection == CometWars)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				mMenu_Data.ChangeState(e_CometWars);
			}
			else if (mCurrentSelection == BreakTrough)
			{
				mMenu_Data.Play_Sound(Menus::snd_Select);
				mMenu_Data.ChangeState(e_BreakTrough);
			}

		}
	}
}

void ChooseMenu::handleRealTimeInput()
{
	bool is_it_outside = true;
	for (auto& it : mButtons)
	{
		if (it.second.check_Bounds((static_cast<sf::Vector2f>(mMenu_Data.MouseCoord()))))
		{
			is_it_outside = false;
			mCurrentSelection = it.first;
			it.second.ToggleSelection_ByColor(true);
			Change_Description(mDescriptionName.at(mCurrentSelection));
		}
		else
		{
			it.second.ToggleSelection_ByColor(false);
		}
	}
	if (is_it_outside)
	{
		mCurrentSelection = None;
		Change_Description(mDescriptionName.at(mCurrentSelection));
	}
}

void ChooseMenu::Change_Description(std::string param)
{
	std::string			text;
	char				letter;
	std::ifstream		file(param);
	while (file.get(letter))
	{
		text.push_back(letter);
	}
	file.close();

	mLabel.set_Text(text);
}

void ChooseMenu::refresh()
{
	sf::Color color = sf::Color(32, 128, 128, 128);
	Button a_Button;
	float x = (static_cast<float>(mMenu_Data.getMenu_Key_Positions(Menus::kp_Center_Screen).x));
	float y = (static_cast<float>(mMenu_Data.getMenu_Key_Positions(Menus::kp_Center_Screen).y));

	if (!mButtons.empty())
	{
		mButtons.erase(mButtons.begin(), mButtons.end());
	}
	//	Prvo dugme
	a_Button = Button(" Quata", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	a_Button.set_Position(sf::Vector2f(x + mMenu_Data.getMenu_Distances(Menus::dis_ExtremlyFar), y - 2 * mMenu_Data.getMenu_Distances(Menus::dis_Medium)));
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	mButtons.insert(std::pair<GameChoice, Button>(Quata, a_Button));
	//	Drugo dugme
	a_Button = Button(" Comet Wars", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	a_Button.set_Position(sf::Vector2f(x + mMenu_Data.getMenu_Distances(Menus::dis_ExtremlyFar), y - mMenu_Data.getMenu_Distances(Menus::dis_Medium)));
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	mButtons.insert(std::pair<GameChoice, Button>(CometWars, a_Button));
	//	Trece dugme
	a_Button = Button(" BreakTrough", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	a_Button.set_Position(sf::Vector2f(x + mMenu_Data.getMenu_Distances(Menus::dis_ExtremlyFar), y));
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	mButtons.insert(std::pair<GameChoice, Button>(BreakTrough, a_Button));
	//	Cetvrto dugme
	a_Button = Button(" Back", mMenu_Data.getResources().getFont(ID_Global), mMenu_Data.getMenu_Char_Sizes(Menus::ch_Medium));
	a_Button.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_Button));
	a_Button.set_Position(sf::Vector2f(x + mMenu_Data.getMenu_Distances(Menus::dis_ExtremlyFar), y + mMenu_Data.getMenu_Distances(Menus::dis_Medium)));
	a_Button.set_Bounds();
	a_Button.set_Colors(color, sf::Color::Cyan);
	mButtons.insert(std::pair<GameChoice, Button>(Back, a_Button));
	//	Oznaka
	mLabel = Label(mMenu_Data.getResources().getFont(ID_Global), "", mMenu_Data.getMenu_Char_Sizes(Menus::ch_Small));
	mLabel.set_Size(mMenu_Data.getMenu_Object_Sizes(Menus::size_HugeLabel));
	mLabel.set_Position(sf::Vector2f(x - mMenu_Data.getMenu_Distances(Menus::dis_ExtremlyFar), y));
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan);
	Change_Description("tekstovi/NoDescription.txt");
	//	Opis
	mDescription.setFont(mMenu_Data.getResources().getFont(ID_Global));
	mDescription.setCharacterSize(mMenu_Data.getMenu_Char_Sizes(Menus::ch_Small));
	mDescription.setString("Description: ");
	mDescription.setStyle(sf::Text::Style::Bold);
	mDescription.setColor(sf::Color::Cyan);
	mDescription.setPosition(mLabel.get_Bounds().left, mLabel.get_Bounds().top - mDescription.getFont()->getLineSpacing(mMenu_Data.getMenu_Char_Sizes(Menus::ch_Small)));

	mMenu_Data.mRefreshed = true;

}
