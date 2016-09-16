#ifndef QUATA_PAUSE_H
#define QUATA_PAUSE_H

#include "Quata Enumerations.h"
#include "Quata UI Objects.h"
#include "Buttons.h"
class QuataData;

class Quata_Pause: public Quata_UI_Objects
{
	Qua::Button_Selection				mCurrentSelection, mPreviousSelection;
	std::map<Qua::Button_Selection, Button>		mButtons;
	sf::RectangleShape				mPause_Area, mScreen_Fill;
	bool						hover;
public:
	Quata_Pause(QuataData&);
	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		interact(sf::Vector2f mouse_pos);
	const bool	is_hovering() const;
	const Qua::Button_Selection		response() const;
};

#endif
