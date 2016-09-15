#ifndef BREAKTROUGH_SCORE_H
#define BREAKTROUGH_SCORE_H

#include "BreakTrough UI Objects.h"
class BreakTrough_Data;

class BrkTr_UI_Score : public BrkTr_UI_Objects
{
	sf::Text			mScore;	
	std::string			mStored_txt;
	sf::RectangleShape	mBackground;
public:
	explicit	BrkTr_UI_Score(BreakTrough_Data&);
	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		update_text(std::string&);
};



#endif