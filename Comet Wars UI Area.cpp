#include "stdafx.h"
#include "Comet Wars UI Area.h"
#include "Comet Wars Data.h"

CometWars_UI_Area::CometWars_UI_Area(CometWarsData& data)
{
	mPosition = data.getUI_Position(CW::UI_Area);
	mRect.setPosition(mPosition);
	mRect.setSize(data.getObj_Sizes(CW::size_UI_Area));
	mRect.setFillColor(sf::Color(32, 128, 128, 64));
	mRect.setOutlineThickness(-1);
	mRect.setOutlineColor(sf::Color::Cyan);

	mBackgroundRect.setPosition(mPosition);
	mBackgroundRect.setSize(data.getObj_Sizes(CW::size_UI_Area));
	mBackgroundRect.setFillColor(sf::Color::Black);

}

void CometWars_UI_Area::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mBackgroundRect);
	target.draw(mRect);
}

void CometWars_UI_Area::update(sf::Time&)
{
	//
}
