#ifndef BREAKTROUGH_UI_OBJECTS_H
#define BREAKTROUGH_UI_OBJECTS_H

#include "stdafx.h"
#include "BreakTrough Enumerations.h"

class BrkTr_UI_Objects : public sf::Drawable, public sf::Transformable
{
	sf::FloatRect		m_Bounds;	//	Currently is not being used
public:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates state) const = 0;
	const sf::FloatRect	getBounds() const { return m_Bounds; };
};
#endif

