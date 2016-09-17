#include "stdafx.h"
#include "Quata Level.h"
#include "Quata Data.h"
#include "Debug.h"

Quata_Level::Quata_Level(QuataData& data)
	: mData(data)
	, mBall(data)
	, mPlayField(data)
{
	mBall_cooldown_time = sf::seconds(0);
	is_ball_on_cooldown = false;
}

std::deque<QuataObjects*> Quata_Level::pass_pointers()
{
	std::deque<QuataObjects*>	cont_of_ptr;
	cont_of_ptr.push_back(&mPlayField);
	cont_of_ptr.push_back(&mBall);

	return cont_of_ptr;
}

void Quata_Level::update(sf::Time& time)
{
	if (!is_ball_on_cooldown)
	{
		mBall.update(time);
	}
	else
	{
		ball_cooldown(time);
	}
	DebugClass::nums[2] = sf::Vector2i(mBall.getPosition());
	DebugClass::nums[3] = sf::Vector2i(mBall.getVelocity());
}

void Quata_Level::start_ball()
{
	mBall.set_Ball_Transparency(false);
	float speed = mBall.reset_speed();		
	float angle;

	std::uniform_int_distribution<int>	dis(0, 1);
	int i = dis(mData.get_Random_Engine());
	if (i == 1)
	{
		std::uniform_int_distribution<int>	distributor(-45, 45);
		angle = distributor(mData.get_Random_Engine());
	}
	else
	{
		std::uniform_int_distribution<int>	distributor(135, 225);
		angle = distributor(mData.get_Random_Engine());
	}

	DebugClass::angle = angle;
	DebugClass::speed = speed;
	angle = angle*(3.14 / 180);

	float x = cos(angle);
	float y = sin(angle);

	mBall.setVelocity(sf::Vector2f(x * speed, y * speed));

}

void Quata_Level::reset_ball()
{
	mBall.setPosition(mData.get_Key_Position(Qua::kp_Center_Screen));
}

void Quata_Level::ball_Wall_bounce()
{
	sf::Vector2f temp_vel = mBall.getVelocity();
	mBall.setVelocity(sf::Vector2f(temp_vel.x, -temp_vel.y));
}

void Quata_Level::ball_Paddle_bounce(bool is_left_paddle, sf::FloatRect paddle_bounds)
{

	float x, y, angle, speed;
	float relative_intersect = (paddle_bounds.top + (paddle_bounds.height / 2)) - mBall.getPosition().y;
	float normalised_relative_intersection = relative_intersect / (paddle_bounds.height / 2);
	angle = normalised_relative_intersection * 45;
	DebugClass::angle = angle;
	
	angle = angle*(3.14 / 180);
	//	Everything is the same exept the cosine. At the left paddle it ispositive, at the right paddle it is negative.
	//	That determines the ball's direction.
	if (is_left_paddle)
	{
		x = cos(angle);
	}
	else
	{
		x = -cos(angle);
	}
	y = -sin(angle);
	speed = mBall.increaseSpeed();
	DebugClass::speed = speed;
	mBall.setVelocity(sf::Vector2f(x*speed, y*speed));
}

void Quata_Level::ball_cooldown(sf::Time& time)
{
	mBall_cooldown_time += time;
	if (mBall_cooldown_time >= sf::seconds(1))
	{
		mBall_cooldown_time = sf::seconds(0);
		is_ball_on_cooldown = false;
		start_ball();
	}
}

void Quata_Level::start_cooldown()
{
	is_ball_on_cooldown = true;
	mBall.set_Ball_Transparency(true);
}

const sf::FloatRect Quata_Level::get_Ball_Bounds() const
{
	return mBall.getBounds();
}

const sf::Vector2f Quata_Level::get_Ball_Position() const
{
	return mBall.getPosition();
}
