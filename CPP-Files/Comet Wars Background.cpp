#include "stdafx.h"
#include "Comet Wars Background.h"
#include "Comet Wars Data.h"

CometWars_Background::CometWars_Background(CometWarsData& data)
{	
	float x = data.getKey_Position(CW::kp_BottomRight).x;
	float y = data.getKey_Position(CW::kp_BottomRight).y;
	mBackground.setSize(sf::Vector2f(x,y));
	mBackground.setFillColor(sf::Color(5, 5, 15, 255));

	mVertices.setPrimitiveType(sf::Points);	
	mVertices.resize(x);
	std::uniform_int_distribution<int>		distributor_X_pos(0, x);
	std::uniform_int_distribution<int>		distributor_Y_pos(0, y);
	std::uniform_int_distribution<int>		distributor_Fade(0, 2);
	std::uniform_int_distribution<int>		distributor_Transparency(64, 255);

	for (UINT i = 0; i < mVertices.getVertexCount(); ++i)
	{
		float x_pos = distributor_X_pos(data.get_random_engine());
		float y_pos = distributor_Y_pos(data.get_random_engine());
		mVertices[i].position = sf::Vector2f(x_pos, y_pos);

		int fade = distributor_Fade(data.get_random_engine());
		FadeStatus status = static_cast<FadeStatus>(fade);
		mStatus.push_back(status);
		if (status == FadeIn || status == FadeOut)
		{
			int alpha = distributor_Transparency(data.get_random_engine());
			mVertices[i].color = sf::Color(255, 255, 255, alpha);
		}
	}
}

void CometWars_Background::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mBackground);
	target.draw(mVertices, state);
}

void CometWars_Background::update(sf::Time& time)
{
	for (UINT i = 0; i < mVertices.getVertexCount(); ++i)
	{
		if (mStatus.at(i) != FadeNone)
		{
			sf::Uint8 r = mVertices[i].color.r;
			sf::Uint8 g = mVertices[i].color.g;
			sf::Uint8 b = mVertices[i].color.b;
			int a = mVertices[i].color.a;
			if (mStatus.at(i) == FadeIn)
			{
				a += 3;
				if (a >= 255)
				{
					a = 255;
					mStatus.at(i) = FadeOut;
				}
			}
			else if (mStatus.at(i) == FadeOut)
			{
				a -= 3;
				if (a <= 64)
				{
					a = 64;
					mStatus.at(i) = FadeIn;
				}
			};
			mVertices[i].color = sf::Color(r, g, b, a);
		}
	}
}
