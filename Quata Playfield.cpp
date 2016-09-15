#include "stdafx.h"
#include "Quata Playfield.h"
#include "Quata Data.h"

Quata_Playfield::Quata_Playfield(QuataData& data)
	: stored_tex(data.get_Resources().getTexture(ID_Quata))
{
	m_LineVertices.setPrimitiveType(sf::Quads);
	m_LineVertices.resize(12);
	

	sf::Vector2f center = data.get_Key_Position(Qua::kp_Center_Screen);

	//Level.setFillColor(sf::Color(16, 16, 16, 255));
	Level.setTexture(&data.get_Resources().getTexture(ID_Quata_table));
	Level.setSize(data.get_Object_Size(Qua::size_Playground));
	sf::FloatRect bound = Level.getLocalBounds();
	Level.setOrigin(bound.width / 2, bound.height / 2);
	Level.setPosition(center);
	
	sf::Vector2f screensize = data.get_Object_Size(Qua::size_Playground);
	sf::Vector2f lineWidth = data.get_Object_Size(Qua::size_LineThickness);

	m_LineVertices[0].position = sf::Vector2f(center.x - lineWidth.x, center.y - screensize.y / 2);	//	width/2 - debljina linije, 0
	m_LineVertices[1].position = sf::Vector2f(center.x + lineWidth.x, center.y - screensize.y / 2);	//	width/2 + debljina linije, 0
	m_LineVertices[2].position = sf::Vector2f(center.x + lineWidth.x, center.y + screensize.y / 2);	//	width/2 + debljina linije, height
	m_LineVertices[3].position = sf::Vector2f(center.x - lineWidth.x, center.y + screensize.y / 2);	//	width/2 - debljina linije, height

	m_LineVertices[4].position = sf::Vector2f(center.x - screensize.x / 2, center.y - screensize.y / 2);					//	0,0
	m_LineVertices[5].position = sf::Vector2f(center.x + screensize.x / 2, center.y - screensize.y / 2);					//	width, 0
	m_LineVertices[6].position = sf::Vector2f(center.x + screensize.x / 2, (center.y - screensize.y / 2) + lineWidth.y);	//	width, 0 + debljina linije
	m_LineVertices[7].position = sf::Vector2f(center.x - screensize.x / 2, (center.y - screensize.y / 2) + lineWidth.y);	//	0, 0 + debljina linije

	m_LineVertices[8].position = sf::Vector2f(center.x - screensize.x / 2, (center.y + screensize.y / 2 - lineWidth.y));	//	0, height - debljina linije
	m_LineVertices[9].position = sf::Vector2f(center.x + screensize.x / 2, (center.y + screensize.y / 2 - lineWidth.y));	//	width, height - debljina linije
	m_LineVertices[10].position = sf::Vector2f(center.x + screensize.x / 2, center.y + screensize.y / 2);					//	width, height
	m_LineVertices[11].position = sf::Vector2f(center.x - screensize.x / 2, center.y + screensize.y / 2);					//	0, height

	//	Boje

	m_LineVertices[0].color = sf::Color::White;
	m_LineVertices[1].color = sf::Color::White;
	m_LineVertices[2].color = sf::Color::White;
	m_LineVertices[3].color = sf::Color::White;

	m_LineVertices[4].color = sf::Color::Green;
	m_LineVertices[5].color = sf::Color::Red;
	m_LineVertices[6].color = sf::Color::Red;
	m_LineVertices[7].color = sf::Color::Green;

	m_LineVertices[8].color = sf::Color::Green;
	m_LineVertices[9].color = sf::Color::Red;
	m_LineVertices[10].color = sf::Color::Red;
	m_LineVertices[11].color = sf::Color::Green;

	//	Pozadina:

	m_BackgroundVertices.setPrimitiveType(sf::Quads);
	sf::IntRect tx = data.get_Texture_rects(Qua::intrect_Background1);
	UINT column = 0;
	UINT row = 0;
	sf::Vector2f screen_sizef = data.get_Key_Position(Qua::kp_BottomRight_Corner);
	sf::Vector2f tex_sizef = data.get_Object_Size(Qua::size_Playground_texture);
	sf::Vector2i screen_size = static_cast<sf::Vector2i>(screen_sizef);
	sf::Vector2i tex_size = static_cast<sf::Vector2i>(tex_sizef);
	float x = std::ceil(screen_sizef.x / tex_sizef.x);
	float y = std::ceil(screen_sizef.y / tex_sizef.y);
	sf::Vector2i tile_number = sf::Vector2i(std::ceil(x), std::ceil(y));

	m_BackgroundVertices.resize(4 * (tile_number.x * tile_number.y));

	for (UINT i = 0; i < m_BackgroundVertices.getVertexCount(); i += 4)
	{
		if (column >= x)
		{
			column = 0;
			row++;
		}

		m_BackgroundVertices[i].position = sf::Vector2f(tex_size.x*column, tex_size.y*row);
		m_BackgroundVertices[i + 1].position = sf::Vector2f(tex_size.x*column + tex_size.x, tex_size.y*row);
		m_BackgroundVertices[i + 2].position = sf::Vector2f(tex_size.x*column + tex_size.x, tex_size.y*row + tex_size.y);
		m_BackgroundVertices[i + 3].position = sf::Vector2f(tex_size.x*column, tex_size.y*row + tex_size.y);
		++column;

		m_BackgroundVertices[i].texCoords = sf::Vector2f(tx.left, tx.top);
		m_BackgroundVertices[i + 1].texCoords = sf::Vector2f(tx.left + tx.width, tx.top);
		m_BackgroundVertices[i + 2].texCoords = sf::Vector2f(tx.left + tx.width, tx.top + tx.height);
		m_BackgroundVertices[i + 3].texCoords = sf::Vector2f(tx.left, tx.top + tx.height);

		m_BackgroundVertices[i].color = sf::Color(64,64,64,255);
		m_BackgroundVertices[i + 1].color = sf::Color(64, 64, 64, 255);
		m_BackgroundVertices[i + 2].color = sf::Color(64, 64, 64, 255);
		m_BackgroundVertices[i + 3].color = sf::Color(64, 64, 64, 255);

	}

}

void Quata_Playfield::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = &stored_tex;
	target.draw(m_BackgroundVertices, state);
	target.draw(Level);	
	target.draw(m_LineVertices);

}

void Quata_Playfield::setPosition(sf::Vector2f)
{
	// podrazumevano nista
}

const sf::Vector2f Quata_Playfield::getPosition() const
{
	return sf::Vector2f(0, 0);
}

