#include "stdafx.h"
#include "Debug.h"
#include "DataStorage.h"

std::vector<sf::Vector2i>	DebugClass::nums;
std::vector<int>			DebugClass::numbers;
sf::FloatRect DebugClass::coll1 = sf::FloatRect(0, 0, 0, 0);

float DebugClass::angle = 0;
float DebugClass::speed = 0;

bool		DebugClass::collision_ball = false;
bool		DebugClass::collision_player_paddle = false;
bool		DebugClass::collision_AI_paddle = false;

bool		DebugClass::top = false;
bool		DebugClass::left = false;
bool		DebugClass::right = false;
bool		DebugClass::bottom = false;


DebugClass::DebugClass(Data& data)
	:mData(data)
{
	nums.reserve(100);
	for (UINT i = 0; i <= 100; ++i)
	{
		nums.push_back(sf::Vector2i(0, 0));
	}
	for (UINT i = 0; i < 3; ++i)
	{
		numbers.push_back(0);
	}

	mFont.loadFromFile("Font/OpenSans-Regular.ttf");
	mFPS.setFont(mFont);
	mFPS.setCharacterSize(12);
	mFPS.setColor(sf::Color::White);
	mFPS.setPosition(1, 0);
	iFPS = 0;

	mTekst.setFont(mFont);
	mTekst.setCharacterSize(12);
	mTekst.setColor(sf::Color::White);
	mTekst.setPosition(1, 50);
}

void DebugClass::DebugText(sf::Time ElapsedTime)
{
	FPS_Time += ElapsedTime;
	iFPS++;
	if (FPS_Time >= sf::seconds(1.0f))
	{
		mFPS.setString("FPS: " + std::to_string(iFPS) + "\n" +
			"Resolution: " + std::to_string(mData.getVideo_Mode().width) + "x" + std::to_string(mData.getVideo_Mode().height) + "\n" +  
			"AA: " + std::to_string(mData.get_Current_AA_Level()));
		FPS_Time -= sf::seconds(1.0f);
		iFPS = 0;

	}

	/*mTekst.setString("Pozicija misa: \nX:  " + std::to_string(mData.mMouseCoordinates.x) + "\n" +
		"Y:  " + std::to_string(mData.mMouseCoordinates.y));*/

	if (mData.getStateID() == eState::e_Menu /*|| mData.getStateID() == eState::e_GameChoice || mData.getStateID() == eState::e_Options*/)
	{
		mTekst.setString("Mouse Position: \nX:  " + std::to_string(mData.mMouseCoordinates.x) + "\n" +
			"Y:  " + std::to_string(mData.mMouseCoordinates.y));
	}
	else if (mData.getStateID() == eState::e_Quata)
	{
		std::string ball, aipaddle, plpaddle;
		if (collision_ball)
			ball = "true";
		else
			ball = "false";
		if (collision_AI_paddle)
			aipaddle = "true";
		else
			aipaddle = "false";
		if (collision_player_paddle)
			plpaddle = "true";
		else
			plpaddle = "false";

		mTekst.setString("Mouse Position: \nX:  " + std::to_string(mData.mMouseCoordinates.x) + "\n" +
			"Y:  " + std::to_string(mData.mMouseCoordinates.y) + "\n" + "\n" +
			"Paddle 1\t " + "X: " + std::to_string(nums[0].x) + "\tY: " + std::to_string(nums[0].y) + "\n" +
			"Paddle 2\t " + "X: " + std::to_string(nums[1].x) + "\tY: " + std::to_string(nums[1].y) + "\n" +
			"Ball\t\t\t   " + "X: " + std::to_string(nums[2].x) + "\tY: " + std::to_string(nums[2].y) + "\n" +
			"Coll Ball:\t " + ball + "\n" +
			"Coll AIp:\t " + aipaddle + "\n" +
			"Coll Plp:\t " + plpaddle + "\n" 
			"Ball Speed:\t" + std::to_string(speed) + "\n" +
			"Ball Angle:\t" + std::to_string(angle) + "\n"/*
			"Collision Area: " + "\n" + "Top:" + std::to_string(coll1.top) + " " + "Left: " + std::to_string(coll1.left) +
			" " + "Width: " + std::to_string(coll1.width) + " " + "Height: " + std::to_string(coll1.height)*/);

	}

	else if (mData.getStateID() == eState::e_CometWars)
	{
		std::string t, l, r, b;
		if (top)
			t = "true";
		else
			t = "false";
		if (left)
			l = "true";
		else
			l = "false";
		if (right)
			r = "true";
		else
			r = "false";
		if (bottom)
			b = "true";
		else
			b = "false";

		mTekst.setString("Mouse Position: \nX:  " + std::to_string(mData.mMouseCoordinates.x) + "\n" +
			"Y:  " + std::to_string(mData.mMouseCoordinates.y) + "\n" +
			"Top_Border:\t\t" + t + "\n" +
			"Left_Border:\t\t" + l + "\n" +
			"Right_Border:\t\t" + r + "\n" +
			"Bottom_Border:\t\t" + b +"\n" +
			"Ship:\t\t " + std::to_string(nums[0].x) + ", " + std::to_string(nums[0].y) +  "\n" + 
			"Border: \t\tLeft: " + std::to_string(coll1.left) + " Top: " + std::to_string(coll1.top) +" Width: " + std::to_string(coll1.width) +" Height: " + std::to_string(coll1.height)
			+ "\n\n" +
			"Comet Number: \t\t\t\t" + std::to_string(numbers[0]) + "\n" +
			"Mini Comet Number: \t\t" + std::to_string(numbers[1]) + "\n" +
			"Projectile Number: \t\t" + std::to_string(numbers[2]) + "\n"
			//	+	"\n\n"  +
			//"Asteroid_1:\t\t " + std::to_string(nums[1].x) + ", " + std::to_string(nums[1].y) + "\n" +
			//"Asteroid_2:\t\t " + std::to_string(nums[2].x) + ", " + std::to_string(nums[2].y) + "\n" +
			//"Asteroid_3:\t\t " + std::to_string(nums[3].x) + ", " + std::to_string(nums[3].y) + "\n" +
			//"Asteroid_4:\t\t " + std::to_string(nums[4].x) + ", " + std::to_string(nums[4].y) + "\n" +
			//"Asteroid_5:\t\t " + std::to_string(nums[5].x) + ", " + std::to_string(nums[5].y) + "\n" +
			//"Asteroid_6:\t\t " + std::to_string(nums[6].x) + ", " + std::to_string(nums[6].y) + "\n" +
			//"Asteroid_7:\t\t " + std::to_string(nums[7].x) + ", " + std::to_string(nums[7].y) + "\n" +
			//"Asteroid_8:\t\t " + std::to_string(nums[8].x) + ", " + std::to_string(nums[8].y) + "\n" +
			//"Asteroid_9:\t\t " + std::to_string(nums[9].x) + ", " + std::to_string(nums[9].y)
			);
		/*+"\n" +*/

	}
	else if (mData.getStateID() == eState::e_BreakTrough)
	{
		mTekst.setString("Mouse Position: \nX:  " + std::to_string(mData.mMouseCoordinates.x) + "\n" +
			"Y:  " + std::to_string(mData.mMouseCoordinates.y)
			//+ "\n" + "Paddle Position: " + std::to_string(nums[0].x) + ", " + std::to_string(nums[0].y)
			//+ "\n" + "Ball 1 Position: " + std::to_string(nums[1].x) + ", " + std::to_string(nums[1].y) 
			//+ "\n" + "Ball 2 Position: " + std::to_string(nums[2].x) + ", " + std::to_string(nums[2].y)
			//+ "\n" + "Ball 3 Position: " + std::to_string(nums[3].x) + ", " + std::to_string(nums[3].y)
			//
			
			);

	}

}

sf::Text DebugClass::drawFPS()
{
	return mFPS;
}

sf::Text DebugClass::drawTxt()
{
	return mTekst;
}

