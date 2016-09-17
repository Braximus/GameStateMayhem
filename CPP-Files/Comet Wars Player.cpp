#include "stdafx.h"
#include "Comet Wars Player.h"
#include "Comet Wars Data.h"
#include "Comet Wars UI Manager.h"
#include "Debug.h"

CometWars_Player::CometWars_Player(CometWarsData& data, CometWars_UI_Manager* ui)
	:mData(data)
	, mShip(data)
	, pUI_Manager(ui)
{
	is_shield_on = false;
	has_fired = false;
	mShield_time = sf::seconds(0);

}

std::deque<CometWars_Game_Objects*> CometWars_Player::pass_pointers()
{
	std::deque<CometWars_Game_Objects*> temp_deque;

	for (auto& it : mProjectiles)
	{
		temp_deque.push_back(&it);
	}
	temp_deque.push_back(&mShip);
	return temp_deque;
}

void CometWars_Player::update(sf::Time& time)
{
	if (!ship_fire_cooldown(time) && has_fired)
	{
		if (!is_shield_on )
		{
			mData.Play_Sound(CW::snd_LaserFire);
			create_projectile();
			add_projectile_cooldown();
		}
		else
		{
			pUI_Manager->create_TextFlash();
		}
	}
	mShip.update(time);
	if (is_shield_on)
	{
		shield(time);
	}
	for (auto& it : mProjectiles)
	{
		it.update(time);
	}

	DebugClass::nums.at(0) =  static_cast<sf::Vector2i>(mShip.getPosition());
	DebugClass::numbers[2] = mProjectiles.size();
}

void CometWars_Player::restart()
{
	mProjectiles.clear();
	mProjectile_interval = sf::seconds(0);
	mShield_time = sf::seconds(0);
	is_shield_on = false;
	mShip.activate_sheld(is_shield_on);

}

void CometWars_Player::setShip_Position(sf::Vector2f param)
{
	mShip.setPosition(param);
}

void CometWars_Player::shield(sf::Time& time)
{
	if (is_shield_on)
	{
		if (mShield_time > sf::seconds(5))
		{
			mData.Play_Sound(CW::snd_PlayerShieldDown);
			is_shield_on = false;
			mShip.activate_sheld(is_shield_on);
			pUI_Manager->delete_TextFlash();
			mShield_time = sf::seconds(0);
		}
		else
		{
			mShield_time += time;
		}

	}
}

void CometWars_Player::activate_shield()
{
	is_shield_on = true;
	mShip.activate_sheld(is_shield_on);
}


void CometWars_Player::create_projectile()
{
	CometWars_Game_Projectiles projectile(mData);
	projectile.setPosition(mShip.getPosition());

	float x = mData.getMouse_position().x - projectile.getPosition().x;
	float y = mData.getMouse_position().y - projectile.getPosition().y;
	float angle = (atan2(y, x));
	//
	x = cos(angle);
	y = sin(angle);

	projectile.setVelocity(sf::Vector2f(x*mData.getSpeed(CW::speed_Projectile), y*mData.getSpeed(CW::speed_Projectile)));

	mProjectiles.push_back(projectile);
}

void CometWars_Player::delete_projectile()
{
	mProjectiles.erase(std::remove_if(mProjectiles.begin(), mProjectiles.end(),
		[&](CometWars_Game_Projectiles obj)
	{
		return obj.is_marked();
	}), mProjectiles.end());
}

void CometWars_Player::destroy_ship()
{
	mShip.set_ship_invisible(true);
	for (auto& it : mProjectiles)
	{
		it.mark_for_deletion();
	}
	mShip.activate_sheld(false);
	mShield_time = sf::seconds(0);
}

void CometWars_Player::handle_ship_movement()
{
	sf::Vector2f ship_pos = mShip.getPosition();
	sf::Vector2f mouse_pos = mData.getMouse_position();

	float x = ship_pos.x - mouse_pos.x;
	float y = ship_pos.y - mouse_pos.y;
	float angle = (atan2(y, x)) * 180 / 3.14159265;

	mShip.rotate_ship(angle - 90);

	has_fired = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	float Up_Down = 0;
	float Left_Right = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Up_Down = -mData.getSpeed(CW::speed_Ship);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Up_Down = mData.getSpeed(CW::speed_Ship);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Left_Right = -mData.getSpeed(CW::speed_Ship);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Left_Right = mData.getSpeed(CW::speed_Ship);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Up_Down = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Left_Right = 0;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))))
	{
		Up_Down /= sqrt(2.f);
		Left_Right /= sqrt(2.f);
	}
	mShip.setVelocity(sf::Vector2f(Left_Right, Up_Down));
}

bool CometWars_Player::ship_fire_cooldown(sf::Time& time)
{
	if (mProjectile_interval > sf::seconds(0))
	{
		mProjectile_interval -= time;
		if (mProjectile_interval <= sf::seconds(0))
		{
			mProjectile_interval = sf::seconds(0);
		}
		return true;	//	On cooldown!
	}
	return false;	//	Not on cooldown - player can fire.

}

void CometWars_Player::add_projectile_cooldown()
{
	if (mProjectile_interval == sf::seconds(0))
	{
		mProjectile_interval = sf::seconds(0.25f);
	}
}

const sf::Vector2f CometWars_Player::getShip_Position() const
{
	return mShip.getPosition();
}

const sf::FloatRect CometWars_Player::getShip_Bounds() const
{
	return mShip.getBounds();
}

const sf::FloatRect CometWars_Player::getProjectile_Bounds(UINT param) const
{
	return mProjectiles.at(param).getBounds();
}

const UINT CometWars_Player::getNumber_of_projectiles() const
{
	return mProjectiles.size();
}

void CometWars_Player::mark_projectile_for_deletion(UINT param)
{
	mProjectiles.at(param).mark_for_deletion();
}

const bool  CometWars_Player::getIs_shield_on() const
{
	return is_shield_on;
}

