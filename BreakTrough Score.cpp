#include "stdafx.h"
#include "BreakTrough Score.h"
#include "BreakTrough Data.h"

BrkTr_UI_Score::BrkTr_UI_Score(BreakTrough_Data& data)
{
	mStored_txt = data.get_Text(Break::txt_Score);
	mScore.setColor(sf::Color::Yellow);
	mScore.setFont(data.get_Resources().getFont(ID_Global));
	mScore.setString(mStored_txt + std::to_string(data.get_Object_Quantities(Break::Score_Number)));
	mScore.setCharacterSize(data.get_Character_Sizes(Break::ch_Medium));
	mScore.setPosition(data.get_UI_Components_Positions(Break::cUI_Score));

	sf::FloatRect	bounds = mScore.getGlobalBounds();
	float			med = data.get_Distances(Break::dis_Medium);
	float			Near = data.get_Distances(Break::dis_Near);

	mBackground.setFillColor(sf::Color(32, 32, 32, 255));
	mBackground.setOutlineColor(sf::Color::Yellow);
	mBackground.setOutlineThickness(-1);
	mBackground.setSize(sf::Vector2f(bounds.width + 3*med, bounds.height + 2*med));
	mBackground.setPosition(bounds.left - med, bounds.top -med);
}

void BrkTr_UI_Score::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mBackground, state);
	target.draw(mScore, state);
}

void BrkTr_UI_Score::update_text(std::string& txt)
{
	mScore.setString(mStored_txt + txt);
}