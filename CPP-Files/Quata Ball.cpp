#include "stdafx.h"
#include "Quata Ball.h"
#include "Quata Data.h"
#include "Debug.h"

Quata_Ball::Quata_Ball(QuataData& data)
	:mData(data)
{
	mBall_circle.setFillColor(sf::Color::White);
	mBall_circle.setTexture(&data.get_Resources().getTexture(ID_Quata));
	mBall_circle.setTextureRect(data.get_Texture_rects(Qua::intrect_Ball));
	sf::Vector2f temp_ball = data.get_Object_Size(Qua::size_Ball);
	mBall_circle.setRadius(temp_ball.x);
	sf::FloatRect	bound = mBall_circle.getLocalBounds();
	mBall_circle.setOrigin(bound.width / 2, bound.height / 2);	
	mBall_circle.setPosition(data.get_Key_Position(Qua::kp_Center_Screen));

	mAngle = 0;
	mSpeed = 0;
}

void Quata_Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	target.draw(mBall_circle, state);
}

void Quata_Ball::update(sf::Time& time)
{
	mBall_circle.move(mVelocity*time.asSeconds());
	mPosition = mBall_circle.getPosition();
	mBounds = mBall_circle.getGlobalBounds();
}

void Quata_Ball::setPosition(sf::Vector2f param)
{
	mPosition = param;
	mBall_circle.setPosition(param);
	mBounds = mBall_circle.getGlobalBounds();
	mSpeed = 0;
	mAngle = 0;
}


void Quata_Ball::setVelocity(sf::Vector2f param)
{
	mVelocity = param;
}

const sf::Vector2f Quata_Ball::getVelocity() const
{
	return mVelocity;
}

void Quata_Ball::setAngle(float param)
{
	mAngle = param;
}

float Quata_Ball::increaseSpeed()
{
	//	Here I am increasing the speed by 50, if it is less than 1000;
	if (mSpeed <= mData.get_Speed(Qua::speed_Ball_max))
	{
		mSpeed += mData.get_Speed(Qua::speed_Ball_increase);
	}
	return mSpeed;
}

float Quata_Ball::reset_speed()
{
	return mSpeed = mData.get_Speed(Qua::speed_Ball_nominal);
}

void Quata_Ball::set_Ball_Transparency(bool is_Transparent)
{
	if (is_Transparent)
	{
		mBall_circle.setFillColor(sf::Color::Transparent);
	}
	else
	{
		mBall_circle.setFillColor(sf::Color::White);
	}
}
