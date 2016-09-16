#ifndef DROP_DOWN_MENU_H
#define DROP_DOWN_MENU_H

#include "Buttons.h"
#include "Label.h"


class DropDownMenu : public sf::Drawable, public sf::Transformable
{
	bool						mCurrentState;
	Label						mCurrentSelection;
	Button						mActivation_Button, mScrollDown_Button, mScrollUp_Button;
	std::vector<Button>				mChoices;
	std::vector<std::string>			mChoicesNames;
	sf::RectangleShape				mChoicesOutline;
	sf::FloatRect					mBound_Of_DropDownMenu;
	UINT						mNumber_Of_ShownChoices, mBegining_Number;
	float						mOutline_size;
	UINT						mValue;

	void						Activate();

public:
	DropDownMenu() {};
	explicit	DropDownMenu(const sf::Font& font, const sf::Texture& tex, float char_size, sf::IntRect tex_rect, sf::Vector2f size, sf::Vector2f position, std::vector<std::string> container_of_names);

	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void					choose(sf::Vector2f param);
	void					release();
	void					force_close();
	bool					hover(sf::Vector2f param);
	void					change_Label(UINT);
	const sf::FloatRect		get_Bounds();
	const UINT				return_value() const;
	

};



#endif
