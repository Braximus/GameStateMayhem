#ifndef BREAKTROUGH_PLAYFIELD_H
#define BREAKTROUGH_PLAYFIELD_H

#include "BreakTrough Game Objects.h"
class BreakTrough_Data;

class BrkTr_Playfield : public BrkTr_Game_Objects
{
	const sf::Texture&		m_Texture;
	sf::RectangleShape		m_Playfield;
	sf::VertexArray			mOutline_Vertices;


	//	Mozda ih prebacim u zasebnu klasu!
	sf::VertexArray			mBackground_Vertices;
public:
	BrkTr_Playfield(BreakTrough_Data&);

	void	draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void	update(sf::Time& time);
};




#endif
