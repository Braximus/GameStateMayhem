#include "stdafx.h"
#include "BreakTrough PowerUp.h"
#include "BreakTrough Data.h"

BrkTr_PowerUp::BrkTr_PowerUp(BreakTrough_Data& data, Break::PowerUp_ID id, sf::Vector2f start_position)
{
	mPowerUp.setSize(data.get_Component_Sizes(Break::size_PowerUp));
	mPowerUp.setTexture(&data.get_Resources().getTexture(ID_BreakTrough));
	mPowerUp.setTextureRect(data.get_TextureRect(id));
	sf::FloatRect	bound = mPowerUp.getLocalBounds();
	mPowerUp.setOrigin(bound.width / 2, bound.height / 2);
	m_Velocity = sf::Vector2f(0, data.get_Speed(Break::speed_PowerUp));
	//	Za startnu poziciju moram da izracunam koji je blok u pitanju, da izracunam njegovu poziciju i da saberem sa polovinom duzine i visine bloka.
	mPowerUp.setPosition(start_position);
	
	mID = id;
	m_Position = mPowerUp.getPosition();
	m_Bounds = mPowerUp.getGlobalBounds();
}

void BrkTr_PowerUp::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mPowerUp, state);
}

//	Pojacanje samo ide u jednom smeru dokle god posotji.
void BrkTr_PowerUp::update(sf::Time& time)
{
	mPowerUp.move(m_Velocity*time.asSeconds());
	m_Position = mPowerUp.getPosition();
	m_Bounds = mPowerUp.getGlobalBounds();
}

const Break::PowerUp_ID BrkTr_PowerUp::pass_ID() const
{
	return mID;
}