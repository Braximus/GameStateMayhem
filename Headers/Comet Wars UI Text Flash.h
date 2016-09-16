#ifndef COMETWARS_UI_TEXT_FLASH_H
#define COMETWARS_UI_TEXT_FLASH_H


#include "Comet Wars UI Objects.h"
class CometWarsData;

class CometWars_UI_Text_Flash : public CometWars_UI_Objects
{
	sf::Text			mText;
public:
	CometWars_UI_Text_Flash(CometWarsData&);
	bool				fade_in;
	bool				fade_out;

	void				draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void				update(sf::Time&);
};
#endif
