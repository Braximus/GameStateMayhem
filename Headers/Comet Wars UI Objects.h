#ifndef COMETWARS_UI_OBJECTS_H
#define COMETWARS_UI_OBJECTS_H

#include "Comet Wars Enumerations.h"


class CometWars_UI_Objects : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Vector2f				mPosition;
public:
	virtual void				draw(sf::RenderTarget&, sf::RenderStates state) const =0;
	virtual void				update(sf::Time&) =0;

	const sf::Vector2f			getPosition() const { return mPosition; };
};
#endif
