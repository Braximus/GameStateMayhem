#ifndef COMET_WARS_UI_COUNTDOWN_H
#define COMET_WARS_UI_COUNTDOWN_H

#include "Comet Wars UI Objects.h"

class CometWarsData;

class CometWars_UI_Countdown : public CometWars_UI_Objects
{
	sf::Text			mText;
	sf::Time			mTime;
public:
	CometWars_UI_Countdown(CometWarsData& data);
	
	void				draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void				update(sf::Time&);

	void				resetTimer();
	const float			getTimer() const;



};





#endif 