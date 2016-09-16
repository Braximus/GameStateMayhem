#ifndef QUATA_BALL_H
#define QUATA_BALL_H

#include "Quata Objects.h"
class QuataData;

class Quata_Ball : public QuataObjects
{
	QuataData&					mData;
	sf::CircleShape					mBall_circle;
	sf::Vector2f					mVelocity;
	float						mAngle, mSpeed;	
public:
	explicit					Quata_Ball(QuataData&);
	void						draw(sf::RenderTarget& target, sf::RenderStates) const;
	void						update(sf::Time&);
	void						setPosition(sf::Vector2f);

	void						setVelocity(sf::Vector2f);
	const sf::Vector2f				getVelocity() const;
	void						setAngle(float);
	float						increaseSpeed();
	float						reset_speed();

	void						set_Ball_Transparency(bool);
};
#endif
