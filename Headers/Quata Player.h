#ifndef QUATA_PLAYER_H
#define QUATA_PLAYER_H

#include "Quata Data.h"
#include "Quata Paddle.h"

class Quata_Player
{
	QuataData&			mData;
	Quata_Paddle				mPaddle;
public:
	Quata_Player(QuataData&);
	Quata_Paddle*				pass_pointer();
	void				update(sf::Time&);

	void				move_Paddle(bool );
	void				reset_Paddle_position();

	const sf::FloatRect		get_Paddle_Bounds() const;	
	const sf::Vector2f		get_Paddle_Position() const;

};

#endif
