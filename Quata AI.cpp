#include "stdafx.h"
#include "Quata AI.h"
#include "Quata Data.h"

QuataAI::QuataAI(QuataData& data)
	: mData(data)
	, mPaddle(data, data.get_Texture_rects(Qua::intrect_AI))
{

}

Quata_Paddle* QuataAI::pass_pointer()
{
	return &mPaddle;
}

void QuataAI::update(sf::Time& time)
{
	mPaddle.update(time);
	mPaddle.setVelocity(sf::Vector2f(0, 0));
}

void QuataAI::move_Paddle(const sf::Vector2f& current_ball_pos, bool upper_border_collision, bool bottom_border_collision)
{
	float offset = mData.get_Distance(Qua::dis_VeryNear);
	float speed = 0;
	sf::Vector2f current_AI_pos = mPaddle.getPosition();
	if ((current_AI_pos.y + offset > current_ball_pos.y) && (current_AI_pos.y - offset > current_ball_pos.y))	
	{
		if (!upper_border_collision)
		{
			speed = -mData.get_Speed(Qua::speed_Paddle);
		}
	}
	else if ((current_AI_pos.y + offset < current_ball_pos.y) && (current_AI_pos.y - offset < current_ball_pos.y))
	{
		if (!bottom_border_collision)
		{
			speed = mData.get_Speed(Qua::speed_Paddle);
		}
	}

	mPaddle.setVelocity(sf::Vector2f(0, speed));
}

void QuataAI::reset_Paddle_Position()
{
	sf::Vector2f position = sf::Vector2f(mData.get_Key_Position(Qua::kp_Center_Screen).x + (mData.get_Object_Size(Qua::size_Playground).x / 2) - mData.get_Distance(Qua::dis_VeryNear), mData.get_Key_Position(Qua::kp_LeftCenter_Screen).y);
	mPaddle.setPosition(position);
}

const sf::FloatRect QuataAI::get_Paddle_Bounds() const
{
	return mPaddle.getBounds();
}

const sf::Vector2f QuataAI::get_Paddle_Position() const
{
	return mPaddle.getPosition();
}