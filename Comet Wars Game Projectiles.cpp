#include "stdafx.h"
#include "Comet Wars Game Projectiles.h"
#include "Comet Wars Data.h"

CometWars_Game_Projectiles::CometWars_Game_Projectiles(CometWarsData& data)
{
	is_deleted = false;
	mProjectile.setRadius(data.getObj_Sizes(CW::size_Projectile).x);
	mProjectile.setFillColor(sf::Color::Cyan);
	sf::FloatRect b = mProjectile.getLocalBounds();
	mProjectile.setOrigin(b.width / 2, b.height / 2);
}

void CometWars_Game_Projectiles::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mProjectile, state);
}

void CometWars_Game_Projectiles::update(sf::Time& time)
{
	mProjectile.move(mVelocity*time.asSeconds());
	mBounds = mProjectile.getGlobalBounds();
}

void CometWars_Game_Projectiles::setPosition(sf::Vector2f param)
{
	mProjectile.setPosition(param);
	mPosition = param;

	mBounds = mProjectile.getGlobalBounds();
}

void CometWars_Game_Projectiles::setVelocity(sf::Vector2f param)
{
	mVelocity = param;
}