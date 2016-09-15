#ifndef COMETWARS_GAME_SHIP_H
#define COMETWARS_GAME_SHIP_H

#include "Comet Wars Game Objects.h"

class CometWarsData;

class CometWars_Game_Ship : public CometWars_Game_Objects
{
	sf::RectangleShape			mShip;
	sf::CircleShape				mShield;
	bool						is_Shield_Active;
	CW::ShipType				mShip_Type;
public:
	explicit					CometWars_Game_Ship(CometWarsData& data);

	void						draw(sf::RenderTarget&, sf::RenderStates) const;
	void						update(sf::Time& time);

	void						setPosition(sf::Vector2f);
	void						setVelocity(sf::Vector2f);

	void						rotate_ship(float);
	void						activate_sheld(bool Shield);
	void						set_ship_invisible(bool);

	const bool					getIs_Shield_active() const;

};



#endif