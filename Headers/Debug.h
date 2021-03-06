#ifndef DEBUG_H
#define DEBUG_H

class Data;

class DebugClass
{
	sf::Font					mFont;
	sf::Time					FPS_Time;
	sf::Text					mFPS, mText;
	unsigned int				iFPS;

	Data&						mData;

public:
	DebugClass(Data&);
	void						DebugText(sf::Time);
	sf::Text					drawFPS();
	sf::Text					drawTxt();
	// 	For Quata
	static	sf::FloatRect			coll1;
	static	std::vector<sf::Vector2i>	nums;
	static	std::vector<int>		numbers;
	static	float				angle, speed;
	static	bool				collision_ball, collision_player_paddle, collision_AI_paddle;
	//	For Comet Wars
	static	bool				top, left, right, bottom;

};

#endif
