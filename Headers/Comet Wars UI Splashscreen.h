#ifndef COMET_WARS_UI_SPLASHSCREEN_H
#define COMET_WARS_UI_SPLASHSCREEN_H

#include "Comet Wars UI Objects.h"
class CometWarsData;

class CometWars_UI_SplashScreen : public CometWars_UI_Objects
{
	sf::RectangleShape		mArea;
	sf::Text				mText;
public:
	CometWars_UI_SplashScreen(CometWarsData&);
	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		update(sf::Time&);

	void		setText(std::string);
};



#endif
