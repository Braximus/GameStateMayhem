#include "stdafx.h"
#include "BreakTrough Level Manager.h"
#include "BreakTrough Data.h"

BreakTrough_Level_Manager::BreakTrough_Level_Manager(BreakTrough_Data& data)
	: mData(data)
	, mLevel(mData)
	, mBlocks(mData)
{
	preload_Levels();
	powerUp_falls = false;

	float distance = data.get_Distances(Break::dis_Far);
	sf::Vector2f level_pos = sf::Vector2f(mLevel.getBounds().left, mLevel.getBounds().top);
	float third_of_level_Y = mLevel.getBounds().height/3;



	sf::FloatRect boundry = sf::FloatRect(level_pos.x - distance, level_pos.y, distance, third_of_level_Y);
	m_Left_Level_Boudries.insert(std::pair<BoundryPosition, sf::FloatRect>(Top, boundry));

	

	boundry = sf::FloatRect(level_pos.x - distance, level_pos.y + third_of_level_Y, distance, third_of_level_Y);
	m_Left_Level_Boudries.insert(std::pair<BoundryPosition, sf::FloatRect>(Middle, boundry));


	boundry = sf::FloatRect(level_pos.x - distance, level_pos.y + 2 * third_of_level_Y, distance, third_of_level_Y);
	m_Left_Level_Boudries.insert(std::pair<BoundryPosition, sf::FloatRect>(Bottom, boundry));


	level_pos = sf::Vector2f(mLevel.getBounds().left + mLevel.getBounds().width, mLevel.getBounds().top);
	boundry = sf::FloatRect(level_pos.x, level_pos.y, distance, third_of_level_Y);
	m_Right_Level_Boudries.insert(std::pair<BoundryPosition, sf::FloatRect>(Top, boundry));


	boundry = sf::FloatRect(level_pos.x, level_pos.y + third_of_level_Y, distance, third_of_level_Y);
	m_Right_Level_Boudries.insert(std::pair<BoundryPosition, sf::FloatRect>(Middle, boundry));


	boundry = sf::FloatRect(level_pos.x, level_pos.y + 2 * third_of_level_Y, distance, third_of_level_Y);
	m_Right_Level_Boudries.insert(std::pair<BoundryPosition, sf::FloatRect>(Bottom, boundry));

}

void BreakTrough_Level_Manager::update(sf::Time& time)
{
	if (powerUp_falls)
		pPower->update(time);
}

void BreakTrough_Level_Manager::Load_Level(UINT param)
{
	m_Current_Level = param;
	if (m_Current_Level <= m_Block_Positions.size())
	{
		m_Number_of_Blocks = m_Block_Positions.at(m_Current_Level).size();
		m_Number_of_Total_Blocks = m_Number_of_Blocks;
		mBlocks.load_Blocks(mData, m_Block_Positions.at(m_Current_Level), m_Block_Type.at(m_Current_Level), m_Number_of_Blocks);
		for (const int& health: m_Block_Health.at(m_Current_Level))
		{
			//	Svi blokovi koji imaju zivot jednak ili manje od nule (tzv, mrtvi i neranjivi) se ne racunaju u blokove koje\
			treba unistiti i oduzimaju se;
			if (health <= 0)
				m_Number_of_Blocks -= 1;
		}
		

	}
}

void BreakTrough_Level_Manager::preload_Levels()
{
	std::vector<sf::FloatRect>	 block_bounds;
	std::vector<sf::Vector2f>	 rows_and_coloumns;
	std::vector<Break::Block_ID> sorted_Block_IDs;
	std::vector<int>			 block_health;
	UINT coloumns;
	UINT rows;
	
	//** PRVI NIVO **//
	
	//	Pozicije blokova po nivou
	coloumns = 10;
	rows = 7;

	for (UINT i = 0; i < rows; ++i)
	{
		int health = 1;
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;
			rows_and_coloumns.push_back(sf::Vector2f(a, b));
			if (i == 0)
			{
				sorted_Block_IDs.push_back(Break::bID_Grey);
				health = 2;
			}
			else
			{
				sorted_Block_IDs.push_back(static_cast<Break::Block_ID>(i - 1));
			}
			block_health.push_back(health);
		}
	}

	//	granice blokova
	block_bounds.reserve(rows*coloumns);
	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;	//	Left
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;	//	Top
			float c = mData.get_Component_Sizes(Break::size_Block).x;														//	Width
			float d = mData.get_Component_Sizes(Break::size_Block).y;														//	Height
			block_bounds.push_back(sf::FloatRect(a, b, c, d));
		}
	}

	m_Block_Positions.insert(std::pair<UINT, std::vector<sf::Vector2f>>(1, std::move(rows_and_coloumns)));
	m_Block_Type.insert(std::pair<UINT, std::vector<Break::Block_ID>>(1, std::move(sorted_Block_IDs)));
	m_Block_Health.insert(std::pair<UINT, std::vector<int>>(1, std::move(block_health)));
	m_Block_Boundries.insert(std::pair<UINT, std::vector<sf::FloatRect>>(1, std::move(block_bounds)));
	
	//** KRAJ PRVOG NIVOA **//

	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	//** DRUGI NIVO **//
	//	Pozicije blokova po nivou
	coloumns = 10;
	rows = 12;
	
	for (UINT i = 0; i < rows; ++i)
	{

		for (UINT j = 0; j < coloumns; ++j)
		{
			int health = 1;
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;
			rows_and_coloumns.push_back(sf::Vector2f(a, b));
			if (j > i - 2 || i < 2)
			{
				sorted_Block_IDs.push_back(Break::bID_None);
				health = 0;
			}
			else if (i == 11)
			{
				if (j < 9)
				{
					sorted_Block_IDs.push_back(Break::bID_Grey);
					health = 2;
				}
				else
					sorted_Block_IDs.push_back(Break::bID_Red);
			}
			else if (j == 1 || j == 4 || j == 7)
			{
				sorted_Block_IDs.push_back(Break::bID_Cyan);
			}
			else if (j == 2 || j == 5 || j == 8)
			{
				sorted_Block_IDs.push_back(Break::bID_Yellow);
			}
			else
			{
				sorted_Block_IDs.push_back(Break::bID_Green);
			}
			block_health.push_back(health);
		}
	}

	//	granice blokova

	block_bounds.reserve(rows*coloumns);
	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;	//	Left
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;	//	Top
			float c = mData.get_Component_Sizes(Break::size_Block).x;														//	Width
			float d = mData.get_Component_Sizes(Break::size_Block).y;														//	Height
			block_bounds.push_back(sf::FloatRect(a, b, c, d));
		}
	}


	m_Block_Positions.insert(std::pair<UINT, std::vector<sf::Vector2f>>(2, std::move(rows_and_coloumns)));
	m_Block_Type.insert(std::pair<UINT, std::vector<Break::Block_ID>>(2, std::move(sorted_Block_IDs)));
	m_Block_Health.insert(std::pair<UINT, std::vector<int>>(2, std::move(block_health)));
	m_Block_Boundries.insert(std::pair<UINT, std::vector<sf::FloatRect>>(2, std::move(block_bounds)));
	
	//** KRAJ DRUGOG NIVOA **//

	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	//** TRECI NIVO **//

	coloumns = 10;
	rows = 11;

	for (UINT i = 0; i < rows; ++i)
	{

		for (UINT j = 0; j < coloumns; ++j)
		{
			int health = 1;
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;
			rows_and_coloumns.push_back(sf::Vector2f(a, b));
			if (i == 0 || i == 8)
			{
				sorted_Block_IDs.push_back(Break::bID_Orange);
			}
			else if (i == 9)
			{
				sorted_Block_IDs.push_back(Break::bID_Yellow);
			}
			else if (i == 10)
			{
				sorted_Block_IDs.push_back(Break::bID_Grey);
				health = 2;
			}
			else if (i == 2 || i == 4)
			{
				if (j == 1 || j == 2 || j == 3 || j == 6 || j == 7 || j == 8)
				{
					sorted_Block_IDs.push_back(Break::bID_Grey);
					health = 2;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_None);
					health = 0;
				}
			}
			else if (i == 3)
			{
				if (j == 1 || j == 3 || j == 6 || j == 8)
				{
					sorted_Block_IDs.push_back(Break::bID_Grey);
					health = 2;
				}
				else if (j == 2 || j == 7)
				{
					sorted_Block_IDs.push_back(Break::bID_Yellow);
					health = 1;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_None);
					health = 0;
				}
			}
			else if (i == 6)
			{
				if (j == 4 || j == 5)
				{
					sorted_Block_IDs.push_back(Break::bID_Red);
					health = 1;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_None);
					health = 0;
				}
			}
			else
			{
				sorted_Block_IDs.push_back(Break::bID_None);
				health = 0;
			}
			block_health.push_back(health);
		}
	}

	//	granice blokova

	block_bounds.reserve(rows*coloumns);
	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;	//	Left
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;	//	Top
			float c = mData.get_Component_Sizes(Break::size_Block).x;														//	Width
			float d = mData.get_Component_Sizes(Break::size_Block).y;														//	Height
			block_bounds.push_back(sf::FloatRect(a, b, c, d));
		}
	}

	m_Block_Positions.insert(std::pair<UINT, std::vector<sf::Vector2f>>(3, std::move(rows_and_coloumns)));
	m_Block_Type.insert(std::pair<UINT, std::vector<Break::Block_ID>>(3, std::move(sorted_Block_IDs)));
	m_Block_Health.insert(std::pair<UINT, std::vector<int>>(3, std::move(block_health)));
	m_Block_Boundries.insert(std::pair<UINT, std::vector<sf::FloatRect>>(3, std::move(block_bounds)));


	//** KRAJ TRECEG NIVOA **//
	
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	//** CETVRTI NIVO **//

	//	Pozicije blokova po nivou
	coloumns = 10;
	rows = 11;

	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			UINT odd = (i + j) % 2;

			int health = 1;
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;
			rows_and_coloumns.push_back(sf::Vector2f(a, b));
			if (j == 3 || j == 6)
			{
				sorted_Block_IDs.push_back(Break::bID_None);
				health = 0;
			}
			else if (i == 5)
			{
				if (j == 4 || j == 5)
				{
					sorted_Block_IDs.push_back(Break::bID_Grey);
					health = 2;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_Gold);
					health = -1;
				}

			}
			else if (i == 0 || i == 10)
			{
				sorted_Block_IDs.push_back(Break::bID_Grey);
				health = 2;
			}
			else if (odd != 0 && i < 5)
			{
				sorted_Block_IDs.push_back(Break::bID_Yellow);
			}
			else if (odd == 0 && i < 5)
			{
				sorted_Block_IDs.push_back(Break::bID_Cyan);
			}
			else if (odd != 0 && i > 5)
			{
				sorted_Block_IDs.push_back(Break::bID_Red);
			}
			else
			{
				sorted_Block_IDs.push_back(Break::bID_OceanBlue);
			}
			block_health.push_back(health);

		}
	}

	//	granice blokova

	block_bounds.reserve(rows*coloumns);
	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;	//	Left
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;	//	Top
			float c = mData.get_Component_Sizes(Break::size_Block).x;														//	Width
			float d = mData.get_Component_Sizes(Break::size_Block).y;														//	Height
			block_bounds.push_back(sf::FloatRect(a, b, c, d));
		}
	}

	m_Block_Positions.insert(std::pair<UINT, std::vector<sf::Vector2f>>(4, std::move(rows_and_coloumns)));
	m_Block_Type.insert(std::pair < UINT, std::vector<Break::Block_ID>>(4, std::move(sorted_Block_IDs)));
	m_Block_Health.insert(std::pair<UINT, std::vector<int>>(4, std::move(block_health)));
	m_Block_Boundries.insert(std::pair<UINT, std::vector<sf::FloatRect>>(4, std::move(block_bounds)));

	//** KRAJ CETVRTOG NIVOA **//
	
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	//** PETI NIVO **//

	coloumns = 10;
	rows = 13;

	for (UINT i = 0; i < rows; ++i)
	{

		for (UINT j = 0; j < coloumns; ++j)
		{
			UINT odd = (i + j) % 2;
			int health = 1;
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;
			rows_and_coloumns.push_back(sf::Vector2f(a, b));

			if (i == 10)
			{
				if (j == 4 || j == 5)
				{
					sorted_Block_IDs.push_back(Break::bID_Orange);
				}
				else if (j == 0 || j == 9)
				{
					sorted_Block_IDs.push_back(Break::bID_None);
					health = 0;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_Gold);
					health = -1;
				}
			}
			else if (i == 11)
			{
				sorted_Block_IDs.push_back(Break::bID_Purple);
			}
			else if (i == 12)
			{
				sorted_Block_IDs.push_back(Break::bID_Red);
			}
			else if (j == 0 || j == 9)
			{
				sorted_Block_IDs.push_back(Break::bID_None);
				health = 0;
			}
			else if (j == 1 || j == 8)
			{
				sorted_Block_IDs.push_back(Break::bID_Gold);
				health = -1;
			}
			else if (j < 4)
			{
				sorted_Block_IDs.push_back(Break::bID_Green);
			}
			else if (j > 5)
			{
				sorted_Block_IDs.push_back(Break::bID_Blue);
			}
			else if (odd != 0)
			{
				sorted_Block_IDs.push_back(Break::bID_Green);
			}
			else if (odd == 0)
			{
				sorted_Block_IDs.push_back(Break::bID_Blue);
			}


			block_health.push_back(health);
		}
	}

	//	granice blokova

	block_bounds.reserve(rows*coloumns);
	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;	//	Left
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;	//	Top
			float c = mData.get_Component_Sizes(Break::size_Block).x;														//	Width
			float d = mData.get_Component_Sizes(Break::size_Block).y;														//	Height
			block_bounds.push_back(sf::FloatRect(a, b, c, d));
		}
	}

	m_Block_Positions.insert(std::pair<UINT, std::vector<sf::Vector2f>>(5, std::move(rows_and_coloumns)));
	m_Block_Type.insert(std::pair<UINT, std::vector<Break::Block_ID>>(5, std::move(sorted_Block_IDs)));
	m_Block_Health.insert(std::pair<UINT, std::vector<int>>(5, std::move(block_health)));
	m_Block_Boundries.insert(std::pair<UINT, std::vector<sf::FloatRect>>(5, std::move(block_bounds)));

	//** KRAJ PETOG NIVOA**//

	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	//** SETSI NIVO **//

	coloumns = 10;
	rows = 12;

	for (UINT i = 0; i < rows; ++i)
	{
		
		for (UINT j = 0; j < coloumns; ++j)
		{
			int health = 1;
			UINT odd = (i + j) % 2;
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;
			rows_and_coloumns.push_back(sf::Vector2f(a, b));

			if (i >= 9)
			{
				if (odd != 0)
				{
					sorted_Block_IDs.push_back(Break::bID_Grey);
					health = 2;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_OceanBlue);
					health = 1;
				}
			}
			else if (i == 7)
			{
				if ((j >= 0 && j < 3) || (j >= 7 && j < 10))
				{
					sorted_Block_IDs.push_back(Break::bID_Gold);
					health = -1;
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_Grey);
					health = 2;
				}
			}
			else if (i == 6 || i == 8)
			{
				sorted_Block_IDs.push_back(Break::bID_None);
				health = 0;
			}
			else
			{
				if (j == 0)
				{
					sorted_Block_IDs.push_back(Break::bID_Yellow);
				}
				else if (j == 2)
				{
					sorted_Block_IDs.push_back(Break::bID_Red);
				}
				else if (j >= 4 && j < 6 )
				{
					sorted_Block_IDs.push_back(Break::bID_Orange);
				}
				else if (j == 7)
				{
					sorted_Block_IDs.push_back(Break::bID_Green);
				}
				else if (j == 9)
				{
					sorted_Block_IDs.push_back(Break::bID_Blue);
				}
				else
				{
					sorted_Block_IDs.push_back(Break::bID_None);
					health = 0;
				}
			}
			block_health.push_back(health);

		}
	}

	//	granice blokova

	block_bounds.reserve(rows*coloumns);
	for (UINT i = 0; i < rows; ++i)
	{
		for (UINT j = 0; j < coloumns; ++j)
		{
			float a = mData.get_Components_Positions(Break::c_Blocks).x + j*mData.get_Component_Sizes(Break::size_Block).x;	//	Left
			float b = mData.get_Components_Positions(Break::c_Blocks).y + i*mData.get_Component_Sizes(Break::size_Block).y;	//	Top
			float c = mData.get_Component_Sizes(Break::size_Block).x;														//	Width
			float d = mData.get_Component_Sizes(Break::size_Block).y;														//	Height
			block_bounds.push_back(sf::FloatRect(a, b, c, d));
		}
	}

	m_Block_Positions.insert(std::pair<UINT, std::vector<sf::Vector2f>>(6, std::move(rows_and_coloumns)));
	m_Block_Type.insert(std::pair<UINT, std::vector<Break::Block_ID>>(6, std::move(sorted_Block_IDs)));
	m_Block_Health.insert(std::pair<UINT, std::vector<int>>(6, std::move(block_health)));
	m_Block_Boundries.insert(std::pair<UINT, std::vector<sf::FloatRect>>(6, std::move(block_bounds)));


	//** KRAJ SESTOG NIVOA**// 


}

void BreakTrough_Level_Manager::create_PowerUp(sf::FloatRect block)
{
	//	Nasumicno bira jedan od osam tipova powerUp-ova;
	std::uniform_int_distribution<int>	dis_2(0, 7);
	UINT number_2 = dis_2(mData.get_Random_Engine());
	Break::PowerUp_ID power_id = static_cast<Break::PowerUp_ID>(number_2);
	//	Odredjuje poziciju powerUp-a u zavisnosti od pozicije bloka i potom stavlja u zaseban pointer. 
	sf::Vector2f position = sf::Vector2f(block.left + block.width / 2, block.top + block.height / 2);
	pPower = std::unique_ptr<BrkTr_PowerUp>(new BrkTr_PowerUp(mData, power_id, position));
	powerUp_falls = true;
}

void BreakTrough_Level_Manager::delete_PowerUp()
{
	pPower.release();
	powerUp_falls = false;
}


const sf::FloatRect BreakTrough_Level_Manager::get_Level_Bounds() const
{
	return mLevel.getBounds();
}

const std::map<BreakTrough_Level_Manager::BoundryPosition, sf::FloatRect>& BreakTrough_Level_Manager::get_Left_Boundries() const
{
	return m_Left_Level_Boudries;
}

const std::map<BreakTrough_Level_Manager::BoundryPosition, sf::FloatRect>& BreakTrough_Level_Manager::get_Right_Boundries() const
{
	return m_Right_Level_Boudries;
}

const sf::FloatRect BreakTrough_Level_Manager::get_Block_Bounds(UINT indice) const
{
	return m_Block_Boundries.at(m_Current_Level).at(indice);
}

const int BreakTrough_Level_Manager::get_Block_Health(UINT indice) const
{
	return m_Block_Health.at(m_Current_Level).at(indice);
}

const Break::Block_ID BreakTrough_Level_Manager::get_Block_ID(UINT indice) const
{
	return m_Block_Type.at(m_Current_Level).at(indice);
}

const bool BreakTrough_Level_Manager::does_PowerUp_falls() const
{
	return powerUp_falls;
}

const UINT BreakTrough_Level_Manager::get_Number_of_Blocks() const
{
	return m_Number_of_Blocks;
}

const UINT BreakTrough_Level_Manager::get_Number_of_Total_Blocks() const
{
	return m_Number_of_Total_Blocks;
}

std::unique_ptr<BrkTr_PowerUp>& BreakTrough_Level_Manager::get_PowerUp()
{
	return pPower;
}

void BreakTrough_Level_Manager::delete_Block(UINT indice)
{
	m_Block_Health.at(m_Current_Level).at(indice) = false;
	mBlocks.remove_block(indice);
	m_Number_of_Blocks -= 1;
}

void BreakTrough_Level_Manager::decrease_Block_Health(UINT indice)
{
	m_Block_Health.at(m_Current_Level).at(indice) -= 1;
}

void BreakTrough_Level_Manager::animate_Block_hit(UINT indice, Break::Block_ID param)
{
	sf::IntRect coordinates = mData.get_TextureRect(param);
	coordinates.left += coordinates.width;
	mBlocks.change_texture_coordinates(indice, coordinates);
}

void BreakTrough_Level_Manager::reset_Block_Texture_coordinates(UINT indice, Break::Block_ID param)
{
	sf::IntRect coordinates = mData.get_TextureRect(param);
	mBlocks.change_texture_coordinates(indice, coordinates);
}

std::deque<BrkTr_Game_Objects*> BreakTrough_Level_Manager::pass_Pointers()
{
	std::deque<BrkTr_Game_Objects*>	temp_deque;
	BrkTr_Game_Objects*				ptr;
	ptr = &mLevel;
	temp_deque.push_back(std::move(ptr));
	ptr = &mBlocks;
	temp_deque.push_back(std::move(ptr));
	if (powerUp_falls)
	{
		ptr = pPower.get();
		temp_deque.push_back(std::move(ptr));
	}

	return temp_deque;
}
