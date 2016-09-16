#ifndef COMETWARS_UI_SCORE_H
#define COMETWARS_UI_SCORE_H

#include "Comet Wars UI Objects.h"

class CometWarsData;

class CometWars_UI_Score : public CometWars_UI_Objects
{
	sf::Text				mText;
	std::string				mStored_txt;
public:
	CometWars_UI_Score(CometWarsData&);
	void					draw(sf::RenderTarget&, sf::RenderStates) const;
	void					update(sf::Time&);
	void					refresh_score(UINT);
};
#endif
