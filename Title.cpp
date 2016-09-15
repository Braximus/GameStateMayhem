#include "stdafx.h"
#include "Title.h"


Title::Title(const sf::Texture& teks, sf::IntRect texture_rect, sf::Vector2f size, sf::Vector2f position)
{
	mTitle.setTexture(&teks);
	mTitle.setTextureRect(texture_rect);
	mTitle.setPosition(position);
	mTitle.setSize(size);
	sf::FloatRect bound = mTitle.getLocalBounds();
	mTitle.setOrigin(bound.width / 2, bound.height / 2);

}

void Title::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mTitle);
}

const sf::Vector2f Title::get_Position() const
{
	return mTitle.getPosition();
}

const sf::FloatRect Title::get_Borders() const
{
	return mTitle.getGlobalBounds();
}