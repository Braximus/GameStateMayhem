#ifndef BREAKTROUGH_GAME_OBJECTS_H
#define BREAKTROUGH_GAME_OBJECTS_H

#include "stdafx.h"
#include "BreakTrough Enumerations.h"

class BrkTr_Game_Objects : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Vector2f		m_Velocity;	//	Imam ideju povodom ovoga, ali cu da je implementiram kasnije - da napravim posebnu "MoveableObject" baznu klasu koju ce naslediti objekti koji se pomeraju
	sf::Vector2f		m_Position;
	sf::FloatRect		m_Bounds;
	bool				marked_for_deletion;
public:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates state) const {};
	virtual void		update(sf::Time&) {};

	virtual void			setPosition(sf::Vector2f) {};
	virtual void			setVelocity(sf::Vector2f) {};

	const sf::Vector2f		getPosition() const { return m_Position; };
	const sf::FloatRect		getBounds() const { return m_Bounds; };

	const bool				is_delete() const { return marked_for_deletion; };
	void					set_delete(bool param) { marked_for_deletion = param; };

};





#endif