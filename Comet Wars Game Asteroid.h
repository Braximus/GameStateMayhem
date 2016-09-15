#ifndef COMETWARS_GAME_ASTEROID_H
#define COMETWARS_GAME_ASTEROID_H

#include "Comet Wars Game Objects.h"

class CometWarsData;

class CometWars_Game_Asteroid : public CometWars_Game_Objects
{
	sf::RectangleShape		mAsteroid;
	CW::AsteroidDamage		mDamageState;

public:
	explicit			CometWars_Game_Asteroid(CometWarsData& data, bool is_mini_comet);
	bool						mini_comet;

	void						draw(sf::RenderTarget&, sf::RenderStates) const;
	void						update(sf::Time& time);

	void						setPosition(sf::Vector2f);
	void						setVelocity(sf::Vector2f);

	void						changeTexRect(sf::IntRect);
	void						changeDamageStatus();
	const	CW::AsteroidDamage	getDamage() const;
};





#endif