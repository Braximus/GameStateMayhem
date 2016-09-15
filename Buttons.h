#ifndef BUTTONS_H
#define BUTTONS_H

class Data;

class Button: public sf::Drawable, sf::Transformable
{
public:
	enum Text_pos
	{
		pos_Center,
		pos_Left,
		pos_Right
	};
private:
	sf::FloatRect			mBounds;
	sf::Text				mText;
	sf::RectangleShape		mSelection;
	sf::IntRect				mStandard_tex_rect;
	sf::Color				mDefault_Selection_Color;
	sf::Color				mDefault_Text_Color;
	sf::Color				mDimmed_Color;
	bool					misSelected;
	Text_pos				mDefault_Text_position;
public:
	Button() {};
	//		Konstruktori ce stavljati podrazumevane vrednosti...
	explicit				Button(std::string button_name, const sf::Font& font, float char_size);
	explicit				Button(const sf::Texture& texture, sf::IntRect tex_rect);
	~Button() {};
	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//		Funkcije za pravljenje dugmeta.
	void					insert_Scale(float);
	void					set_Bounds();
	void					set_Colors(sf::Color selection, sf::Color text, sf::Color dimmed = sf::Color(32,32,32,255));
	void					set_Size(sf::Vector2f);	
	void					set_Position(sf::Vector2f);
	void					set_Text_Position(Text_pos);

	void					ToggleSelection_ByColor(bool);
	void					ToggleSelection_ByTexRect(bool);
	const bool				check_Bounds(sf::Vector2f) const;
	void					toggle_DimText(bool);
	const sf::FloatRect		get_Bounds() const;

	void					change_Texture_rect(sf::IntRect);
	void					change_Button_name(std::string);
	const std::string		getButton_name() const;

};



#endif