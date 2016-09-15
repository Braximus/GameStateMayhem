#include "stdafx.h"
#include "Quata UI SplashScreen.h"


Quata_SplashScreen::Quata_SplashScreen(QuataData& data, const std::string info)
{
	mText.setFont(data.get_Resources().getFont(ID_Global));
	mText.setCharacterSize(data.get_Character_Size(Qua::ch_Medium));
	mText.setString(info);
	mText.setColor(sf::Color::Red);
	sf::FloatRect bound = mText.getLocalBounds();
	mText.setOrigin(bound.width / 2, 0);

	mRect.setFillColor(sf::Color(140, 0, 0, 128));
	mRect.setOutlineColor(sf::Color::Red);
	mRect.setOutlineThickness(-2.0f);
	mRect.setSize(data.get_Object_Size(Qua::size_SplashScreen));

	
	bound = mRect.getLocalBounds();
	mRect.setOrigin(bound.width / 2, 0);
	mRect.setPosition(data.get_Key_Position(Qua::kp_Center_Screen));
	
	mText.setPosition(mRect.getPosition());
	
}

void Quata_SplashScreen::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	target.draw(mRect, state);
	target.draw(mText, state);
}
