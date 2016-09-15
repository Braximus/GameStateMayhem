#ifndef BREAKTROUGH_LIVES_H
#define BREAKTROUGH_LIVES_H

#include "BreakTrough UI Objects.h"
class BreakTrough_Data;


class BrkTr_UI_Lives : public BrkTr_UI_Objects
{
	const sf::Texture&					m_Stored_Texture;
	sf::RectangleShape					m_Life;
	std::vector<sf::RectangleShape>		m_Lives;
	float								m_Lives_distance;
	sf::RectangleShape					m_Background;
	sf::VertexArray						m_Vertices;
public:
	explicit			BrkTr_UI_Lives(BreakTrough_Data& data);
	void				draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void				delete_life();
	void				add_life();
};




#endif