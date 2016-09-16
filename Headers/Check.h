#ifndef CHECK_H
#define CHECK_H

class Check : public sf::Drawable, public sf::Transformable
{
	enum TextureAreas
	{
		Not_selected,
		Selected,
		Selected_and_hovered,
		Not_selected_but_hovered,

	};
	std::map<TextureAreas,sf::IntRect>	mTexRects;
	sf::RectangleShape			mCheck;
	bool					mActivated;
public:
	Check() {};
	Check(const sf::Texture& texture, const std::vector<sf::IntRect>& tex_rects);
	void			draw(sf::RenderTarget& target, sf::RenderStates state) const;

	void			set_Size(sf::Vector2f);
	void			set_Scale(float);
	void			set_Position(sf::Vector2f);


	bool			onHover(sf::Vector2f);
	bool			onClick();

	void			initValue(bool);
	const sf::FloatRect		get_Bounds() const;

};



#endif
