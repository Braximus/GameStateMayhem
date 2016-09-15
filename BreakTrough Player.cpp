#include "stdafx.h"
#include "BreakTrough Player.h"
#include "BreakTrough Data.h"


BreakTrough_Player::BreakTrough_Player(BreakTrough_Data& data)
	: mData(data)
	, mPaddle(mData)
{
	number_of_balls = 1;
	BrkTr_Ball ball(mData);
	mBalls.push_back(ball);
	mCurrent_ball_speed = Break::speed_Ball_Default;

	has_fired = false;
	
	mData.update_Mouse();
	previous_mouse_pos = static_cast<sf::Vector2f>(mData.get_Mouse_Coordinates());
	mCurrent_type = Break::Paddle_Default;
	mPrevious_type = mCurrent_type;
	//	Ovo bi trebalo da postavi pedalu i loptu na startnu poziciju!
	mBalls.at(0).reset_or_stick_Ball(sf::Vector2f(mPaddle.getPosition().x, mPaddle.getPosition().y - 2 * mData.get_Component_Sizes(Break::size_Ball).x));

}

void BreakTrough_Player::update(sf::Time& time)
{
	bool del = false;
	Break::PowerUp_ID temp_id;


	for (BrkTr_Ball& i : mBalls)
	{
		i.update(time);
	}
	if (has_fired)
	{
		pLas->update(time);
	}
	for (auto& it : mActive_PowerUp_time)
	{
		it.second -= time;
		if (it.second <= sf::seconds(0))
		{
			del = true;
			temp_id = it.first;
		}
	}
	if (del)
	{
		remove_PowerUp(temp_id);
	}
	mPaddle.update(time);

	
}

std::deque<BrkTr_Game_Objects*> BreakTrough_Player::pass_Pointers()
{
	std::deque<BrkTr_Game_Objects*> the_deque;
	BrkTr_Game_Objects*				ptr;

	ptr = &mPaddle;
	the_deque.push_back(std::move(ptr));
	if (has_fired)
	{
		ptr = pLas.get();
		the_deque.push_back(std::move(ptr));
	}
	for (BrkTr_Ball& it : mBalls)
	{
		ptr = &it;
		the_deque.push_back(std::move(ptr));
	}

	return the_deque;
}

void BreakTrough_Player::create_Laser()
{
	if (!has_fired)
	{
		pLas.reset(new BrkTr_Laser(mData));
		pLas->setPosition(mPaddle.getPosition());
		has_fired = true;
	}
}

void BreakTrough_Player::delete_Laser()
{
	if (has_fired)
	{
		pLas.release();
		has_fired = false;
	}
}

const bool BreakTrough_Player::has_fired_check() const
{
	return has_fired;
}

void BreakTrough_Player::create_Balls()
{
	float x, y, ugaono_odstojanje;
	//	Prva lopta
	BrkTr_Ball ball1(mData);
	mBalls.push_back(ball1);
	ugaono_odstojanje = static_cast<float>(30 * (3.14 / 180));
	x = cos(mBalls.at(0).getAngle() - ugaono_odstojanje);
	y = sin(mBalls.at(0).getAngle() - ugaono_odstojanje);
	mBalls.at(1).setPosition(mBalls.at(0).getPosition());
	sf::Vector2f speed = sf::Vector2f(mData.get_Speed(mCurrent_ball_speed)*x, mData.get_Speed(mCurrent_ball_speed)*y);
	mBalls.at(1).setVelocity(speed);
	//	Druga lopta
	BrkTr_Ball ball2(mData);
	mBalls.push_back(ball2);
	ugaono_odstojanje = static_cast<float>(30 * (3.14 / 180));
	x = cos(mBalls.at(0).getAngle() + ugaono_odstojanje);
	y = sin(mBalls.at(0).getAngle() + ugaono_odstojanje);
	mBalls.at(2).setPosition(mBalls.at(0).getPosition());
	speed = sf::Vector2f(mData.get_Speed(mCurrent_ball_speed)*x, mData.get_Speed(mCurrent_ball_speed)*y);
	mBalls.at(2).setVelocity(speed);

	number_of_balls = 3;
}

void BreakTrough_Player::reset_Ball()
{
	mBalls.clear();
	number_of_balls = 1;
	BrkTr_Ball ball(mData);
	mBalls.push_back(ball);
	mCurrent_ball_speed = Break::speed_Ball_Default;

	mBalls.at(0).reset_or_stick_Ball(sf::Vector2f(mPaddle.getPosition().x, mPaddle.getPosition().y - 2 * mData.get_Component_Sizes(Break::size_Ball).x));

}

void BreakTrough_Player::delete_Ball()
{	
	mBalls.erase(std::remove_if(mBalls.begin(), mBalls.end(),
	[&] (BrkTr_Ball obj) 
	{ 
		if (obj.is_delete())
		{
			number_of_balls--;
			return true;
		}
		else
			return false;
	}
	), mBalls.end());
	
}

void BreakTrough_Player::set_Ball_Speed(Break::Speeds param)
{
	mCurrent_ball_speed = param;

	for (BrkTr_Ball& ball : mBalls)
	{
		sf::Vector2f cur_pos = ball.getPosition();
		sf::Vector2f prev_pos = ball.getPrevious_Position();

		float x = cur_pos.x - prev_pos.x;
		float y = cur_pos.y - prev_pos.y;
		float angle = (atan2(y, x));

		x = cos(angle);
		y = sin(angle);

		float speed = mData.get_Speed(mCurrent_ball_speed);
		ball.setVelocity(sf::Vector2f(x*speed, y*speed));
	}
}

void BreakTrough_Player::move_Paddle()
{
	if (!mPaddle.is_fading())
	{
		sf::Vector2f cur_mouse_pos = static_cast<sf::Vector2f>(mData.get_Mouse_Coordinates());
		sf::Vector2f diff = cur_mouse_pos - previous_mouse_pos;		
		mPaddle.setVelocity(sf::Vector2f(diff.x, 0));
		previous_mouse_pos = cur_mouse_pos;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (auto& it : mBalls)
			{
				if (it.sticked())
				{
					if (mCurrent_type == Break::Paddle_Sticky)
					{
						it.ball_start(it.getStored_Velocity());
					}
					else
					{
						it.ball_start(sf::Vector2f(0, -mData.get_Speed(mCurrent_ball_speed)));
					}

				}
			}
			if (mCurrent_type == Break::Paddle_Laser)
			{
				if (!has_fired)
				{
					mData.Play_Sound(Break::snd_Laser_fire);
					create_Laser();
				}
			}
		}
	}
}

void BreakTrough_Player::start_Paddle_fade()
{
	mActive_PowerUp_time.clear();	//	Dok smo ovde, da izbrisemo i svo preostalo vreme za pojacanja
	mPaddle.start_Paddle_fading();
}

void BreakTrough_Player::fade_Paddle()
{
	mPaddle.fade_Paddle();
}

void BreakTrough_Player::set_Paddle_Type(Break::Paddle_Type param)
{
	mCurrent_type = param;

	if (mCurrent_type != mPrevious_type)
	{
		if (mCurrent_type == Break::Paddle_Sticky || mCurrent_type == Break::Paddle_Laser || mCurrent_type == Break::Paddle_Laser || mCurrent_type == Break::Paddle_Default)
		{
			mPaddle.Change_Paddle(mData.get_Component_Sizes(Break::size_Paddle_Default), mData.get_TextureRect(mCurrent_type));
		}
		else if (mCurrent_type == Break::Paddle_Big)
		{
			mPaddle.Change_Paddle(mData.get_Component_Sizes(Break::size_Paddle_Large), mData.get_TextureRect(mCurrent_type));
		}
		else
		{
			mPaddle.Change_Paddle(mData.get_Component_Sizes(Break::size_Paddle_Small), mData.get_TextureRect(mCurrent_type));
		}
		mPrevious_type = mCurrent_type;
	}

}

void BreakTrough_Player::reset_Paddle()
{
	set_Paddle_Type(Break::Paddle_Default);
	sf::Vector2f pad_pos = mData.get_Components_Positions(Break::c_Paddle);
	mPaddle.reset_Paddle_opacity();
	mPaddle.setPosition(pad_pos);
	//	Eventualno da stavim da se pozicija vrati na sredinu nivoa.
}

void BreakTrough_Player::take_PowerUp(Break::PowerUp_ID param)
{
	bool create = true;
	if (!mActive_PowerUp_time.empty())
	{
		std::map<Break::PowerUp_ID, sf::Time>::iterator it;
		//	Ako pojacanje postoji i isto je, samo mu osvezi vreme.
		it = mActive_PowerUp_time.find(param);
		if (it != mActive_PowerUp_time.end())
		{
			if (it->first == Break::pID_Laser_Paddle)
				it->second = sf::seconds(15);//mData.get_Timer(Break::time_Short);
			else if (it->first == Break::pID_Sticky_Paddle)
				it->second = sf::seconds(45);//mData.get_Timer(Break::time_Long);
			else if (it->first == Break::pID_Stretch_Paddle)
				it->second = sf::seconds(45);//mData.get_Timer(Break::time_Long);
			else if (it->first == Break::pID_Shrink_Paddle)
				it->second = sf::seconds(45);//mData.get_Timer(Break::time_Long);
			else if (it->first == Break::pID_Slow_Ball)
				it->second = sf::seconds(30);//mData.get_Timer(Break::time_Medium);
			else if (it->first == Break::pID_Fast_Ball)
				it->second = sf::seconds(30);//mData.get_Timer(Break::time_Medium);

			create = false;			
		}
		else
		{
			//	Ako postojanje je kontradiktorno sa drugim pojacanjem, neka novo pojacanje zameni staro. 
			for (std::map<Break::PowerUp_ID, sf::Time>::iterator for_it = mActive_PowerUp_time.begin(); for_it != mActive_PowerUp_time.end(); ++for_it)
			{
				if (param == Break::pID_Laser_Paddle || param == Break::pID_Sticky_Paddle || param == Break::pID_Stretch_Paddle || param == Break::pID_Shrink_Paddle )
				{
					if (for_it->first != param && for_it->first != Break::pID_Slow_Ball && for_it->first != Break::pID_Fast_Ball)
					{
						mActive_PowerUp_time.erase(for_it);
						break;
					}
				}
				else if (param == Break::pID_Slow_Ball || param == Break::pID_Fast_Ball)
				{
					if (for_it->first != param && for_it->first != Break::pID_Laser_Paddle && for_it->first != Break::pID_Stretch_Paddle && for_it->first != Break::pID_Shrink_Paddle && for_it->first != Break::pID_Sticky_Paddle)
					{
						mActive_PowerUp_time.erase(for_it);
						break;
					}
				}
			}
		}
	}

	if (create)
	{
		if (param == Break::pID_Laser_Paddle)
		{
			mActive_PowerUp_time.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, sf::seconds(15)));
			set_Paddle_Type(Break::Paddle_Laser);
		}
		else if (param == Break::pID_Sticky_Paddle)
		{
			mActive_PowerUp_time.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, sf::seconds(45)));
			set_Paddle_Type(Break::Paddle_Sticky);
		}
		else if (param == Break::pID_Stretch_Paddle)
		{
			mActive_PowerUp_time.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, sf::seconds(45)));
			set_Paddle_Type(Break::Paddle_Big);
		}
		else if (param == Break::pID_Shrink_Paddle)
		{
			mActive_PowerUp_time.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, sf::seconds(45)));
			set_Paddle_Type(Break::Paddle_Small);
		}
		else if (param == Break::pID_Triple_Ball)
		{
			if (number_of_balls == 1)
				create_Balls();
		}
		else if (param == Break::pID_Slow_Ball)
		{
			mActive_PowerUp_time.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, sf::seconds(30)));
			set_Ball_Speed(Break::speed_Ball_Slow);
		}
		else if (param == Break::pID_Fast_Ball)
		{
			mActive_PowerUp_time.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, sf::seconds(30)));
			set_Ball_Speed(Break::speed_Ball_Fast);
		}
		else if (param == Break::pID_Extra_Life)
		{
			UINT life = mData.get_Object_Quantities(Break::Number_of_Lives) + 1;
			mData.set_Object_Quantities(Break::Number_of_Lives, life);
		}
	}
	
}


void BreakTrough_Player::remove_PowerUp(Break::PowerUp_ID param)
{
	mData.Play_Sound(Break::snd_PowerUp_lost);
	mActive_PowerUp_time.erase(param);
	if (param != Break::pID_Slow_Ball && param != Break::pID_Fast_Ball)
	{
		set_Paddle_Type(Break::Paddle_Default);
	}
	else
	{
		set_Ball_Speed(Break::speed_Ball_Default);
	}
}


std::deque<BrkTr_Ball>& BreakTrough_Player::get_Balls()
{
	return mBalls;
}

BrkTr_Paddle& BreakTrough_Player::get_Paddle() 
{
	return mPaddle;
}

std::unique_ptr<BrkTr_Laser>& BreakTrough_Player::get_Laser() 
{
	return pLas;
}

const UINT BreakTrough_Player::get_number_of_Balls() const
{
	return number_of_balls;
}

const Break::Speeds BreakTrough_Player::get_Current_Ball_Speed() const
{
	return mCurrent_ball_speed;
}

const Break::Paddle_Type BreakTrough_Player::get_Current_Paddle_Type() const
{
	return mCurrent_type;
}

const bool BreakTrough_Player::get_is_Paddle_fading() const
{
	return mPaddle.is_fading();
}