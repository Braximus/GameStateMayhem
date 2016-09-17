#include "stdafx.h"
#include "Quata Paddle.h"
#include "Quata Data.h"

Quata_Paddle::Quata_Paddle(QuataData& data, sf::IntRect tex_area)
{
	mPaddle_rect.setSize(data.get_Object_Size(Qua::size_Paddle));
	sf::FloatRect b = mPaddle_rect.getLocalBounds();
	mPaddle_rect.setOrigin(b.width / 2, b.height / 2);
	mPaddle_rect.setTexture(&data.get_Resources().getTexture(ID_Quata));
	mPaddle_rect.setTextureRect(tex_area);
	mBounds = mPaddle_rect.getGlobalBounds();
}

void Quata_Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	target.draw(mPaddle_rect, state);
}

void Quata_Paddle::setPosition(sf::Vector2f new_position)
{
	mPaddle_rect.setPosition(new_position);
	mBounds = mPaddle_rect.getGlobalBounds();
}

const sf::Vector2f Quata_Paddle::getPosition() const
{
	return mPaddle_rect.getPosition();
}

void Quata_Paddle::setVelocity(sf::Vector2f param)
{
	mVelocity = param;
}

void Quata_Paddle::update(sf::Time& time)
{
	mPaddle_rect.move(mVelocity *time.asSeconds());
	mBounds = mPaddle_rect.getGlobalBounds();
}

