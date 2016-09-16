#ifndef QUATA_UI_OBJECTS_H
#define QUATA_UI_OBJECTS_H

#include "stdafx.h"

class Quata_UI_Objects : public sf::Drawable, public sf::Transformable
{
public:
	virtual void		draw(sf::RenderTarget&, sf::RenderStates) const = 0;
};
#endif
