#ifndef BREAKTROUGH_BLOCK_ARRAY_H
#define BREAKTROUGH_BLOCK_ARRAY_H

#include "BreakTrough Game Objects.h"
class BreakTrough_Data;
class BreakTrough_Level_Manager;

class BrkTr_Block_Array : public BrkTr_Game_Objects
{
	const sf::Texture&			mTex_ref;
	sf::VertexArray				m_Blocks;
public:
	BrkTr_Block_Array(BreakTrough_Data&);
	void			draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void			update(sf::Time& time);
	
	void			load_Blocks(BreakTrough_Data& data, std::vector<sf::Vector2f> positions, std::vector<Break::Block_ID> IDs, UINT number_of_blocks);
	void			remove_block(UINT indice);
	void			change_texture_coordinates(UINT indice, sf::IntRect coordinates);

	void			setPosition(sf::Vector2f param);
	void			setVelocity(sf::Vector2f param);


};








#endif