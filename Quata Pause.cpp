#include "stdafx.h"
#include "Quata Pause.h"
#include "Quata Data.h"

//	U potpunosti isto kao i BreakTrough pauza.

Quata_Pause::Quata_Pause(QuataData& data)
{
	sf::Vector2f center = data.get_Key_Position(Qua::kp_Center_Screen);
	sf::Vector2f button_size = data.get_Object_Size(Qua::size_Button);
	float distance = data.get_Distance(Qua::dis_Near);
	float char_size = data.get_Character_Size(Qua::ch_Medium);
	const sf::Font& font = data.get_Resources().getFont(ID_Global);

	mScreen_Fill.setFillColor(sf::Color(0, 0, 0, 128));
	mScreen_Fill.setSize(data.get_Key_Position(Qua::kp_BottomRight_Corner));

	mPause_Area.setFillColor(sf::Color(140, 0, 0, 64));
	mPause_Area.setOutlineColor(sf::Color::Red);
	mPause_Area.setOutlineThickness(3);
	mPause_Area.setSize(data.get_Object_Size(Qua::size_Pause_Area));
	sf::FloatRect bounds = mPause_Area.getLocalBounds();
	mPause_Area.setOrigin(bounds.width / 2, bounds.height / 2);
	mPause_Area.setPosition(center);

	Button		button1(data.get_Text(Qua::txt_New_button), font, char_size);
	Button		button2(data.get_Text(Qua::txt_Continue_button), font, char_size);
	Button		button3(data.get_Text(Qua::txt_Exit_button), font, char_size);

	button1.set_Size(button_size);
	button2.set_Size(button_size);
	button3.set_Size(button_size);

	button1.set_Position(sf::Vector2f(center.x, center.y - button_size.y / 2 - distance));
	button2.set_Position(sf::Vector2f(center.x, center.y));
	button3.set_Position(sf::Vector2f(center.x, center.y + button_size.y / 2 + distance));
	
	button1.set_Bounds();
	button2.set_Bounds();
	button3.set_Bounds();

	button1.set_Colors(sf::Color(140, 0, 0, 128), sf::Color::Red);
	button2.set_Colors(sf::Color(140, 0, 0, 128), sf::Color::Red);
	button3.set_Colors(sf::Color(140, 0, 0, 128), sf::Color::Red);

	mButtons.insert(std::pair<Qua::Button_Selection, Button>(Qua::New, button1));
	mButtons.insert(std::pair<Qua::Button_Selection, Button>(Qua::Continue, button2));
	mButtons.insert(std::pair<Qua::Button_Selection, Button>(Qua::Exit, button3));
	
	hover = false;
}

void Quata_Pause::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mScreen_Fill);
	target.draw(mPause_Area);
	for (const auto& it : mButtons)
	{
		target.draw(it.second);
	}
}

void Quata_Pause::interact(sf::Vector2f mouse_pos)
{
	bool mouse_is_outside = true;
	for (auto& it : mButtons)
	{
		//	Proveravam da li granica dugmeta sadrzi mis (tj. param):
		if (it.second.check_Bounds(mouse_pos))
		{
			//	Ako sadrzi, onda neka trentuna selekcija bude selekcija kljuca doticnog dugmeta i da se promeni boja dugmeta
			mouse_is_outside = false;
			mCurrentSelection = it.first;
			it.second.ToggleSelection_ByColor(true);
		}
		else
		{
			it.second.ToggleSelection_ByColor(false);
		}
	}
	//	Dokle god je trenutna selekcija ista kao i prethodna selekcija, nema potrebe da se konstanto osvezava.
	if (mCurrentSelection != mPreviousSelection)
	{
		if (mCurrentSelection != Qua::None)
		{
			hover = true;
		}
		else
		{
			hover = false;
		}
		mPreviousSelection = mCurrentSelection;
	}

	//	Ako je mis van svakog dugmeta, onda je nema selekcije.
	if (mouse_is_outside)
	{
		mCurrentSelection = Qua::None;
	}
}

const bool Quata_Pause::is_hovering() const
{
	return hover;
}

const Qua::Button_Selection Quata_Pause::response() const
{
	return mCurrentSelection;
}