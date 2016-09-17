#include "stdafx.h"
#include "Label.h"

Label::Label(const sf::Font& font, std::string text, float char_size)
{
	mDefault_Text_Color = sf::Color::White;
	mDefault_Outline_Color = sf::Color::White;

	mLabel.setFont(font);
	mLabel.setString(text);
	mLabel.setCharacterSize(char_size);

	mOffset = sf::Vector2f(1, 1);

	mOutline.setFillColor(sf::Color::Transparent);
	mOutline.setOutlineColor(mDefault_Outline_Color);
	mOutline.setOutlineThickness(-2);
	mOutline.setSize(sf::Vector2f(100,100));
	mOutline.setPosition(100,50);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mOutline);
	target.draw(mLabel);
}

void Label::set_Size(sf::Vector2f param)
{
	mOutline.setSize(param);
	sf::FloatRect	bound_1 = mOutline.getLocalBounds();
	sf::FloatRect	bound_2 = mLabel.getLocalBounds();

	mOutline.setOrigin(bound_1.left + bound_1.width / 2, bound_1.top + bound_1.height / 2);
	bound_1 = mOutline.getGlobalBounds();
	mLabel.setPosition(bound_1.left + mOffset.x, bound_1.top + mOffset.y);
}

void Label::set_Scale(float param)
{
	mOffset = sf::Vector2f(5*param, 5*param);
	mLabel.setScale(sf::Vector2f(param, param));
	mOutline.setScale(sf::Vector2f(param, param));
}

void Label::set_Position(sf::Vector2f param)
{
	mOutline.setPosition(param);
	sf::FloatRect bound = mOutline.getGlobalBounds();
	mLabel.setPosition(bound.left + mOffset.x, bound.top + mOffset.y);
}

void Label::set_Availability(bool param)
{
	if (param)
	{
		mLabel.setColor(mDefault_Text_Color);
		mOutline.setOutlineColor(mDefault_Outline_Color);
	}
	else
	{
		mLabel.setColor(mDimmed_color);
		mOutline.setOutlineColor(mDimmed_color);
	}
}

void Label::set_Text(std::string new_text)
{
	mLabel.setString(new_text);
}

const std::string Label::get_Text() const
{
	return mLabel.getString();
}

const sf::FloatRect Label::get_Bounds() const
{
	return mOutline.getGlobalBounds();
}

void Label::set_Color(sf::Color Text_Color, sf::Color Outline_Color, sf::Color Dimmed_color)
{
	mDefault_Text_Color = Text_Color;
	mDefault_Outline_Color = Outline_Color;
	mDimmed_color = Dimmed_color;

	mLabel.setColor(mDefault_Text_Color);
	mOutline.setOutlineColor(mDefault_Outline_Color);

}
