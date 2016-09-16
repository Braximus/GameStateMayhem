#ifndef COMET_MANAGER_H
#define COMET_MANAGER_H

#include "Comet Wars Game Asteroid.h"

class CometWarsData;

class Comet_Manager
{
	CometWarsData&				mData;
	std::deque<CometWars_Game_Asteroid>	mComets;	
public:
	Comet_Manager(CometWarsData&);	
	std::deque<CometWars_Game_Objects*>		pass_pointers();
	void			update(sf::Time&);
	void			restart();

	void					create_comet(bool);
	void					delete_comet();
	const CW::AsteroidDamage		damage_comet(UINT);
	
	void					setComet_Position(UINT, sf::Vector2f);
	const sf::Vector2f			getComet_Position(UINT) const;
	const sf::FloatRect			getComet_Bounds(UINT) const;
	const bool				isMini_Comet(UINT) const;
	const UINT				getNumber_of_comets() const;
};
#endif
