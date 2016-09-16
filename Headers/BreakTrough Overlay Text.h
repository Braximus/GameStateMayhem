#ifndef BREAKTROUGH_OVERLAY_TEXT_H
#define BREAKTROUGH_OVERLAY_TEXT_H

#include "BreakTrough UI Objects.h"
class BreakTrough_Data;

class BrkTr_Overlay : public BrkTr_UI_Objects
{
	sf::Text			mOverlay_text1;
	sf::Text			mOverlay_text2;
	sf::RectangleShape	mOverlay_box;
public:
	BrkTr_Overlay(BreakTrough_Data& data);
	void				draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void				update_text(std::string&);
	void				game_over_text(std::string&);
};


#endif
