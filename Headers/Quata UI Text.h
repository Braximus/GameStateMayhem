#ifndef QUATA_UI_TEXT_H
#define QUATA_UI_TEXT_H


#include "Quata UI Objects.h"
class QuataData;

//	This class will pull a double duty as a label and as a score.

class Quata_UI_Text : public Quata_UI_Objects
{
	sf::Text			mText;
public:
	explicit			Quata_UI_Text(QuataData&, sf::Vector2f);
	void				draw(sf::RenderTarget& target, sf::RenderStates) const;
	void				refresh_Text(std::string);
	void				set_Text(UINT size ,std::string text);
	void				set_Text_Color(sf::Color);
};


#endif
