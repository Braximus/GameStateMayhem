#include "stdafx.h"
#include "Comet Wars UI Splashscreen.h"
#include "Comet Wars Data.h"

CometWars_UI_SplashScreen::CometWars_UI_SplashScreen(CometWarsData& data)
{
	mArea.setSize(data.getObj_Sizes(CW::size_SplashScreen));
	mArea.setPosition(data.getKey_Position(CW::kp_Center));
	mArea.setOutlineThickness(2);
	mArea.setOutlineColor(sf::Color::Cyan);
	mArea.setFillColor(sf::Color(32, 128, 128, 32));
	sf::FloatRect bounds = mArea.getLocalBounds();
	mArea.setOrigin(bounds.width / 2, bounds.height / 2);

	mText.setFont(data.getResources().getFont(ID_Global));
	mText.setCharacterSize(data.getCharacter_Size(CW::ch_Medium));
	mText.setColor(sf::Color::Cyan);
}

void CometWars_UI_SplashScreen::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mArea);
	target.draw(mText);
}

void CometWars_UI_SplashScreen::update(sf::Time&)
{
	//
}

void CometWars_UI_SplashScreen::setText(std::string param)
{
	mText.setString(param);
	sf::FloatRect bounds = mText.getLocalBounds();
	mText.setOrigin(bounds.width / 2, bounds.top + (bounds.height / 2));
	mText.setPosition(mArea.getPosition());
}
