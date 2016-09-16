#ifndef LABEL_H
#define LABEL_H

class Label : public sf::Drawable, public sf::Transformable
{
	sf::Text			mLabel;
	sf::RectangleShape		mOutline;
	sf::Vector2f			mOffset;
	sf::Color			mDefault_Text_Color, mDefault_Outline_Color, mDimmed_color;
public:
	Label(){};
	Label(const sf::Font& font, std::string text, float char_size);
	void			draw(sf::RenderTarget& target, sf::RenderStates state) const;

	void			set_Position(sf::Vector2f);
	void			set_Size(sf::Vector2f);
	void			set_Scale(float);
	void			set_Availability(bool);

	const std::string			get_Text() const;
	void						set_Text(std::string new_text);
	const sf::FloatRect			get_Bounds() const;

	void			set_Color(sf::Color Text_color, sf::Color Outline_color, sf::Color mDimmed_color = sf::Color(32,32,32,255));

};


#endif
