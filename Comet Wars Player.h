#ifndef COMETWARS_PLAYER_H
#define COMETWARS_PLAYER_H


#include "Comet Wars Game Ship.h"
#include "Comet Wars Game Projectiles.h"
class CometWarsData;
class CometWars_UI_Manager;

class CometWars_Player
{
	CometWarsData&			mData;
	CometWars_UI_Manager*	pUI_Manager;
	CometWars_Game_Ship		mShip;
	std::deque<CometWars_Game_Projectiles>	mProjectiles;

	sf::Time				mProjectile_interval;
	sf::Time				mShield_time;
	bool					is_shield_on, has_fired;
public:
	CometWars_Player(CometWarsData& data, CometWars_UI_Manager* ui);
	std::deque<CometWars_Game_Objects*>		pass_pointers();
	void									update(sf::Time&);
	void					restart();
	
	void					setShip_Position(sf::Vector2f);
	const sf::Vector2f		getShip_Position() const;
	const sf::FloatRect		getShip_Bounds() const;
	
	const sf::FloatRect	 	getProjectile_Bounds(UINT) const;
	const UINT				getNumber_of_projectiles() const;
	void					mark_projectile_for_deletion(UINT);
	void					create_projectile();
	void					delete_projectile();
	void					destroy_ship();

	void					handle_ship_movement();
	bool					ship_fire_cooldown(sf::Time& time);
	void					add_projectile_cooldown();
	void					shield(sf::Time& time);
	void					activate_shield();
	const bool				getIs_shield_on() const;

};





#endif