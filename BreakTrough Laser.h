#ifndef BREAKTROUGH_LASER_H
#define BREAKTROUGH_LASER_H

#include "BreakTrough Game Objects.h"
class BreakTrough_Data;

class BrkTr_Laser : public BrkTr_Game_Objects
{
	sf::RectangleShape		m_Laser_left, m_Laser_right;
	float					distance_from_paddle_centre;
public:
	BrkTr_Laser(BreakTrough_Data&);

	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		update(sf::Time&);
	void		setPosition(sf::Vector2f);
	void		setVelocity(sf::Vector2f);

};



#endif
