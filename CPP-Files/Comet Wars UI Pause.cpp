#include "stdafx.h"
#include "Comet Wars UI Pause.h"
#include "Comet Wars Data.h"

CometWars_UI_Pause::CometWars_UI_Pause(CometWarsData& data)
{
	const sf::Font& font = data.getResources().getFont(ID_Global);
	float ch_size = data.getCharacter_Size(CW::ch_Medium);
	sf::Vector2f kp = data.getKey_Position(CW::kp_Center);
	sf::Vector2f button_size = data.getObj_Sizes(CW::size_Pause_Button);
	
	mScreen_Fill.setFillColor(sf::Color(0, 0, 0, 128));
	mScreen_Fill.setSize(data.getKey_Position(CW::kp_BottomRight));

	mPause_Area.setFillColor(sf::Color(32, 128, 128, 32));
	mPause_Area.setOutlineColor(sf::Color::Cyan);
	mPause_Area.setOutlineThickness(1);
	mPause_Area.setSize(data.getObj_Sizes(CW::size_Pause_Area));

	sf::FloatRect bounds = mPause_Area.getLocalBounds();
	mPause_Area.setOrigin(bounds.width / 2, bounds.height / 2);
	mPause_Area.setPosition(kp);

	Button		button1(data.getText(CW::txt_Continue_Button), font, ch_size);
	Button		button2(data.getText(CW::txt_NewGame_Button), font, ch_size);
	Button		button3(data.getText(CW::txt_Exit_Button), font, ch_size);

	button1.set_Size(sf::Vector2f(button_size));
	button2.set_Size(sf::Vector2f(button_size));
	button3.set_Size(sf::Vector2f(button_size));

	button1.set_Colors(sf::Color(32, 128, 128, 128), sf::Color::Cyan);
	button2.set_Colors(sf::Color(32, 128, 128, 128), sf::Color::Cyan);
	button3.set_Colors(sf::Color(32, 128, 128, 128), sf::Color::Cyan);

	button1.set_Position(sf::Vector2f(kp.x, kp.y - button_size.y - data.getDistance(CW::dis_Near)));
	button2.set_Position(sf::Vector2f(kp.x, kp.y));
	button3.set_Position(sf::Vector2f(kp.x, kp.y + button_size.y + data.getDistance(CW::dis_Near)));

	button1.set_Text_Position(Button::Text_pos::pos_Center);
	button2.set_Text_Position(Button::Text_pos::pos_Center);
	button3.set_Text_Position(Button::Text_pos::pos_Center);

	button1.set_Bounds();
	button2.set_Bounds();
	button3.set_Bounds();

	mButtons.insert(std::pair<CW::Button_Selection, Button>(CW::bt_Continue, button1));
	mButtons.insert(std::pair<CW::Button_Selection, Button>(CW::bt_New, button2));
	mButtons.insert(std::pair<CW::Button_Selection, Button>(CW::bt_Exit, button3));

	hover = false;
}

void CometWars_UI_Pause::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mScreen_Fill);
	target.draw(mPause_Area);
	for (const auto& it : mButtons)
	{
		target.draw(it.second);
	}
}

void CometWars_UI_Pause::update(sf::Time&)
{
	//
}

void CometWars_UI_Pause::interact(sf::Vector2f mouse_pos)
{
	bool mouse_is_outside = true;
	for (auto& it : mButtons)
	{
		if (it.second.check_Bounds(mouse_pos))
		{
			mouse_is_outside = false;
			mCurrentSelection = it.first;
			it.second.ToggleSelection_ByColor(true);
		}
		else
		{
			it.second.ToggleSelection_ByColor(false);
		}
	}
	if (mCurrentSelection != mPreviousSelection)
	{
		if (mCurrentSelection != CW::bt_None)
		{
			hover = true;
		}
		else
		{
			hover = false;
		}
		mPreviousSelection = mCurrentSelection;
	}

	if (mouse_is_outside)
	{
		mCurrentSelection = CW::bt_None;
	}
}


const bool CometWars_UI_Pause::is_hovering() const
{
	return hover;
}

const CW::Button_Selection CometWars_UI_Pause::response() const
{
	return mCurrentSelection;
}
