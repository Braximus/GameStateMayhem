#ifndef COMETWARS_GAME_PROJECTILES_H
#define COMETWARS_GAME_PROJECTILES_H

#include "Comet Wars Game Objects.h"

class CometWarsData;

class CometWars_Game_Projectiles : public CometWars_Game_Objects
{
	sf::CircleShape			mProjectile;
public:
	explicit			CometWars_Game_Projectiles(CometWarsData& data);

	void				setPosition(sf::Vector2f);
	void				setVelocity(sf::Vector2f);

	void				draw(sf::RenderTarget&, sf::RenderStates) const;
	void				update(sf::Time& time);



};



#endif