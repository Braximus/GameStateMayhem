#include "stdafx.h"
#include "Quata UI Text.h"
#include "Quata Data.h"


Quata_UI_Text::Quata_UI_Text(QuataData& data, sf::Vector2f pos)
{
	mText.setFont(data.get_Resources().getFont(ID_Global));
	mText.setString(std::to_string(0));
	mText.setCharacterSize(data.get_Character_Size(Qua::ch_Large));
	sf::FloatRect bound = mText.getLocalBounds();
	mText.setOrigin(bound.width / 2, bound.height / 2);
	mText.setPosition(pos);

}

void Quata_UI_Text::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mText, state);
}

void Quata_UI_Text::set_Text(UINT size, std::string text)
{
	mText.setCharacterSize(size);
	mText.setString(text);
}

void Quata_UI_Text::refresh_Text(std::string txt)
{
	mText.setString(txt);
}

void Quata_UI_Text::set_Text_Color(sf::Color param)
{
	mText.setColor(param);
}