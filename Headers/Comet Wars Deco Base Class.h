#ifndef COMET_WARS_DECORATIONS_BASE_CLASS_H
#define COMET_WARS_DECORATIONS_BASE_CLASS_H

#include "stdafx.h"

class CometWars_Deco_Base_Class : public sf::Drawable, public sf::Transformable
{
public:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates state) const =0;
	virtual void	update(sf::Time&) = 0;
};
#endif
