#include "stdafx.h"
#include "BreakTrough Block Array.h"
#include "BreakTrough Data.h"
#include "BreakTrough Level Manager.h"


BrkTr_Block_Array::BrkTr_Block_Array(BreakTrough_Data& data)
	: mTex_ref(data.get_Resources().getTexture(ID_BreakTrough))
{
	
	marked_for_deletion = false;
}

void BrkTr_Block_Array::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = &mTex_ref;
	target.draw(m_Blocks, state);

}

void BrkTr_Block_Array::update(sf::Time& time)
{
	//
}

void BrkTr_Block_Array::load_Blocks(BreakTrough_Data& data, std::vector<sf::Vector2f> positions, std::vector<Break::Block_ID> IDs, UINT number_of_blocks)
{
	//	In the begining I need to delete all blocks and then to fill them with apropriate amount of vertices.
	//	Since they are rectangles, one "object" will have four vertices.
	m_Blocks.clear();
	m_Blocks.setPrimitiveType(sf::Quads);
	m_Blocks.resize(4 * number_of_blocks);

	//	I take the size of a rectangle and use it as a parameter for second, third and fourth vertice.
	sf::Vector2f siz = sf::Vector2f(data.get_Component_Sizes(Break::size_Block));
	UINT indice = 0;
	for (UINT i = 0; i < number_of_blocks; ++i)
	{
		//	I take the position - it defines the top left corner of object, i.e. the first vertice.
		const sf::Vector2f& pos = positions.at(i);
		//	Then I take the enumeration for texture.
		Break::Block_ID color = IDs.at(i);
		m_Blocks[indice].position = sf::Vector2f(pos);
		m_Blocks[indice].texCoords = sf::Vector2f(data.get_TextureRect(color).left, data.get_TextureRect(color).top);
		indice++;
		m_Blocks[indice].position = sf::Vector2f(pos.x + siz.x, pos.y);
		m_Blocks[indice].texCoords = sf::Vector2f(data.get_TextureRect(color).left + data.get_TextureRect(color).width, data.get_TextureRect(color).top);
		indice++;
		m_Blocks[indice].position = sf::Vector2f(pos.x + siz.x, pos.y + siz.y);
		m_Blocks[indice].texCoords = sf::Vector2f(data.get_TextureRect(color).left + data.get_TextureRect(color).width, data.get_TextureRect(color).top + data.get_TextureRect(color).height);
		indice++;
		m_Blocks[indice].position = sf::Vector2f(pos.x, pos.y + siz.y);
		m_Blocks[indice].texCoords = sf::Vector2f(data.get_TextureRect(color).left, data.get_TextureRect(color).top + data.get_TextureRect(color).height);
		indice++;
	}
}

//	Function that deletes the bloc...
void BrkTr_Block_Array::remove_block(UINT indice)
{
	//	...actualy, it only changes it's color to be transparent. :)
	UINT block = 4 * indice;
	m_Blocks[block].color = sf::Color::Transparent;
	m_Blocks[block + 1].color = sf::Color::Transparent;
	m_Blocks[block + 2].color = sf::Color::Transparent;
	m_Blocks[block + 3].color = sf::Color::Transparent;
	
}

//	Here the animations take place.
//	Function doesn't care whether coordtinates are is correct or not.
void BrkTr_Block_Array::change_texture_coordinates(UINT indice, sf::IntRect coordinates)
{
	UINT block = 4 * indice;
	m_Blocks[block].texCoords = sf::Vector2f(coordinates.left, coordinates.top);
	m_Blocks[block + 1].texCoords = sf::Vector2f(coordinates.left + coordinates.width, coordinates.top);
	m_Blocks[block + 2].texCoords = sf::Vector2f(coordinates.left + coordinates.width, coordinates.top + coordinates.height);
	m_Blocks[block + 3].texCoords = sf::Vector2f(coordinates.left, coordinates.top + coordinates.height);
}

void BrkTr_Block_Array::setPosition(sf::Vector2f)
{
	//
}

void BrkTr_Block_Array::setVelocity(sf::Vector2f)
{
	//
}
