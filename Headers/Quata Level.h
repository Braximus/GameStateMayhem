#ifndef QUATA_LEVEL_H
#define QUATA_LEVEL_H

#include "Quata Ball.h"
#include "Quata Playfield.h"
#include "Quata Objects.h"

class QuataData;

class Quata_Level
{
	QuataData&		mData;
	Quata_Ball		mBall;
	Quata_Playfield		mPlayField;

	sf::Time	mBall_cooldown_time;
	bool		is_ball_on_cooldown;
public:
	explicit					Quata_Level(QuataData&);
	std::deque<QuataObjects*>			pass_pointers();
	void							update(sf::Time&);

	void							start_ball();
	void							reset_ball();
	void							ball_Wall_bounce();
	void							ball_Paddle_bounce(bool is_left_paddle, sf::FloatRect paddleBounds);
	void							ball_cooldown(sf::Time&);
	void							start_cooldown();
	const sf::FloatRect				get_Ball_Bounds() const;
	const sf::Vector2f				get_Ball_Position() const;

};
#endif
