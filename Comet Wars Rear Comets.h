#ifndef COMET_WARS_REAR_COMETS_H
#define COMET_WARS_REAR_COMETS_H

#include "Comet Wars Deco Base Class.h"

class CometWarsData;

class CometWars_Rear_Comets : public CometWars_Deco_Base_Class
{
	const sf::Texture&				mStored_tex;
	sf::VertexArray					mVertices;
	std::vector<sf::FloatRect>		mCometBounds;
	sf::FloatRect					mBoundry;
	float							mRestartPosition, mSpeed;
	sf::Vector2f					mStored_size_big, mStored_size_small;
public:
	CometWars_Rear_Comets(CometWarsData&);

	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		update(sf::Time&);



};



#endif