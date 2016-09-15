#ifndef	MENU_SUBSTATES_BASE_CLASS_H
#define MENU_SUBSTATES_BASE_CLASS_H

#include "Menu_Enumerations.h"
#include "Menu_Data.h"

class Menu_SubStates : public sf::Drawable, public sf::Transformable
{

public:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates state) const = 0;
	virtual void		update(sf::Time& time) = 0;
	virtual void		handleEvents(sf::Event& Event) = 0;
	virtual void		handleRealTimeInput() = 0;
	virtual void		refresh() = 0;

};



#endif