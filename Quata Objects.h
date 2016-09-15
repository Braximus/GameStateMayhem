#ifndef QUATA_OBJECTS_H
#define QUATA_OBJECTS_H

#include "stdafx.h"

class QuataObjects: public sf::Drawable, public sf::Transformable
{
protected:
	sf::FloatRect					mBounds;
	sf::Vector2f					mPosition;
public:
	const sf::FloatRect			getBounds() const { return mBounds; };

	virtual void					draw(sf::RenderTarget& target, sf::RenderStates state) const = 0;

	virtual void					setPosition(sf::Vector2f) = 0;
	virtual const sf::Vector2f		getPosition() const { return mPosition; };



};

#endif