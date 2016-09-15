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

//	Funkcija za ucitavanje blokova.
void BrkTr_Block_Array::load_Blocks(BreakTrough_Data& data, std::vector<sf::Vector2f> positions, std::vector<Break::Block_ID> IDs, UINT number_of_blocks)
{
	//	Uvek na pocetku moram da izbrisem sve blokove, a i potom da ih popunim sa odgovarajucim brojem temena.
	//	Posto su pravougaonici, jedan "objekat" ce imati cetiri temena.
	m_Blocks.clear();
	m_Blocks.setPrimitiveType(sf::Quads);
	m_Blocks.resize(4 * number_of_blocks);

	//	Uzimam velicinu bloka koji cu da koristim kao parametar za poziciju drugog, treceg i cetvrtog temena.
	sf::Vector2f siz = sf::Vector2f(data.get_Component_Sizes(Break::size_Block));
	UINT indice = 0;	//	Brojilac za temena.
	for (UINT i = 0; i < number_of_blocks; ++i)
	{
		//	Uzimam poziciju - ona oznacava mesto prvog temena, tj. gornji levi angle bloka.
		const sf::Vector2f& pos = positions.at(i);
		//	Potom uzimam boju, tj. nadimak za teksture koje cu kasnije pozvati.
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

//	Funckija koja brise blok...
void BrkTr_Block_Array::remove_block(UINT indice)
{
	//	...zapravo, samo menja boju da bude providno. :)
	UINT block = 4 * indice;
	m_Blocks[block].color = sf::Color::Transparent;
	m_Blocks[block + 1].color = sf::Color::Transparent;
	m_Blocks[block + 2].color = sf::Color::Transparent;
	m_Blocks[block + 3].color = sf::Color::Transparent;
	
}

//	Ovde se vrse animacije.
//	Funkcija samo izvrsava naredbu, nju ne zanima da li je ispravno.
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