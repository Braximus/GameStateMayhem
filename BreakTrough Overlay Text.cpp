#include "stdafx.h"
#include "BreakTrough Overlay Text.h"
#include "BreakTrough Data.h"


BrkTr_Overlay::BrkTr_Overlay(BreakTrough_Data& data)
{
	mOverlay_box.setFillColor(sf::Color(64, 55, 0, 255));
	mOverlay_box.setSize(data.get_Component_Sizes(Break::size_Overlay));		
	mOverlay_box.setOutlineThickness(-1);
	mOverlay_box.setOutlineColor(sf::Color(204, 175, 0, 255));
	mOverlay_box.setPosition(data.get_Key_Position(Break::kp_Center));
	sf::FloatRect Bounds = mOverlay_box.getLocalBounds();
	mOverlay_box.setOrigin(Bounds.width / 2, Bounds.height / 2);
	Bounds = mOverlay_box.getGlobalBounds();

	mOverlay_text1.setFont(data.get_Resources().getFont(ID_Global));
	mOverlay_text1.setCharacterSize(data.get_Character_Sizes(Break::ch_Large));
	mOverlay_text1.setString(data.get_Text(Break::txt_Mission_Start));
	mOverlay_text1.setColor(sf::Color(204, 175, 0, 255));
	sf::FloatRect Bounds2 = mOverlay_text1.getLocalBounds();
	mOverlay_text1.setOrigin(Bounds2.width / 2, Bounds2.top + Bounds2.height / 2);
	mOverlay_text1.setPosition(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 4);

	mOverlay_text2.setFont(data.get_Resources().getFont(ID_Global));
	mOverlay_text2.setCharacterSize(data.get_Character_Sizes(Break::ch_Large));
	mOverlay_text2.setString(std::to_string(data.get_Object_Quantities(Break::Current_Level)));	//	Ovde treba da stavom broj nivoa iz datoteke
	mOverlay_text2.setColor(sf::Color(204, 175, 0, 255));
	Bounds2 = mOverlay_text2.getLocalBounds();
	mOverlay_text2.setOrigin(Bounds2.width / 2, Bounds2.top + Bounds2.height / 2);
	mOverlay_text2.setPosition(Bounds.left + Bounds.width / 2, Bounds.top + 2 * Bounds.height / 3);
}

void BrkTr_Overlay::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mOverlay_box, state);
	target.draw(mOverlay_text1, state);
	target.draw(mOverlay_text2, state);
}

//	Funkcija za tekst koji se pojavljuje na pocetku svake misije i posto igrac izgubi zivot.
void BrkTr_Overlay::update_text(std::string& txt)
{
	mOverlay_text2.setString(txt);
	sf::FloatRect Bounds = mOverlay_text2.getLocalBounds();
	mOverlay_text2.setOrigin(Bounds.width / 2, Bounds.top + Bounds.height / 2);
}

//	Funkcija za tekst koji se prikazuje na kraju igre.
void BrkTr_Overlay::game_over_text(std::string& txt)
{
	mOverlay_box.setSize(sf::Vector2f(3.0f*mOverlay_box.getSize().x / 2.0f, mOverlay_box.getSize().y));
	sf::FloatRect Bounds = mOverlay_box.getLocalBounds();
	mOverlay_box.setOrigin(Bounds.width / 2, Bounds.height / 2);

	mOverlay_text2.setString("");	// nista
	Bounds = mOverlay_box.getGlobalBounds();

	mOverlay_text1.setString(txt);
	sf::FloatRect Bounds2 = mOverlay_text1.getLocalBounds();
	mOverlay_text1.setOrigin(Bounds2.width / 2, Bounds2.top + Bounds2.height / 2);
	mOverlay_text1.setPosition(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2);
}