#ifndef COMETWARS_UI_AREA_H
#define COMETWARS_UI_AREA_H

#include "Comet Wars UI Objects.h"

class CometWarsData;

class CometWars_UI_Area : public CometWars_UI_Objects
{
	sf::RectangleShape			mRect;
	sf::RectangleShape			mBackgroundRect;
public:
	CometWars_UI_Area(CometWarsData&);
	void				draw(sf::RenderTarget&, sf::RenderStates) const;
	void				update(sf::Time&);
};



#endif