#ifndef COMET_WARS_BACKGROUND_H
#define COMET_WARS_BACKGROUND_H

#include "Comet Wars Deco Base Class.h"
class CometWarsData;

//	Za sada ce sadrzati samo zvezde;

class CometWars_Background: public CometWars_Deco_Base_Class
{
	enum FadeStatus
	{
		FadeNone,
		FadeIn,
		FadeOut
	};
	
	sf::RectangleShape			mBackground;
	sf::VertexArray				mVertices;
	std::vector<FadeStatus>		mStatus;
public:
	CometWars_Background(CometWarsData&);

	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		update(sf::Time& time);

};




#endif