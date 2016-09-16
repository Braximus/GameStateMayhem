#ifndef QUATA_PADDLES_H
#define QUATA_PADDLES_H

#include "Quata Objects.h"
class QuataData;

class Quata_Paddle : public QuataObjects
{
	sf::RectangleShape				mPaddle_rect;
	sf::Vector2f					mVelocity;
public:
	explicit						Quata_Paddle(QuataData& data, sf::IntRect tex_area);
	void							draw(sf::RenderTarget&, sf::RenderStates) const;
	void							update(sf::Time&);

	void							setPosition(sf::Vector2f);
	const sf::Vector2f				getPosition() const;

	void							setVelocity(sf::Vector2f);
};

#endif
