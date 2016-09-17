#include "stdafx.h"
#include "Buttons.h"

#include "DataStorage.h"

Button::Button(std::string button_name, const sf::Font& font, float Char_size)
{
	mDefault_Text_position = pos_Left;

	mDefault_Selection_Color = sf::Color(32, 32, 32, 255);
	mSelection.setFillColor(mDefault_Selection_Color);
	mSelection.setSize(sf::Vector2f(10,10));		
	mSelection.setPosition(sf::Vector2f(0,0));

	mDefault_Text_Color = sf::Color::White;	
	mText.setFont(font);
	mText.setCharacterSize(Char_size);
	mText.setString(button_name);

	misSelected = false;
}

Button::Button(const sf::Texture& texture, sf::IntRect tex_rect)
{
	mDefault_Text_position = pos_Left;

	mSelection.setTexture(&texture);
	mSelection.setTextureRect(tex_rect);
	mStandard_tex_rect = tex_rect;
	mSelection.setSize(sf::Vector2f(10,10));
	mSelection.setPosition(sf::Vector2f(0,0));

	misSelected = false;
}


void Button::set_Size(sf::Vector2f param)
{
	mSelection.setSize(param);
	sf::FloatRect Bounds = mSelection.getLocalBounds();
	mSelection.setOrigin(Bounds.width / 2, Bounds.height / 2);
	set_Text_Position(mDefault_Text_position);
}

void Button::set_Colors(sf::Color selection, sf::Color text, sf::Color dimmed)
{
	mDefault_Selection_Color = selection;
	mSelection.setFillColor(mDefault_Selection_Color);
	mDimmed_Color = dimmed;

	mDefault_Text_Color = text;
	mText.setColor(mDefault_Text_Color);
}

void Button::insert_Scale(float scale_coef)
{
	mText.setScale(sf::Vector2f(scale_coef, scale_coef));
	mSelection.setScale(sf::Vector2f(scale_coef, scale_coef));
}

void Button::set_Position(sf::Vector2f param)
{
	mSelection.setPosition(param);
	sf::FloatRect Bounds = mSelection.getGlobalBounds();
	mText.setPosition(Bounds.left, Bounds.top + Bounds.height / 2);
}

void Button::set_Text_Position(Text_pos param)
{
	//	Top and left aren't equeal to zero when taking their local bounds. 

	sf::FloatRect t_bounds = mText.getLocalBounds();
	sf::FloatRect sel_bounds = mSelection.getGlobalBounds();
	mDefault_Text_position = param;
	if (param == pos_Right)
	{
		mText.setOrigin(t_bounds.width + 2*t_bounds.left, t_bounds.top + t_bounds.height / 2);
		mText.setPosition(sel_bounds.left + sel_bounds.width, sel_bounds.top + sel_bounds.height / 2);
	}
	else if (param == pos_Center)
	{
		mText.setOrigin( (2 * t_bounds.left) +(t_bounds.width / 2), t_bounds.top + t_bounds.height / 2);
		mText.setPosition(sel_bounds.left + sel_bounds.width / 2, sel_bounds.top + sel_bounds.height / 2);
	}
	else
	{
		mText.setOrigin(-2 * t_bounds.left, t_bounds.top + t_bounds.height / 2);
		mText.setPosition(sel_bounds.left, sel_bounds.top + sel_bounds.height / 2);
	}
}

void Button::set_Bounds()
{
	mBounds = mSelection.getGlobalBounds();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mSelection);
	target.draw(mText);
}

void Button::ToggleSelection_ByColor(bool on_off)
{
	if (on_off)
	{
		sf::Uint8 r = mDefault_Selection_Color.r + 64;
		sf::Uint8 g = mDefault_Selection_Color.g + 64;
		sf::Uint8 b = mDefault_Selection_Color.b + 64;
		sf::Uint8 a = mDefault_Selection_Color.a;
		mSelection.setFillColor(sf::Color(r, g, b, a));
	}
	else
	{
		mSelection.setFillColor(mDefault_Selection_Color);
	}
}

void Button::ToggleSelection_ByTexRect(bool on_off)
{
	if (on_off)
	{
		if (!misSelected)
		{
			mSelection.setTextureRect(sf::IntRect(mStandard_tex_rect.left + 250, mStandard_tex_rect.top, mStandard_tex_rect.width, mStandard_tex_rect.height));
			misSelected = true;
		}
	}
	else
	{
		if (misSelected)
		{
			mSelection.setTextureRect(mStandard_tex_rect);
			misSelected = false;
		}
		
	}

}

const bool Button::check_Bounds(sf::Vector2f entity_position) const
{
	if (mBounds.contains(entity_position))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::change_Texture_rect(sf::IntRect param)
{
	mStandard_tex_rect = param;
	mSelection.setTextureRect(param);
	misSelected = false;
}

const sf::FloatRect Button::get_Bounds() const
{
	return mBounds;
}

void Button::toggle_DimText(bool on_off)
{
	if (on_off)
	{
		mText.setColor(mDimmed_Color);
	}
	else
	{
		mText.setColor(mDefault_Text_Color);
	}
}

void Button::change_Button_name(std::string param)
{
	mText.setString(param);
}

const std::string Button::getButton_name() const
{
	return mText.getString();
}
