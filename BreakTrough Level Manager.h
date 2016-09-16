#ifndef BREAKTROUGH_LEVEL_MANAGER_H
#define BREAKTROUGH_LEVEL_MANAGER_H

#include "BreakTrough Game Objects.h"
#include "BreakTrough Block Array.h"
#include "BreakTrough Playfield.h"
#include "BreakTrough PowerUp.h"
class BreakTrough_Data;

class BreakTrough_Level_Manager
{
public:
	enum BoundryPosition
	{
		Top,
		Middle,
		Bottom
	};
private:
	BreakTrough_Data&				mData;
	//	UINT represents the number of level;
	std::map<UINT, std::vector<sf::Vector2f>>			m_Block_Positions;
	std::map<UINT, std::vector<sf::FloatRect>>			m_Block_Boundries;
	std::map<UINT, std::vector<Break::Block_ID>>		m_Block_Type;
	std::map<BoundryPosition, sf::FloatRect>			m_Left_Level_Boudries;
	std::map<BoundryPosition, sf::FloatRect>			m_Right_Level_Boudries;
	std::map<UINT, std::vector<int>>					m_Block_Health;
	UINT												m_Number_of_Blocks;
	UINT												m_Number_of_Total_Blocks;
	UINT												m_Current_Level;
	
	

	std::unique_ptr<BrkTr_PowerUp>		pPower;	
	bool								powerUp_falls;
	
	BrkTr_Block_Array					mBlocks;
	BrkTr_Playfield						mLevel;
	void								preload_Levels();
public:
	BreakTrough_Level_Manager(BreakTrough_Data&);
	void			update(sf::Time&);
	void			Load_Level(UINT);

	void			create_PowerUp(sf::FloatRect block);
	void			delete_PowerUp();

	const sf::FloatRect					get_Level_Bounds() const;
	const std::map<BoundryPosition, sf::FloatRect>&		get_Left_Boundries() const;
	const std::map<BoundryPosition, sf::FloatRect>&		get_Right_Boundries() const;
	const sf::FloatRect					get_Block_Bounds(UINT indice) const;
	const int							get_Block_Health(UINT indice) const;
	const Break::Block_ID				get_Block_ID(UINT indice) const;

	const bool							does_PowerUp_falls() const;
	const UINT							get_Number_of_Blocks() const;
	const UINT							get_Number_of_Total_Blocks() const;
		
	std::unique_ptr<BrkTr_PowerUp>&		get_PowerUp();

	void								delete_Block(UINT indice);
	void								decrease_Block_Health(UINT);
	void								animate_Block_hit(UINT indice, Break::Block_ID param);
	void								reset_Block_Texture_coordinates(UINT indice, Break::Block_ID param);
	std::deque<BrkTr_Game_Objects*>		pass_Pointers();



};




#endif
