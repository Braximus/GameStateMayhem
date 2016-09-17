#include "stdafx.h"
#include "Comet Wars UI Lives.h"
#include "Comet Wars Data.h"

CometWars_UI_Lives::CometWars_UI_Lives(CometWarsData& data)
{
	mStored_rect.setTexture(&data.getResources().getTexture(ID_CometWars));
	mStored_rect.setSize(data.getObj_Sizes(CW::size_Ship));
	mStored_rect.setTextureRect(data.getMisc_Texture_rect(CW::msc_Battery)); 

	is_life_removed = false;
	mPosition = data.getUI_Position(CW::UI_Lives);
	lives_offset = 2 * data.getScale_Coefficient();

	UINT mLifeCheck = data.getNumber_of_Lives();	
	for (int i = 0; i < mLifeCheck; ++i)
	{
		mStored_rect.setPosition(mPosition.x - i * (data.getObj_Sizes(CW::size_Ship).x + lives_offset), mPosition.y + lives_offset);
		mLives.push_back(mStored_rect);
	}	
}

void CometWars_UI_Lives::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	for (const auto& it : mLives)
	{
		target.draw(it, state);
	}
}

void CometWars_UI_Lives::update(sf::Time& time)
{
	if (is_life_removed)
	{
		if (!mLives.empty())
		{
			mLives.pop_back();
		}
		is_life_removed = false;
	}
}

void CometWars_UI_Lives::delete_life()
{
	is_life_removed = true;
}

void CometWars_UI_Lives::reset(UINT param)
{
	for (UINT i = 0; i < param; ++i)
	{
		mStored_rect.setPosition(mPosition.x - i * (mStored_rect.getSize().x + lives_offset), mPosition.y + lives_offset);
		mLives.push_back(mStored_rect);
	}
}

