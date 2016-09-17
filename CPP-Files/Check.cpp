#include "stdafx.h"
#include "Check.h"

Check::Check(const sf::Texture& texture, const std::vector<sf::IntRect>& tex_rects)
{
	mCheck.setTexture(&texture);
	mCheck.setPosition(0, 0);
	mCheck.setSize(sf::Vector2f(10, 10));

	mTexRects.insert(std::pair<TextureAreas, sf::IntRect>(Not_selected, tex_rects.at(0)));
	mTexRects.insert(std::pair<TextureAreas, sf::IntRect>(Selected, tex_rects.at(1)));
	mTexRects.insert(std::pair<TextureAreas, sf::IntRect>(Selected_and_hovered, tex_rects.at(3)));
	mTexRects.insert(std::pair<TextureAreas, sf::IntRect>(Not_selected_but_hovered, tex_rects.at(2)));
	
	mCheck.setTextureRect(mTexRects.at(Not_selected));

	mActivated = false;
}

void Check::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mCheck, state);
}

void Check::set_Position(sf::Vector2f param)
{
	mCheck.setPosition(param);
}

void Check::set_Size(sf::Vector2f param)
{
	mCheck.setSize(param);
	sf::FloatRect b = mCheck.getLocalBounds();
	mCheck.setOrigin(b.width / 2, b.height / 2);
}

void Check::set_Scale(float param)
{
	mCheck.setScale(sf::Vector2f(param, param));
}

const sf::FloatRect Check::get_Bounds() const
{
	sf::FloatRect bound = mCheck.getGlobalBounds();
	return bound;
}

bool Check::onHover(sf::Vector2f param)
{
	if (mCheck.getGlobalBounds().contains(param))
	{
		if (mActivated)
		{
			mCheck.setTextureRect(mTexRects.at(Selected_and_hovered));
		}
		else
		{
			mCheck.setTextureRect(mTexRects.at(Not_selected_but_hovered));
		}
		return true;
	}
	else
	{
		if (mActivated)
		{
			mCheck.setTextureRect(mTexRects.at(Selected));
		}
		else
		{
			mCheck.setTextureRect(mTexRects.at(Not_selected));
		}
		return false;
	}
}

bool Check::onClick()
{
	if (mActivated)
	{
		mActivated = false;
	}
	else
	{
		mActivated = true;
	}
	return mActivated;
}

void Check::initValue(bool param)
{
	mActivated = param;

	if (mActivated)
	{
		mCheck.setTextureRect(mTexRects.at(Selected));
	}
	else
	{
		mCheck.setTextureRect(mTexRects.at(Not_selected));
	}
}
