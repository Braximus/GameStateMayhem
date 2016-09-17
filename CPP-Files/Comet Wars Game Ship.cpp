#include "stdafx.h"
#include "Comet Wars Game Ship.h"
#include "Comet Wars Data.h"


CometWars_Game_Ship::CometWars_Game_Ship(CometWarsData& data)
{
	is_Shield_Active = false;
	mShip.setTexture(&data.getResources().getTexture(ID_CometWars));

	std::uniform_int_distribution<int>	distributor_number(0, 2);
	UINT n = distributor_number(data.get_random_engine());
	CW::ShipType type = static_cast<CW::ShipType>(n);
	mShip.setTextureRect(data.getShip_Texture_rect(type));
	mShip_Type = type;
	mShip.setSize(data.getObj_Sizes(CW::size_Ship));
	sf::FloatRect	b = mShip.getLocalBounds();
	mShip.setOrigin(b.width / 2, b.height / 2);
	
	mShield.setRadius(data.getObj_Sizes(CW::size_Shield).x);
	b = mShield.getLocalBounds();
	mShield.setOrigin(b.width / 2, b.height / 2);
	if (mShip_Type == CW::ship_Type1)
	{
		mShield.setFillColor((sf::Color(0, 127, 255, 127)));
	}
	else if (mShip_Type == CW::ship_Type2)
	{
		mShield.setFillColor((sf::Color(64, 0, 0, 127)));
	}
	else
	{
		mShield.setFillColor((sf::Color(90, 20, 205, 127)));
	}
}

void CometWars_Game_Ship::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mShip, state);
	if (is_Shield_Active)
	{
		target.draw(mShield, state);
	}
}

void CometWars_Game_Ship::update(sf::Time& time)
{
	mShip.setRotation(mRotation);
	mShip.move(mVelocity*time.asSeconds());

	mPosition = mShip.getPosition();
	mBounds = mShip.getGlobalBounds();
	mShield.setPosition(mShip.getPosition());
}

void CometWars_Game_Ship::setPosition(sf::Vector2f param)
{
	mPosition = param;
	mShip.setPosition(mPosition);
	mShield.setPosition(mPosition);

	mBounds = mShip.getGlobalBounds();
}

void CometWars_Game_Ship::setVelocity(sf::Vector2f param)
{
	mVelocity = param;
}

void CometWars_Game_Ship::rotate_ship(float param)
{
	mRotation = param;
	mShip.setRotation(param);
}

void CometWars_Game_Ship::activate_sheld(bool Shield)
{
	is_Shield_Active = Shield;
}

void CometWars_Game_Ship::set_ship_invisible(bool param)
{
	if (param)
	{
		mShip.setFillColor(sf::Color::Transparent);
	}
	else
	{
		mShip.setFillColor(sf::Color::White);
	}
}

const bool CometWars_Game_Ship::getIs_Shield_active() const
{
	return is_Shield_Active;
}
