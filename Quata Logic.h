#ifndef QUATA_LOGIC_H
#define QUATA_LOGIC_H

#include "Quata Objects.h"
#include "Debug.h"
#include "Quata Enumerations.h"

class Quata_Player;
class QuataAI;
class Quata_Level;
class QuataData;
class Quata_UI_Manager;

// Quata Logic klasa služi za detekciju sudara između objekata i daje odgovor na njih!.


class QuataLogic
{
private:
	enum CollisionType
	{
		Ball_Player_Paddle,
		Ball_AI_Paddle,
		Ball_Top_OR_BottomPlayfield,
		Ball_LeftPlayfield,
		Ball_RightPlayfield,
		Paddle_TopPlayfield,
		Paddle_BottomPlayfield
	};

	typedef	std::unique_ptr<QuataObjects>	pPtr;

	Quata_Player*						pPlayer;
	QuataAI*							pAI;
	Quata_Level*						pLevel;
	Quata_UI_Manager*					pUI;
	//--------------------------------//
	QuataData&							mData;
	CollisionType						mType;
	//--------------------------------//

	//--------------------------------//
	//	Da klasa moze da prikupi par stvarcica...
	sf::FloatRect						Paddle_Bounds;
	float								PaddleY_pos_offset;
	//--------------------------------//

	void				bounceBallFromPaddle_Response(bool);
	void				bounceBallfromBorderResponse();
	void				scoreResponse(CollisionType type);

public:
	explicit			QuataLogic(QuataData&);
	bool				collisionCheck( const sf::FloatRect& p1, sf::FloatRect& p2);
	void				collisionResponse(CollisionType);

	void				get_pointers(Quata_Player* player, QuataAI* AI, Quata_Level* ball, Quata_UI_Manager* ui);

	void				startBallMovement();

	void				LogicFunction();
	


};



#endif
