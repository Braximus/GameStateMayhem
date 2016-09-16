#include "stdafx.h"
#include "BreakTrough Laser.h"
#include "BreakTrough Data.h"


BrkTr_Laser::BrkTr_Laser(BreakTrough_Data& data)
{	
	marked_for_deletion = false;
	//	Graphically - what player sees, it exist two lasers.
	//	Logically, they are treated as a single object!

	m_Laser_left.setFillColor(sf::Color::Cyan);
	m_Laser_left.setSize(data.get_Component_Sizes(Break::size_Laser_Beam));
	sf::FloatRect bound = m_Laser_left.getLocalBounds();
	m_Laser_left.setOrigin(bound.width / 2, bound.height / 2);
	
	m_Laser_right.setFillColor(sf::Color::Cyan);
	m_Laser_right.setSize(data.get_Component_Sizes(Break::size_Laser_Beam));
	bound = m_Laser_right.getLocalBounds();
	m_Laser_right.setOrigin(bound.width / 2, bound.height / 2);
	m_Velocity = sf::Vector2f(0,-data.get_Speed(Break::speed_Laser_Beam));

	distance_from_paddle_centre = data.get_Component_Sizes(Break::size_Paddle_Default).x / 2 - data.get_Distances(Break::dis_Near);
}

void BrkTr_Laser::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_Laser_left, state);
	target.draw(m_Laser_right, state);
}

void BrkTr_Laser::setPosition(sf::Vector2f param)
{
	m_Position = param;
	m_Laser_left.setPosition(m_Position.x - distance_from_paddle_centre, m_Position.y);
	m_Laser_right.setPosition(m_Position.x + distance_from_paddle_centre, m_Position.y);
	m_Bounds = sf::FloatRect(m_Position.x - distance_from_paddle_centre, m_Position.y, 2 * distance_from_paddle_centre, m_Laser_left.getSize().y);
}

void BrkTr_Laser::update(sf::Time& time)
{
	m_Laser_left.move(m_Velocity*time.asSeconds());
	m_Laser_right.move(m_Velocity*time.asSeconds());

	m_Position.x += m_Velocity.x*time.asSeconds();
	m_Position.y += m_Velocity.y*time.asSeconds();

	m_Bounds = sf::FloatRect(m_Position.x - distance_from_paddle_centre, m_Position.y, 2 * distance_from_paddle_centre, m_Laser_left.getSize().y);
}

void BrkTr_Laser::setVelocity(sf::Vector2f param)
{
	m_Velocity = param;
}
