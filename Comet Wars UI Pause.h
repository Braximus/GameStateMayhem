#ifndef COMET_WARS_UI_PAUSE_H
#define COMET_WARS_UI_PAUSE_H

#include "Comet Wars UI Objects.h"
#include "Buttons.h"
class CometWarsData;

class CometWars_UI_Pause : public CometWars_UI_Objects
{
	CW::Button_Selection						mCurrentSelection, mPreviousSelection;
	std::map<CW::Button_Selection, Button>		mButtons;
	sf::RectangleShape							mPause_Area, mScreen_Fill;
	bool										hover;
public:
	CometWars_UI_Pause(CometWarsData&);
	void					draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void					update(sf::Time&);
	void					interact(sf::Vector2f param);
	const bool				is_hovering() const;

	const	CW::Button_Selection				response() const;


};





#endif