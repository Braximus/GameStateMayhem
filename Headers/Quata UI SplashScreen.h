#ifndef QUATA_SPLASH_SCREEN_H
#define QUATA_SPLASH_SCREEN_H


#include "Quata Data.h"
#include "Quata UI Objects.h"

class Quata_SplashScreen : public Quata_UI_Objects
{
	sf::Text					mText;
	sf::RectangleShape			mRect;
public:
	Quata_SplashScreen(QuataData& data, const std::string);
	void						draw(sf::RenderTarget& target, sf::RenderStates state) const;
};
#endif
