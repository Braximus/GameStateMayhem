#ifndef BREAKTROUGH_PLAYER_H
#define BREAKTROUGH_PLAYER_H

#include "BreakTrough Game Objects.h"
#include "BreakTrough Ball.h"
#include "BreakTrough Paddle.h"
#include "BreakTrough Laser.h"
#include "BreakTrough PowerUp.h"

class BreakTrough_Data;

class BreakTrough_Player
{
	BreakTrough_Data&				mData;
	UINT						number_of_balls;
	std::deque<BrkTr_Ball>				mBalls;
	Break::Speeds					mCurrent_ball_speed;
	BrkTr_Paddle					mPaddle;
	Break::Paddle_Type				mCurrent_type, mPrevious_type;
	std::unique_ptr<BrkTr_Laser>			pLas;
	bool						has_fired;	
	std::map<Break::PowerUp_ID, sf::Time>		mActive_PowerUp_time;
	sf::Vector2f					previous_mouse_pos;
public:
	BreakTrough_Player(BreakTrough_Data&);
	void			update(sf::Time& time);
	std::deque<BrkTr_Game_Objects*> pass_Pointers();

	void			create_Laser();
	void			delete_Laser();
	const bool		has_fired_check() const;

	void			create_Balls();			//	Will always make 2 balls when there is only one;
	void			reset_Ball();		
	void			delete_Ball();		
	void			set_Ball_Speed(Break::Speeds);

	void			move_Paddle();
	void			start_Paddle_fade();
	void			fade_Paddle();
	void			set_Paddle_Type(Break::Paddle_Type);
	void			reset_Paddle();

	void			take_PowerUp(Break::PowerUp_ID);
	void			remove_PowerUp(Break::PowerUp_ID);


	std::deque<BrkTr_Ball>&				get_Balls();
	BrkTr_Paddle&					get_Paddle();
	std::unique_ptr<BrkTr_Laser>&			get_Laser();
		
	const UINT					get_number_of_Balls() const;
	const Break::Speeds				get_Current_Ball_Speed() const;
	const Break::Paddle_Type			get_Current_Paddle_Type() const;
	const bool					get_is_Paddle_fading() const;


	
	

};




#endif
