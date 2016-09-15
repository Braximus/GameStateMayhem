#ifndef BREAKTROUGH_PAUSE_H
#define BREAKTROUGH_PAUSE_H


#include "BreakTrough UI Objects.h"
#include "Buttons.h"
class BreakTrough_Data;

class BreakTrough_Pause: public BrkTr_UI_Objects
{
	Break::Button_Selection							mCurrentSelection, mPreviousSelection;
	std::map<Break::Button_Selection, Button>		mButtons;
	sf::RectangleShape		mPause_Area, mScreen_Fill;
	bool					hover;
public:
	BreakTrough_Pause(BreakTrough_Data&);
	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		interact(sf::Vector2f param);
	const bool	is_hovering() const;
	const Break::Button_Selection		response() const;

	
};



#endif