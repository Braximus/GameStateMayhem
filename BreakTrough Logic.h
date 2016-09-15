#ifndef BREAKTROUGH_LOGIC_H
#define BREAKTROUGH_LOGIC_H

#include "Debug.h"
#include "BreakTrough Level Manager.h"

class BreakTrough_Data;
class BreakTrough_Player;

class BreakTrough_UI_Manager;
class BrkTr_Ball;


class BreakTrough_Logic
{
	BreakTrough_Data&			mData;
	BreakTrough_Player*			pPlayer;
	BreakTrough_Level_Manager*	pLevel_Manager;
	BreakTrough_UI_Manager*		pUI_Manager; 
	
	UINT				score_buffer;
	
	std::vector<BreakTrough_Level_Manager::BoundryPosition>	boundry_hits;
	void				check_boundry_hits();

	void				check_Collisions();
	void				Paddle_Movement_restriction();
	sf::Vector2f		Ball_velocity_calculation(BrkTr_Ball& param);
	void				Ball_Random_direction_launch(bool is_left_boundry, BrkTr_Ball& ball);
	void				Ball_Block_Collision_response(BrkTr_Ball& ball);
	void				Ball_Level_Collision_response(BrkTr_Ball& ball);
	void				Ball_Paddle_Collision_response(BrkTr_Ball& ball);
	void				Ball_Lost();
	void				Ball_Block_Response(BrkTr_Ball& ball, sf::FloatRect bl);
	void				PowerUp_Behavior();
	void				PowerUp_Creation(sf::FloatRect param);
	void				Laser_Behavior_and_Block_Collision();
	void				Increase_Score(UINT);
	void				Reset_Block_animations();
	void				Block_hit(UINT indice, sf::FloatRect bl_bound);
	bool				erase_ball;
public:
	BreakTrough_Logic(BreakTrough_Data&);
	void		pass_Pointers(BreakTrough_Player* pPlay, BreakTrough_Level_Manager* pLevel, BreakTrough_UI_Manager* pUI);
	
	void		Logic_function();

};





#endif