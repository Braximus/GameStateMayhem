#ifndef COMETWARS_GAME_OBJECTS_H
#define COMETWARS_GAME_OBJECTS_H

#include "stdafx.h"
#include "Comet Wars Enumerations.h"

class CometWars_Game_Objects: public sf::Drawable, public sf::Transformable
{
protected:
	sf::FloatRect				mBounds;
	sf::Vector2f				mPosition;
	sf::Vector2f				mVelocity;
	sf::IntRect					mTextureRect;
	float						mRotation;
	bool						is_deleted;
public:
	virtual void				draw(sf::RenderTarget&, sf::RenderStates) const =0;
	virtual void				update(sf::Time& time) = 0;

	virtual void				setPosition(sf::Vector2f) = 0;
	virtual void				setVelocity(sf::Vector2f) = 0;

	virtual void				mark_for_deletion() { is_deleted = true; };
	virtual	const bool			is_marked() const { return is_deleted; };

	virtual const sf::FloatRect				getBounds() const { return mBounds; }
	virtual const sf::Vector2f				getPosition() const { return mPosition; }
};



#endif
