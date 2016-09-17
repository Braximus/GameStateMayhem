#include "stdafx.h"
#include "BreakTrough Playfield.h"
#include "BreakTrough Data.h"
#include "math.h"

BrkTr_Playfield::BrkTr_Playfield(BreakTrough_Data& data)
	: m_Texture(data.get_Resources().getTexture(ID_BreakTrough))
{	
	marked_for_deletion = false;
	std::default_random_engine& random = data.get_Random_Engine();
	sf::Vector2f sizef = data.get_Component_Sizes(Break::size_Deco_Background_slab);
	sf::Vector2f lvl_sizef = data.get_Key_Position(Break::kp_BottomRight);
	sf::Vector2i lvl_size = static_cast<sf::Vector2i>(lvl_sizef);
	sf::Vector2i size = static_cast<sf::Vector2i>(sizef);
	//	There is a problem when scaleing - a lines appear between the quads when the number is decimal.

	mBackground_Vertices.setPrimitiveType(sf::Quads);

	float x = std::ceil(lvl_sizef.x / sizef.x);
	float y = std::ceil(lvl_sizef.y / sizef.y);
	sf::Vector2i tile_number = sf::Vector2i(std::ceil(x), (std::ceil(y)));

	mBackground_Vertices.resize(4* (tile_number.x * tile_number.y));
	
	//	The laziest approach - I will use random numbers and use them as enum keys for textures.
	std::uniform_int_distribution<int>	percent(0, 100);

	UINT column = 0;
	UINT row = 0;
	sf::IntRect tx;

	for (UINT i = 0; i < mBackground_Vertices.getVertexCount(); i += 4)
	{
		if (column >= x)
		{
			column = 0;
			row++;
		}

		mBackground_Vertices[i].position = sf::Vector2f(size.x*column,size.y*row);
		mBackground_Vertices[i + 1].position = sf::Vector2f(size.x*column + size.x, size.y*row);
		mBackground_Vertices[i + 2].position = sf::Vector2f(size.x*column + size.x, size.y*row + size.y);
		mBackground_Vertices[i + 3].position = sf::Vector2f(size.x*column, size.y*row + size.y);
		++column;


		//	Now adding different textures;
		UINT per = percent(random);
		if (per < 50)
		{
			UINT sec_per = percent(random);
			if (sec_per <= 75)
			{
				tx = data.get_TextureRect(Break::t_Background_Deco3);
			}
			else if (sec_per < 50 && sec_per >= 25)
			{
				tx = data.get_TextureRect(Break::t_Background_Deco2);
			}
			else
			{
				tx = data.get_TextureRect(Break::t_Background_Deco1);
			}

		}
		else
		{
			tx = data.get_TextureRect(Break::t_Background_Deco4);
		}


		mBackground_Vertices[i].texCoords = sf::Vector2f(tx.left, tx.top);
		mBackground_Vertices[i + 1].texCoords = sf::Vector2f(tx.left + tx.width, tx.top);
		mBackground_Vertices[i + 2].texCoords = sf::Vector2f(tx.left + tx.width, tx.top + tx.height);
		mBackground_Vertices[i + 3].texCoords = sf::Vector2f(tx.left, tx.top + tx.height);

	}

	m_Playfield.setFillColor(sf::Color(32, 32, 32, 255));
	m_Playfield.setPosition(data.get_Components_Positions(Break::c_Level_Area));
	m_Playfield.setSize(data.get_Component_Sizes(Break::size_Level));
	sf::FloatRect b = m_Playfield.getLocalBounds();
	m_Playfield.setOrigin(b.width / 2, b.height / 2);

	m_Bounds = m_Playfield.getGlobalBounds();

	mOutline_Vertices.setPrimitiveType(sf::Quads);
	mOutline_Vertices.resize(76);

	sf::Vector2f p = m_Playfield.getPosition();
	sf::Vector2f s = m_Playfield.getSize();
	sf::Vector2f d = data.get_Component_Sizes(Break::size_Vertical_Outline);
	tx = data.get_TextureRect(Break::t_Level_Vertical);
	
	//	Peremiter of playfield
	for (UINT i = 0; i < mOutline_Vertices.getVertexCount(); i += 4)
	{	
		if (i < 24)
		{		
			//	Left side
			if (i == 0)
			{
				//	First part
				mOutline_Vertices[i].position = sf::Vector2f((p.x - s.x / 2) - d.x, p.y - s.y / 2);
				mOutline_Vertices[i + 1].position = sf::Vector2f(p.x - s.x / 2, p.y - s.y / 2);
				mOutline_Vertices[i + 2].position = sf::Vector2f(p.x - s.x / 2, (p.y - s.y / 2) + d.y);
				mOutline_Vertices[i + 3].position = sf::Vector2f((p.x - s.x / 2) - d.x, (p.y - s.y / 2) + d.y);
			}
			else
			{
				//	Rest
				p = mOutline_Vertices[i - 1].position;
				mOutline_Vertices[i].position = sf::Vector2f(p.x, p.y);
				mOutline_Vertices[i + 1].position = sf::Vector2f(p.x + d.x, p.y);
				mOutline_Vertices[i + 2].position = sf::Vector2f(p.x + d.x, p.y + d.y);
				mOutline_Vertices[i + 3].position = sf::Vector2f(p.x, p.y + d.y);
			}
		}
		else if (i >= 24 && i < 48)
		{
			//	Right side
			if (i == 24)
			{
				//	First part
				p = m_Playfield.getPosition();
				mOutline_Vertices[i].position = sf::Vector2f((p.x + s.x / 2), p.y - s.y / 2);
				mOutline_Vertices[i + 1].position = sf::Vector2f(p.x + s.x / 2 + d.x, p.y - s.y / 2);
				mOutline_Vertices[i + 2].position = sf::Vector2f(p.x + s.x / 2 + d.x, (p.y - s.y / 2) + d.y);
				mOutline_Vertices[i + 3].position = sf::Vector2f((p.x + s.x / 2), (p.y - s.y / 2) + d.y);
			}
			else
			{
				//	Rest
				p = mOutline_Vertices[i - 1].position;
				mOutline_Vertices[i].position = sf::Vector2f(p.x, p.y);
				mOutline_Vertices[i + 1].position = sf::Vector2f(p.x + d.x, p.y);
				mOutline_Vertices[i + 2].position = sf::Vector2f(p.x + d.x, p.y + d.y);
				mOutline_Vertices[i + 3].position = sf::Vector2f(p.x, p.y + d.y);
			}
		}
		else if (i >= 48 && i < 68)
		{
			//	Upper part
			if (i == 48)
			{
				//	First part
				p = m_Playfield.getPosition();
				d = data.get_Component_Sizes(Break::size_Horizontal_Outline);
				tx = data.get_TextureRect(Break::t_Level_Horizontal);

				mOutline_Vertices[i].position = sf::Vector2f((p.x - s.x / 2), p.y - s.y / 2 - d.y);
				mOutline_Vertices[i + 1].position = sf::Vector2f(p.x - s.x / 2 + d.x, p.y - s.y / 2 - d.y);
				mOutline_Vertices[i + 2].position = sf::Vector2f(p.x - s.x / 2 + d.x, (p.y - s.y / 2));
				mOutline_Vertices[i + 3].position = sf::Vector2f((p.x - s.x / 2), (p.y - s.y / 2));
			}
			else
			{
				//	Rest
				p = mOutline_Vertices[i - 2].position;
				mOutline_Vertices[i].position = sf::Vector2f(p.x, p.y - d.y);
				mOutline_Vertices[i + 1].position = sf::Vector2f(p.x + d.x, p.y - d.y);
				mOutline_Vertices[i + 2].position = sf::Vector2f(p.x + d.x, p.y);
				mOutline_Vertices[i + 3].position = sf::Vector2f(p.x, p.y);
			}

		}
		else if (i == 68)
		{
			//	Left upper angle
			p = m_Playfield.getPosition();
			d = data.get_Component_Sizes(Break::size_Corner_Outline);
			tx = data.get_TextureRect(Break::t_Level_TopLeft);
			mOutline_Vertices[i].position = sf::Vector2f((p.x - s.x / 2) - d.x, p.y - s.y / 2 - d.y);
			mOutline_Vertices[i + 1].position = sf::Vector2f(p.x - s.x / 2, p.y - s.y / 2 - d.y);
			mOutline_Vertices[i + 2].position = sf::Vector2f(p.x - s.x / 2, (p.y - s.y / 2));
			mOutline_Vertices[i + 3].position = sf::Vector2f((p.x - s.x / 2) - d.x, (p.y - s.y / 2));

		}
		else if (i == 72)
		{
			//	Right upper angle
			p = m_Playfield.getPosition();
			d = data.get_Component_Sizes(Break::size_Corner_Outline);
			tx = data.get_TextureRect(Break::t_Level_TopRight);
			mOutline_Vertices[i].position = sf::Vector2f((p.x + s.x / 2), p.y - s.y / 2 - d.y);
			mOutline_Vertices[i + 1].position = sf::Vector2f( (p.x + s.x / 2) + d.x, p.y - s.y / 2 - d.y);
			mOutline_Vertices[i + 2].position = sf::Vector2f(p.x + s.x / 2 + d.x, (p.y - s.y / 2));
			mOutline_Vertices[i + 3].position = sf::Vector2f((p.x + s.x / 2), (p.y - s.y / 2));
		}

		//	Textures
		mOutline_Vertices[i].texCoords = sf::Vector2f(tx.left, tx.top);
		mOutline_Vertices[i + 1].texCoords = sf::Vector2f(tx.left + tx.width, tx.top);
		mOutline_Vertices[i + 2].texCoords = sf::Vector2f(tx.left + tx.width, tx.top + tx.height);
		mOutline_Vertices[i + 3].texCoords = sf::Vector2f(tx.left, tx.top + tx.height);

	}
}

void BrkTr_Playfield::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = &m_Texture;
	target.draw(mBackground_Vertices, state);
	target.draw(m_Playfield, state);
	target.draw(mOutline_Vertices, state);
}

void BrkTr_Playfield::update(sf::Time& time)
{
	//
}
