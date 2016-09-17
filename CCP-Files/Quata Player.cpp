#include "stdafx.h"
#include "Quata Player.h"

Quata_Player::Quata_Player(QuataData& data)
	: mData(data)
	, mPaddle(data, data.get_Texture_rects(Qua::intrect_Player))
{
	
}

Quata_Paddle* Quata_Player::pass_pointer()
{
	return &mPaddle;
}

void Quata_Player::update(sf::Time& time)
{
	mPaddle.update(time);
	mPaddle.setVelocity(sf::Vector2f(0, 0));
}

void Quata_Player::move_Paddle(bool upward)
{
	if (upward)
	{
		mPaddle.setVelocity(sf::Vector2f(0, -mData.get_Speed(Qua::speed_Paddle)));
	}
	else
	{
		mPaddle.setVelocity(sf::Vector2f(0, mData.get_Speed(Qua::speed_Paddle)));
	}
}

void Quata_Player::reset_Paddle_position()
{
	sf::Vector2f position = sf::Vector2f( mData.get_Key_Position(Qua::kp_Center_Screen).x - (mData.get_Object_Size(Qua::size_Playground).x / 2) + mData.get_Distance(Qua::dis_VeryNear), mData.get_Key_Position(Qua::kp_LeftCenter_Screen).y);
	mPaddle.setPosition(position);
}

const sf::FloatRect Quata_Player::get_Paddle_Bounds() const
{
	return mPaddle.getBounds();
}

const sf::Vector2f Quata_Player::get_Paddle_Position() const
{
	return mPaddle.getPosition();
}
