#ifndef COMETWARS_UI_LIVES_H
#define COMETWARS_UI_LIVES_H

#include "Comet Wars UI Objects.h"
class CometWarsData;

class CometWars_UI_Lives : public CometWars_UI_Objects
{
	std::deque<sf::RectangleShape>		mLives;			//	Deque gives me an option to "pop_front"
	sf::RectangleShape			mStored_rect;
	float					lives_offset;
	bool					is_life_removed;
public:
	explicit		CometWars_UI_Lives(CometWarsData&);

	void			draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void			update(sf::Time&);
	void			delete_life();
	void			reset(UINT);
};
#endif
