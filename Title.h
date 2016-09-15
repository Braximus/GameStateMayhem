#ifndef TITLE_H
#define TITLE_H

class Title : public sf::Drawable, public sf::Transformable
{
	sf::RectangleShape			mTitle;
public:
	Title(){};
	Title(const sf::Texture& teks, sf::IntRect texture_rect, sf::Vector2f size, sf::Vector2f position);
	void	draw(sf::RenderTarget& target, sf::RenderStates state) const;

	const sf::FloatRect			get_Borders() const;
	const sf::Vector2f			get_Position() const; 
};


#endif