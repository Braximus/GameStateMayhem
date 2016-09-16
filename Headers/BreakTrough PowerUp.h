#ifndef BREAKTROUGH_POWERUP_H
#define BREAKTROUGH_POWERUP_H

#include "BreakTrough Game Objects.h"

class BreakTrough_Data;

class BrkTr_PowerUp : public BrkTr_Game_Objects
{
	sf::RectangleShape			mPowerUp;
	Break::PowerUp_ID			mID;
public:
	BrkTr_PowerUp(BreakTrough_Data& data, Break::PowerUp_ID id, sf::Vector2f start_position);

	void			draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void			update(sf::Time& time);

	const Break::PowerUp_ID			pass_ID() const;
};
#endif
