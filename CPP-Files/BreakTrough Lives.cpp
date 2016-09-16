#include "stdafx.h"
#include "BreakTrough Lives.h"
#include "BreakTrough Data.h"

BrkTr_UI_Lives::BrkTr_UI_Lives(BreakTrough_Data& data)
	: m_Stored_Texture(data.get_Resources().getTexture(ID_BreakTrough))
{
	m_Lives_distance = data.get_Distances(Break::dis_Near) + data.get_Component_Sizes(Break::size_Paddle_Default).y;
	

	m_Life.setTexture(&m_Stored_Texture);
	m_Life.setTextureRect(data.get_TextureRect(Break::Paddle_Default));
	m_Life.setSize(data.get_Component_Sizes(Break::size_Paddle_Default));
	m_Life.setPosition(data.get_UI_Components_Positions(Break::cUI_Lives));
	m_Life.setScale(0.5f, 0.5f);
	for (UINT i = 0; i < data.get_Object_Quantities(Break::Number_of_Lives); ++i)
	{
		sf::RectangleShape	spr = m_Life;
		spr.setPosition(m_Life.getPosition().x, m_Life.getPosition().y + i * m_Lives_distance);
		m_Lives.push_back(spr);
	}

	m_Background.setOutlineColor(sf::Color::Yellow);
	m_Background.setOutlineThickness(-1);
	m_Background.setFillColor(sf::Color(32, 32, 32, 255));
	m_Background.setSize(sf::Vector2f(m_Life.getSize().x, 5*(m_Life.getSize().y + m_Lives_distance) ));
	m_Background.setPosition(m_Life.getPosition().x - data.get_Distances(Break::dis_Medium), m_Life.getPosition().y - data.get_Distances(Break::dis_Medium));

	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(32);

	sf::Vector2f bp = m_Background.getPosition();
	sf::Vector2f bs = m_Background.getSize();
	sf::IntRect tx = data.get_TextureRect(Break::t_Decoration_Feature_Corner2);
	sf::Vector2f size = data.get_Component_Sizes(Break::size_Deco_Bolt);

	sf::Vector2f pos; 

	for (UINT i = 0; i < m_Vertices.getVertexCount(); i += 4)
	{
		if (i == 0)
		{
			pos = sf::Vector2f(bp.x - size.x, bp.y - size.y);
		}
		else if (i == 4)
		{
			pos = sf::Vector2f(bp.x + bs.x, bp.y - size.y);
		}
		else if (i == 8)
		{
			pos = sf::Vector2f(bp.x + bs.x, bp.y + bs.y);
		}
		else if (i == 12)
		{
			pos = sf::Vector2f(bp.x - size.x , bp.y + bs.y);
		}
		else if (i == 16)
		{
			size = sf::Vector2f(data.get_Component_Sizes(Break::size_Deco_Vertical_border).x, bs.y);//data.get_Component_Sizes(Break::size_Deco_Vertical_border);
			tx = data.get_TextureRect(Break::t_Decoration_Feature_Vertical2);
			pos = sf::Vector2f(bp.x - size.x, bp.y);
		}
		else if (i == 20)
		{
			pos = sf::Vector2f(bp.x + bs.x, bp.y);
		}
		else if (i == 24)
		{
			size = sf::Vector2f(bs.x, data.get_Component_Sizes(Break::size_Deco_Horizontal_border).y);//data.get_Component_Sizes(Break::size_Deco_Horizontal_border);
			tx = data.get_TextureRect(Break::t_Decoration_Feature_Horizontal2);
			pos = sf::Vector2f(bp.x, bp.y - size.y);
		}
		else if (i == 28)
		{
			pos = sf::Vector2f(bp.x, bp.y + bs.y);
		}

		m_Vertices[i].position = pos;
		m_Vertices[i + 1].position = sf::Vector2f(pos.x + size.x, pos.y);
		m_Vertices[i + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
		m_Vertices[i + 3].position = sf::Vector2f(pos.x, pos.y + size.y);

		m_Vertices[i].texCoords = sf::Vector2f(tx.left, tx.top); 
		m_Vertices[i + 1].texCoords = sf::Vector2f(tx.left + tx.width, tx.top);
		m_Vertices[i + 2].texCoords = sf::Vector2f(tx.left + tx.width, tx.top + tx.height);
		m_Vertices[i + 3].texCoords = sf::Vector2f(tx.left, tx.top + tx.height);

	}
}

void BrkTr_UI_Lives::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = &m_Stored_Texture;
	target.draw(m_Vertices, state);
	target.draw(m_Background, state);
	for (const sf::RectangleShape& it : m_Lives)
	{
		target.draw(it);
	}
}

void BrkTr_UI_Lives::add_life()
{
	//	New life object is added bellow the last one.
	size_t i = std::distance(m_Lives.begin(), m_Lives.end());
	sf::RectangleShape	spr = m_Life;
	spr.setPosition(m_Life.getPosition().x, m_Life.getPosition().y + i * m_Lives_distance);
	m_Lives.push_back(spr);
}

void BrkTr_UI_Lives::delete_life()
{
	if (m_Lives.size() != 0)
	{
		m_Lives.pop_back();
	}
}
