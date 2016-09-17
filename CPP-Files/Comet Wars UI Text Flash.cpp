#include "stdafx.h"
#include "Comet Wars UI Text Flash.h"
#include "Comet Wars Data.h"

CometWars_UI_Text_Flash::CometWars_UI_Text_Flash(CometWarsData& data)
{
	mText.setFont(data.getResources().getFont(ID_Global));
	mText.setCharacterSize(data.getCharacter_Size(CW::ch_Medium));
	mText.setString(data.getText(CW::txt_Text_Flash));
	sf::FloatRect bound = mText.getLocalBounds();
	mText.setOrigin(bound.width / 2, (bound.height - (mText.getCharacterSize() - bound.top)) / 2);
	mPosition = data.getUI_Position(CW::UI_Text_Flash);
	mText.setPosition(mPosition);
	mText.setColor(sf::Color(0, 128, 255, 0));

	fade_in = true;
	fade_out = false;
}

void CometWars_UI_Text_Flash::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mText,state);
}

void CometWars_UI_Text_Flash::update(sf::Time& time)
{
	sf::Color tmp_col = mText.getColor();
	sf::Uint8 r = tmp_col.r;
	sf::Uint8 g = tmp_col.g;
	sf::Uint8 b = tmp_col.b;
	int a = tmp_col.a;
	if (fade_in)
	{
		a += 5;
		if (a >= 255)
		{
			a = 255;
			fade_in = false;
			fade_out = true;
		}
	}
	else if (fade_out)
	{
		a -= 5;
		if (a <= 0)
		{
			a = 0;
			fade_out = false;
		}
	}
	a = static_cast<sf::Uint8>(a);
	mText.setColor(sf::Color(r, g, b, a));
}
