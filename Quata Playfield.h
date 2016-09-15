#ifndef QUATA_PLAYFIELD_H
#define QUATA_PLAYFIELD_H


#include "Quata Objects.h"
class QuataData;

class Quata_Playfield : public QuataObjects
{
	sf::RectangleShape		Level;
	const sf::Texture&		stored_tex;
	sf::VertexArray			m_LineVertices;
	sf::VertexArray			m_BackgroundVertices;
public:
	explicit				Quata_Playfield(QuataData&);

	void					draw(sf::RenderTarget&, sf::RenderStates) const;
	void					setPosition(sf::Vector2f);
	const sf::Vector2f		getPosition() const;
};



#endif