#include "stdafx.h"
#include "Comet Wars UI Score.h"
#include "Comet Wars Data.h"


CometWars_UI_Score::CometWars_UI_Score(CometWarsData& data)
{
	mStored_txt = data.getText(CW::txt_Score);
	mText.setFont(data.getResources().getFont(ID_Global));
	mText.setCharacterSize(data.getCharacter_Size(CW::ch_Medium));
	mPosition = data.getUI_Position(CW::UI_Score);
	mText.setPosition(mPosition);
	mText.setString(mStored_txt + std::to_string(data.getScore()) );
	mText.setColor(sf::Color::Red);
}

void CometWars_UI_Score::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mText, state);
}

void CometWars_UI_Score::update(sf::Time& time)
{
	//
}

void CometWars_UI_Score::refresh_score(UINT param)
{
	mText.setString(mStored_txt + std::to_string(param));
}
