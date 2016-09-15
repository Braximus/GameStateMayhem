#include "stdafx.h"
#include "Comet Wars UI Countdown.h"
#include "Comet Wars Data.h"

CometWars_UI_Countdown::CometWars_UI_Countdown(CometWarsData& data)
{
	mTime = sf::seconds(4);
	
	mText.setFont(data.getResources().getFont(ID_Global));
	mText.setCharacterSize(data.getCharacter_Size(CW::ch_Large));
	mText.setPosition(data.getKey_Position(CW::kp_Center));
	mText.setString(std::to_string(static_cast<UINT>(mTime.asSeconds())));
	sf::FloatRect bounds = mText.getLocalBounds();
	mText.setOrigin(bounds.width / 2, bounds.top - bounds.height / 2);
	mText.setColor(sf::Color::Cyan);
}

void CometWars_UI_Countdown::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mText, state);
}

void CometWars_UI_Countdown::update(sf::Time& time)
{
	mTime -= time;
	mText.setString(std::to_string(static_cast<UINT>(mTime.asSeconds())));
}

void CometWars_UI_Countdown::resetTimer()
{
	mTime = sf::seconds(4);
}

const float CometWars_UI_Countdown::getTimer() const
{
	return mTime.asSeconds();
}
