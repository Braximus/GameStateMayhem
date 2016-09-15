#include "stdafx.h"
#include "BreakTrough Ball.h"
#include "BreakTrough Data.h"

BrkTr_Ball::BrkTr_Ball(BreakTrough_Data& data)
{
	marked_for_deletion = false;

	mBall.setTexture(&data.get_Resources().getTexture(ID_BreakTrough));
	mBall.setTextureRect(data.get_TextureRect(Break::t_Ball));
	mBall.setRadius(data.get_Component_Sizes(Break::size_Ball).x);
	sf::FloatRect b = mBall.getLocalBounds();
	mBall.setOrigin(b.width / 2, b.height / 2);
	mBall.setPosition(data.get_Components_Positions(Break::c_Ball));
	angle = 0;

	mPrevious_Position = sf::Vector2f(0, 0);
	position_on_paddle = 0;
	is_sticked_on_paddle = false;
	calcualted = false;
	has_hit_block = false;
};

void BrkTr_Ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mBall, state);

}

void BrkTr_Ball::update(sf::Time& time)
{
	mPrevious_Position = m_Position;
	if (!is_sticked_on_paddle)
	{
		mBall.move(m_Velocity*time.asSeconds());
	}
	m_Position = mBall.getPosition();
	m_Bounds = mBall.getGlobalBounds();
}

//	Called when the ball falls in "abyss" or when the paddle is sticky.
void BrkTr_Ball::reset_or_stick_Ball(sf::Vector2f param)	
{
	m_Position = param;
	mBall.setPosition(m_Position);
	is_sticked_on_paddle = true;
	m_Velocity = sf::Vector2f(0, 0);

}

void BrkTr_Ball::move(float offsetX, float offsetY)
{
	mBall.move(offsetX, offsetY);
	m_Position = mBall.getPosition();
}

void BrkTr_Ball::setPosition(sf::Vector2f param)
{
	m_Position = param;
	mBall.setPosition(m_Position);
	m_Bounds = mBall.getGlobalBounds();
}

void BrkTr_Ball::setVelocity(sf::Vector2f param)
{	
	m_Velocity = param;
}

const sf::Vector2f BrkTr_Ball::getVelocity() const
{
	return m_Velocity;
}

const sf::Vector2f BrkTr_Ball::getPrevious_Position() const
{
	return mPrevious_Position;
}

void BrkTr_Ball::bounce(bool b)
{
	if (b)
		m_Velocity.x *= -1;
	else
		m_Velocity.y *= -1;
}

void BrkTr_Ball::ball_start(sf::Vector2f param)
{
	if (is_sticked_on_paddle)
		is_sticked_on_paddle = false;
	m_Velocity = param;
}

const bool BrkTr_Ball::sticked() const
{
	return is_sticked_on_paddle;
}

void BrkTr_Ball::set_calculated(bool param)
{
	calcualted = param;
}

void BrkTr_Ball::set_has_hit_block(bool param)
{
	has_hit_block = param;
}

const bool BrkTr_Ball::get_has_hit_block() const
{
	return has_hit_block;
}

const bool BrkTr_Ball::is_calculated() const
{
	return calcualted;
}

//	angle is in radians!
void BrkTr_Ball::setAngle(float param)
{
	angle = param;
}

const float BrkTr_Ball::getAngle() const
{
	return angle;
}
//	Ball position on paddle when the paddle is sticky.
void BrkTr_Ball::setPosition_on_Paddle(float param)
{
	position_on_paddle = param;
}

const float BrkTr_Ball::getPosition_on_Paddle() const
{
	return position_on_paddle;
}

void BrkTr_Ball::setStored_Velocity(sf::Vector2f param)
{
	stored_velocity = param;
}

const sf::Vector2f BrkTr_Ball::getStored_Velocity() const
{
	return stored_velocity;
}
