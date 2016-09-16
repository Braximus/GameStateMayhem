#ifndef QUATA_AI_H
#define QUATA_AI_H

#include "Quata Paddle.h"

//	Currently, the AI will only follow the ball;
class QuataData;

class QuataAI
{
	QuataData&		mData;
	Quata_Paddle			mPaddle;
public:
	QuataAI(QuataData&);
	Quata_Paddle*		pass_pointer();
	void		update(sf::Time&);

	void		move_Paddle(const sf::Vector2f&, bool, bool);
	void		reset_Paddle_Position();

	const sf::FloatRect	get_Paddle_Bounds() const;
	const sf::Vector2f	get_Paddle_Position() const;
};



#endif
