#include "stdafx.h"
#include "Quata Logic.h"
#include "Quata Data.h"
#include "Quata Level.h"
#include "Quata AI.h"
#include "Quata Player.h"
#include "Quata UI Manager.h"


QuataLogic::QuataLogic(QuataData& data)
	: mData(data)
{
	//
};

void QuataLogic::get_pointers(Quata_Player* player, QuataAI* AI, Quata_Level* level, Quata_UI_Manager* ui)
{
	pPlayer = player;
	pAI = AI;
	pLevel = level;
	pUI = ui;
}

void QuataLogic::LogicFunction()
{
	DebugClass::collision_AI_paddle = false;
	DebugClass::collision_player_paddle = false;
	DebugClass::collision_ball = false;

	sf::FloatRect it2 = pLevel->get_Ball_Bounds();

	if (collisionCheck(mData.get_Zone(Qua::z_BottomPlayField), it2))
	{
		collisionResponse(Ball_Top_OR_BottomPlayfield);
		DebugClass::collision_ball = true;
	}
	else if (collisionCheck(mData.get_Zone(Qua::z_UpperPlayField), it2))
	{
		collisionResponse(Ball_Top_OR_BottomPlayfield);
		DebugClass::collision_ball = true;
	}
	else if (collisionCheck(mData.get_Zone(Qua::z_LeftPlayField), it2))
	{
		collisionResponse(Ball_LeftPlayfield);
	}
	else if (collisionCheck(mData.get_Zone(Qua::z_RightPlayField), it2))
	{
		collisionResponse(Ball_RightPlayfield);
	}
	else if (collisionCheck(pPlayer->get_Paddle_Bounds(), it2))
	{
		collisionResponse(Ball_Player_Paddle);
	}
	else if (collisionCheck(pAI->get_Paddle_Bounds(), it2))
	{
		collisionResponse(Ball_AI_Paddle);
	}
}

bool QuataLogic::collisionCheck(const sf::FloatRect& p1, sf::FloatRect& p2)
{
	if (p1.intersects(p2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void QuataLogic::bounceBallFromPaddle_Response(bool is_left_paddle)
{
	if (is_left_paddle)
	{
		pLevel->ball_Paddle_bounce(is_left_paddle, pPlayer->get_Paddle_Bounds());
		mData.Play_Sound(Qua::snd_Player_Ball_bounce);
	}
	else
	{
		pLevel->ball_Paddle_bounce(is_left_paddle, pAI->get_Paddle_Bounds());
		mData.Play_Sound(Qua::snd_Opponent_Ball_bounce);
	}
}

void QuataLogic::bounceBallfromBorderResponse()
{
	mData.Play_Sound(Qua::snd_Wall_Ball_bounce);
	pLevel->ball_Wall_bounce();

}

void QuataLogic::scoreResponse(CollisionType type)
{
	pLevel->reset_ball();
	
	if (type == Ball_LeftPlayfield)
	{
		mData.Play_Sound(Qua::snd_Opponent_Score);
		UINT i = mData.get_Score(Qua::cu_Score2);
		i++;
		mData.set_Score(Qua::cu_Score2, i);
		pUI->change_score(Qua::cu_Score2);
	}
	else if (type == Ball_RightPlayfield)
	{
		mData.Play_Sound(Qua::snd_Player_Score);
		UINT i = mData.get_Score(Qua::cu_Score1);
		i++;
		mData.set_Score(Qua::cu_Score1, i);
		pUI->change_score(Qua::cu_Score1);
	}
	
}

void QuataLogic::collisionResponse(CollisionType type)
{
	if (type == Ball_LeftPlayfield || type == Ball_RightPlayfield)
	{
		scoreResponse(type);
		pLevel->start_cooldown();
	}
	else if (type == Ball_Top_OR_BottomPlayfield)
	{
		bounceBallfromBorderResponse();
	}
	else if (type == Ball_AI_Paddle)
	{
		bounceBallFromPaddle_Response(false);
	}
	else if (type == Ball_Player_Paddle)
	{
		bounceBallFromPaddle_Response(true);
	}
}

void QuataLogic::startBallMovement()
{	
	pLevel->start_ball();
}