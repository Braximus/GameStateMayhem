#ifndef BREAKTROUGH_PADDLE_H
#define BREAKTROUGH_PADDLE_H

#include "BreakTrough Game Objects.h"
class BreakTrough_Data;

class BrkTr_Paddle : public BrkTr_Game_Objects
{
	sf::RectangleShape		mPaddle;
	bool					is_being_faded;
public:
	BrkTr_Paddle(BreakTrough_Data& data);
	void			draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void			update(sf::Time& time);

	void			setPosition(sf::Vector2f);
	void			setVelocity(sf::Vector2f);
	void			Change_Paddle(sf::Vector2f size, sf::IntRect tex_rect);

	void			start_Paddle_fading();
	void			fade_Paddle();
	void			reset_Paddle_opacity();

	const bool		is_fading() const;
};






#endif