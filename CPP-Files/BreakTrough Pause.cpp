#include "stdafx.h"
#include "BreakTrough Pause.h"
#include "BreakTrough Data.h"

BreakTrough_Pause::BreakTrough_Pause(BreakTrough_Data& data)
{
	mScreen_Fill.setFillColor(sf::Color(0, 0, 0, 128));
	mScreen_Fill.setSize(data.get_Key_Position(Break::kp_BottomRight));

	mPause_Area.setFillColor(sf::Color(128, 110, 0, 64));
	mPause_Area.setOutlineColor(sf::Color(204, 175, 0, 255));
	mPause_Area.setOutlineThickness(3);
	mPause_Area.setSize(data.get_Component_Sizes(Break::size_Pause_Area));	

	sf::FloatRect bounds = mPause_Area.getLocalBounds();
	mPause_Area.setOrigin(bounds.width / 2, bounds.height / 2);
	mPause_Area.setPosition(data.get_Key_Position(Break::kp_Center));

	Button		button1(data.get_Text(Break::txt_pau_Continue), data.get_Resources().getFont(ID_Global), data.get_Character_Sizes(Break::ch_Medium));
	Button		button2(data.get_Text(Break::txt_pau_Exit), data.get_Resources().getFont(ID_Global), data.get_Character_Sizes(Break::ch_Medium));

	button1.set_Size(sf::Vector2f(data.get_Component_Sizes(Break::size_Pause_Button)));
	button2.set_Size(sf::Vector2f(data.get_Component_Sizes(Break::size_Pause_Button)));

	button1.set_Position(sf::Vector2f(data.get_Key_Position(Break::kp_Center).x, data.get_Key_Position(Break::kp_Center).y - data.get_Component_Sizes(Break::size_Pause_Button).y/2 - data.get_Distances(Break::dis_Near)));
	button2.set_Position(sf::Vector2f(data.get_Key_Position(Break::kp_Center).x, data.get_Key_Position(Break::kp_Center).y + data.get_Component_Sizes(Break::size_Pause_Button).y/2 + data.get_Distances(Break::dis_Near)));

	button1.set_Bounds();
	button2.set_Bounds();

	button1.set_Colors(sf::Color(90, 64, 0, 255), sf::Color(204, 175, 0, 255));
	button2.set_Colors(sf::Color(90, 64, 0, 255), sf::Color(204, 175, 0, 255));

	mButtons.insert(std::pair<Break::Button_Selection, Button>(Break::Continue, button1));
	mButtons.insert(std::pair<Break::Button_Selection, Button>(Break::Exit, button2));

	hover = false;
}

void BreakTrough_Pause::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mScreen_Fill, state);
	target.draw(mPause_Area, state);
	for (const auto& it : mButtons)
	{
		target.draw(it.second, state);
	}
}

void BreakTrough_Pause::interact(sf::Vector2f param)
{
	bool mouse_is_outside = true;
	for (auto& it : mButtons)
	{
		if (it.second.check_Bounds(param))
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
	//	As long as the current selection is the same as the previous one, there is no need to refresh it.
	if (mCurrentSelection != mPreviousSelection)
	{
		if (mCurrentSelection != Break::None)
		{
			hover = true;
		}
		else
		{
			hover = false;
		}
		mPreviousSelection = mCurrentSelection;
	}

	//	If mouse is outside of the any button area, then there is no selection.
	if (mouse_is_outside)
	{
		mCurrentSelection = Break::None;
	}
}

const Break::Button_Selection BreakTrough_Pause::response() const
{
	return mCurrentSelection;
}

const bool BreakTrough_Pause::is_hovering() const
{
	return hover;
}
