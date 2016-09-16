#include "stdafx.h"
#include "BreakTrough Paddle.h"
#include "BreakTrough Data.h"

BrkTr_Paddle::BrkTr_Paddle(BreakTrough_Data& data)
{	
	marked_for_deletion = false;
	is_being_faded = false;

	mPaddle.setTexture(&data.get_Resources().getTexture(ID_BreakTrough));
	mPaddle.setTextureRect(data.get_TextureRect(Break::Paddle_Default));
	mPaddle.setSize(data.get_Component_Sizes(Break::size_Paddle_Default));
	mPaddle.setPosition(data.get_Components_Positions(Break::c_Paddle));
	sf::FloatRect b = mPaddle.getLocalBounds();
	mPaddle.setOrigin(b.width / 2, b.height / 2);

	m_Position = mPaddle.getPosition();
	m_Bounds = mPaddle.getGlobalBounds();
}

void BrkTr_Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mPaddle, state);
}

void BrkTr_Paddle::update(sf::Time& time)
{
	mPaddle.move(m_Velocity);	//	Yes. Without multiplying with time.
	m_Position = mPaddle.getPosition();
	m_Bounds = mPaddle.getGlobalBounds();
}

void BrkTr_Paddle::setPosition(sf::Vector2f param)
{
	m_Position = sf::Vector2f(param.x, mPaddle.getPosition().y);
	mPaddle.setPosition(m_Position);
	m_Bounds = mPaddle.getGlobalBounds();
}

void BrkTr_Paddle::setVelocity(sf::Vector2f param)
{
	m_Velocity = param;
}

void BrkTr_Paddle::Change_Paddle(sf::Vector2f size, sf::IntRect tex_rect)
{
	mPaddle.setSize(size);
	mPaddle.setTextureRect(tex_rect);
	sf::FloatRect b = mPaddle.getLocalBounds();
	mPaddle.setOrigin(b.width / 2, b.height / 2);
}

void BrkTr_Paddle::start_Paddle_fading()
{
	is_being_faded = true;
}

void BrkTr_Paddle::fade_Paddle()
{
	float transparency = mPaddle.getFillColor().a;
	transparency -= 3;
	if (transparency <= 0)
	{
		transparency = 0;
		is_being_faded = false;
	}
	sf::Color new_color = mPaddle.getFillColor();
	new_color.a = static_cast<sf::Uint8>(transparency);
	mPaddle.setFillColor(new_color);
}

void BrkTr_Paddle::reset_Paddle_opacity()
{
	sf::Uint8 transparency = 255;
	sf::Color new_color = mPaddle.getFillColor();
	new_color.a = transparency;
	mPaddle.setFillColor(new_color);
}

const bool BrkTr_Paddle::is_fading() const
{
	return is_being_faded;
}
