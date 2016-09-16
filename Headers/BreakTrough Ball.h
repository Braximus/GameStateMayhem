#ifndef BREAKTROUGH_GAME_BALL_H
#define BREAKTROUGH_GAME_BALL_H

#include "BreakTrough Game Objects.h"
class BreakTrough_Data;

class BrkTr_Ball : public BrkTr_Game_Objects
{
	float					angle, position_on_paddle;
	sf::Vector2f			stored_velocity;
	sf::CircleShape			mBall;
	sf::Vector2f			mPrevious_Position;
	bool					is_sticked_on_paddle, calcualted, has_hit_block;
public:
	BrkTr_Ball(BreakTrough_Data& );

	void					draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void					update(sf::Time& time);

	void					setPosition(sf::Vector2f);
	void					setVelocity(sf::Vector2f);
	const sf::Vector2f		getVelocity() const;
	const sf::Vector2f		getPrevious_Position() const;
	void					bounce(bool);
	void					reset_or_stick_Ball(sf::Vector2f);
	void					move(float offsetX, float offsetY);	

	void					ball_start(sf::Vector2f);
	const bool				sticked() const;

	void					set_calculated(bool);
	const bool				is_calculated() const;

	void					set_has_hit_block(bool);
	const bool				get_has_hit_block() const;

	void					setPosition_on_Paddle(float);
	const float				getPosition_on_Paddle() const;

	void					setAngle(float);
	const float				getAngle() const;

	void					setStored_Velocity(sf::Vector2f);
	const sf::Vector2f		getStored_Velocity() const;
};
#endif
