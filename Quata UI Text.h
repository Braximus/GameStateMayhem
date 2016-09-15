#ifndef QUATA_UI_TEXT_H
#define QUATA_UI_TEXT_H


#include "Quata UI Objects.h"
class QuataData;

//	Ova klasa ce povuci dvostruku duznost i kao oznaka i kao rezultat

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
