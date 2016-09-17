#include "stdafx.h"
#include "DropDownMenu.h"

DropDownMenu::DropDownMenu(const sf::Font& font, const sf::Texture& texture, float char_size, sf::IntRect tex_rect, sf::Vector2f size, sf::Vector2f position, std::vector<std::string> container_of_names)
{
	
	mNumber_Of_ShownChoices = 5;
	mBegining_Number = 0;

	mChoicesNames = container_of_names;

	mCurrentSelection = Label(font, " ", char_size);
	mCurrentSelection.set_Size(sf::Vector2f(5*size.x/6, size.y));
	mCurrentSelection.set_Color(sf::Color::Cyan, sf::Color::Cyan);
	mCurrentSelection.set_Position(position);

	sf::FloatRect bounds = mCurrentSelection.get_Bounds();
	sf::Vector2f size2 = sf::Vector2f(bounds.width / 6, bounds.height);
	sf::Vector2f pos2 = sf::Vector2f(bounds.left + bounds.width + size2.x / 2, bounds.top + bounds.height - size2.y / 2);

	mActivation_Button = Button(texture, tex_rect);
	mActivation_Button.set_Size(size2);
	mActivation_Button.set_Position(pos2);
	mActivation_Button.set_Bounds();

	sf::Vector2f new_pos = sf::Vector2f(bounds.left, bounds.top + bounds.height / 2);
	mOutline_size = size.y * mNumber_Of_ShownChoices;
	UINT Current_Choices_shown = mBegining_Number + mNumber_Of_ShownChoices;
	if (Current_Choices_shown > mChoicesNames.size())
	{
		mBegining_Number = mChoicesNames.size() - mNumber_Of_ShownChoices;
		Current_Choices_shown = mBegining_Number + mNumber_Of_ShownChoices;
	}

	bounds = mActivation_Button.get_Bounds();
	sf::Vector2f pos3  = sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height + mOutline_size / 4);
	sf::Vector2f size3 = sf::Vector2f(bounds.width, mOutline_size / 2);
	sf::IntRect tex_rect2 = sf::IntRect(tex_rect.left, tex_rect.top + 110, tex_rect.width, tex_rect.height);

	mScrollUp_Button = Button(texture, tex_rect2);
	mScrollUp_Button.set_Size(size3);
	mScrollUp_Button.set_Position(pos3);
	mScrollUp_Button.set_Bounds();

	sf::Vector2f pos4 = sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height + mOutline_size / 2 + mOutline_size / 4);
	mScrollDown_Button = Button(texture, tex_rect);
	mScrollDown_Button.set_Size(size3);
	mScrollDown_Button.set_Position(pos4);
	mScrollDown_Button.set_Bounds();

	bounds = mCurrentSelection.get_Bounds();
	UINT n = 0;
	float ch = char_size;
	for (UINT i = mBegining_Number; i < mNumber_Of_ShownChoices; ++i)
	{
		Button but = Button(mChoicesNames.at(i), font, ch);
		but.set_Size(sf::Vector2f(bounds.width, bounds.height));
		but.set_Position(sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + (bounds.height * (n + 1) + bounds.height / 2)));
		but.set_Bounds();
		but.set_Colors(sf::Color(16, 64, 64, 255), sf::Color::Cyan);
		mChoices.push_back(but);
		n++;
	}
	mCurrentState = false;	
}

void DropDownMenu::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mCurrentSelection);
	target.draw(mActivation_Button);
	if (mCurrentState)
	{
		target.draw(mScrollUp_Button);
		target.draw(mScrollDown_Button);
		for (const Button& it : mChoices)
		{
			target.draw(it);
		}
	}
}

void DropDownMenu::Activate()
{
	if (mCurrentState)
	{
		mActivation_Button.change_Texture_rect(sf::IntRect(0, 400, 107, 107));
		mCurrentState = false;
	}
	else
	{
		mActivation_Button.change_Texture_rect(sf::IntRect(110, 400, 107, 107));
		mCurrentState = true;
	}
}

//	This function is used durring pollEvent();
void DropDownMenu::choose(sf::Vector2f param)	
{
	if (mActivation_Button.check_Bounds(param))
	{
		Activate();
	}	
	if (mCurrentState)
	{
		bool refresh = false;
	
		for (Button& it : mChoices)
		{			
			if (it.check_Bounds(param))
			{
				std::vector<std::string>::iterator it2 = std::find(mChoicesNames.begin(), mChoicesNames.end(), it.getButton_name());
				size_t size = std::distance(mChoicesNames.begin(), it2);
				change_Label(size);
				mValue = size;
				return_value();
				Activate();
			}
			
		}
		if (mScrollUp_Button.check_Bounds(param))
		{
			mScrollUp_Button.change_Texture_rect(sf::IntRect(110, 510, 107, 107));
			if (mBegining_Number != 0)
			{
				mBegining_Number--;
			}
			refresh = true;
		}
		else if (mScrollDown_Button.check_Bounds(param))
		{
			mScrollDown_Button.change_Texture_rect(sf::IntRect(110, 400, 107, 107));
			UINT Current_Choices_shown = mBegining_Number + mNumber_Of_ShownChoices;
			if (!(Current_Choices_shown > mChoicesNames.size() - 1))
			{
				mBegining_Number++;
			}
			refresh = true;
		}

		if (refresh)
		{
			UINT i = mBegining_Number;
			for (Button& it : mChoices)
			{
				it.change_Button_name(mChoicesNames.at(i));
				i++;
			}
			
		}
	}
}

//	This function is used during real time update
bool DropDownMenu::hover(sf::Vector2f param)	
{
	if (mBound_Of_DropDownMenu.contains(param))
	{
		if (mActivation_Button.check_Bounds(param))
		{
			mActivation_Button.ToggleSelection_ByTexRect(true);
		}
		else
		{
			mActivation_Button.ToggleSelection_ByTexRect(false);
		}
		if (mCurrentState)
		{
			if (mScrollUp_Button.check_Bounds(param))
			{
				mScrollUp_Button.ToggleSelection_ByTexRect(true);
			}
			else
			{
				mScrollUp_Button.ToggleSelection_ByTexRect(false);
			}
			if (mScrollDown_Button.check_Bounds(param))
			{
				mScrollDown_Button.ToggleSelection_ByTexRect(true);
			}
			else
			{
				mScrollDown_Button.ToggleSelection_ByTexRect(false);
			}
			for (Button& it : mChoices)
			{
				if (it.check_Bounds(param))
				{
					it.ToggleSelection_ByColor(true);
				}
				else
				{
					it.ToggleSelection_ByColor(false);
				}
			}
		}

		return true;
	}
	else
	{
		mActivation_Button.ToggleSelection_ByTexRect(false);
		return false;
	}
}

const sf::FloatRect DropDownMenu::get_Bounds() 
{
	sf::FloatRect b1 = mCurrentSelection.get_Bounds();
	sf::FloatRect b2 = mActivation_Button.get_Bounds();

	if (mCurrentState)
	{
		mBound_Of_DropDownMenu = sf::FloatRect(b1.left, b1.top, b1.width + b2.width, b1.height + mOutline_size);
	}
	else
	{
		mBound_Of_DropDownMenu = sf::FloatRect(b1.left, b1.top, b1.width + b2.width, b1.height);
	}
	return mBound_Of_DropDownMenu;
}

void DropDownMenu::change_Label(UINT param)
{
	mValue = param;
	mCurrentSelection.set_Text(mChoicesNames.at(param));
}

const UINT DropDownMenu::return_value() const
{
	return mValue;
}

void DropDownMenu::release()
{
	mScrollDown_Button.change_Texture_rect(sf::IntRect(0, 400, 107, 107));
	mScrollUp_Button.change_Texture_rect(sf::IntRect(0, 510, 107, 107));
}

void DropDownMenu::force_close()
{
	mActivation_Button.change_Texture_rect(sf::IntRect(0, 400, 107, 107));
	mCurrentState = false;
}
