#include "stdafx.h"
#include "Comet Wars Rear Comets.h"
#include "Comet Wars Data.h"

CometWars_Rear_Comets::CometWars_Rear_Comets(CometWarsData& data)
	: mStored_tex(data.getResources().getTexture(ID_CometWars))
{
	std::default_random_engine& random = data.get_random_engine();
	UINT comet_number = data.getKey_Position(CW::kp_BottomRight).x / 4;

	mVertices.setPrimitiveType(sf::Quads);
	mVertices.resize(4 * comet_number);

	mRestartPosition = -2*data.getDistance(CW::dis_Far);	// Da, minus!
	mSpeed = data.getSpeed(CW::speed_Rear_Comet);

	std::uniform_int_distribution<int> distributor_X(-data.getDistance(CW::dis_Far), data.getKey_Position(CW::kp_BottomRight).x + data.getDistance(CW::dis_Far));
	std::uniform_int_distribution<int> distributor_Y(0, data.getKey_Position(CW::kp_BottomRight).y );

	mStored_size_big = data.getObj_Sizes(CW::size_Rear_Comet);
	mStored_size_small = data.getObj_Sizes(CW::size_Rear_Mini_Comet);

	sf::Vector2f size;	//	Treba da se pomnozi sa koefeicijentom skaliranja.

	UINT big_comets = 10;
	sf::IntRect tr;

	for (UINT i = 0; i < mVertices.getVertexCount(); i = i + 4)
	{

		if ((i / 4) <= big_comets)
		{
			std::uniform_int_distribution<int>	distributor_number(12, 17);
			UINT number = distributor_number(data.get_random_engine());		// Bira nasumicno od 12 do 17, tj. sve Rear Major tipa asteroida.
			CW::AsteroidType type = static_cast<CW::AsteroidType>(number);
			tr = data.getComet_Texture_rect(type);
			size = mStored_size_big;
			
		}
		else
		{
			std::uniform_int_distribution<int>	distributor_number(18, 29);
			UINT number = distributor_number(data.get_random_engine());		// Bira nasumicno od 18 do 29, tj. sve Rear Minor tipa asteroida.
			CW::AsteroidType type = static_cast<CW::AsteroidType>(number);
			tr = data.getComet_Texture_rect(type);
			size = mStored_size_small;
			
		}

		float x = distributor_X(random);
		float y = distributor_Y(random);
		sf::Vector2f pos(x, y);
		sf::FloatRect	gran(pos, size);

		mCometBounds.push_back(gran);

		mVertices[i].position = sf::Vector2f(pos);
		mVertices[i + 1].position = sf::Vector2f(pos.x + size.x, pos.y);
		mVertices[i + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
		mVertices[i + 3].position = sf::Vector2f(pos.x, pos.y + size.y);
		
		mVertices[i].texCoords = sf::Vector2f(tr.left, tr.top);
		mVertices[i + 1].texCoords = sf::Vector2f(tr.left + tr.width, tr.top);
		mVertices[i + 2].texCoords = sf::Vector2f(tr.left + tr.width, tr.top + tr.height);
		mVertices[i + 3].texCoords = sf::Vector2f(tr.left, tr.top + tr.height);

		mVertices[i].color = sf::Color(128,128,128,255);
		mVertices[i + 1].color = sf::Color(128, 128, 128, 255);
		mVertices[i + 2].color = sf::Color(128, 128, 128, 255);
		mVertices[i + 3].color = sf::Color(128, 128, 128, 255);

	}
	mBoundry = sf::FloatRect(sf::Vector2f(data.getKey_Position(CW::kp_TopRight).x + 2*data.getDistance(CW::dis_Far), data.getKey_Position(CW::kp_TopRight).y), sf::Vector2f(data.getDistance(CW::dis_Medium), data.getKey_Position(CW::kp_BottomRight).y));
}

void CometWars_Rear_Comets::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = &mStored_tex;
	target.draw(mVertices, state);
}

void CometWars_Rear_Comets::update(sf::Time& vreme)
{
	for (auto& i : mCometBounds)
	{
		if (i.intersects(mBoundry))
		{
			i.left = mRestartPosition;
		}
	}

	UINT j = 0;
	for (UINT i = 0; i < mVertices.getVertexCount(); i = i + 4)
	{
		sf::Vector2f size;
		sf::FloatRect temp = mCometBounds.at(j);
		temp.left += mSpeed * vreme.asSeconds();
		if (temp.width >= mStored_size_big.x && temp.height >= mStored_size_big.y)
		{
			size = mStored_size_big;
		}
		else
		{
			size = mStored_size_small;
		}
		sf::Vector2f pos(temp.left, temp.top);

		mVertices[i].position = sf::Vector2f(pos);
		mVertices[i + 1].position = sf::Vector2f(pos.x + size.x, pos.y);
		mVertices[i + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
		mVertices[i + 3].position = sf::Vector2f(pos.x, pos.y + size.y);
		mCometBounds.at(j) = temp;
		j++;
	}
}