#include "stdafx.h"
#include "Comet Wars Game Asteroid.h"
#include "Comet Wars Data.h"

CometWars_Game_Asteroid::CometWars_Game_Asteroid(CometWarsData& data, bool is_mini_comet)
{
	mini_comet = is_mini_comet;
	mAsteroid.setTexture(&data.getResources().getTexture(ID_CometWars));
	if (!mini_comet)
	{
		mDamageState = CW::No_Damage;		

		std::uniform_int_distribution<int>	distributor_number(0, 3);
		UINT n = distributor_number(data.get_random_engine());		//	Chooses randomly between 0 and 3 - all Major types of comet.
		CW::AsteroidType type = static_cast<CW::AsteroidType>(n);
		mTextureRect = data.getComet_Texture_rect(type);
		mAsteroid.setTextureRect(mTextureRect);
	
		mAsteroid.setSize(data.getObj_Sizes(CW::size_Comet));
		sf::FloatRect b = mAsteroid.getLocalBounds();
		mAsteroid.setOrigin(b.width / 2, b.height / 2);
	
		
		std::uniform_int_distribution<int> dis_number(-180, 180);
		float angle = dis_number(data.get_random_engine());
		mRotation = angle;

		float angle_direction = dis_number(data.get_random_engine());
		angle_direction = angle_direction*3.14 / 180;
		float x = cos(angle_direction);
		float y = sin(angle_direction);
		float speed = data.getSpeed(CW::speed_Asteroid);
		mVelocity = sf::Vector2f(speed*x, speed*y);

	}
	else
	{
		mDamageState = CW::Heavy_Damage;

		std::uniform_int_distribution<int>	distributor_number(4, 11);
		UINT n = distributor_number(data.get_random_engine());		//	Chooses randomly between 4 and 11 - all Minor types of comet.
		CW::AsteroidType type = static_cast<CW::AsteroidType>(n);
		mTextureRect = data.getComet_Texture_rect(type);
		mAsteroid.setTextureRect(mTextureRect);

		mAsteroid.setSize(data.getObj_Sizes(CW::size_Mini_Comet));
		sf::FloatRect b = mAsteroid.getLocalBounds();
		mAsteroid.setOrigin(b.width / 2, b.height / 2);
	

		std::uniform_int_distribution<int> dis_number(-180, 180);
		float angle = dis_number(data.get_random_engine());
		mRotation = angle;

		float angle_direction = dis_number(data.get_random_engine());
		angle_direction = angle_direction*3.14 / 180;
		float x = cos(angle_direction);
		float y = sin(angle_direction);
		float speed = data.getSpeed(CW::speed_Mini_Asteroid);
		mVelocity = sf::Vector2f(speed*x, speed*y);
	}
	UINT i = data.getNumber_of_Comets();
	i++;
	data.setNumber_of_Comets(i);
	is_deleted = false;
}

void CometWars_Game_Asteroid::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(mAsteroid, state);
}

void CometWars_Game_Asteroid::update(sf::Time& time)
{
	//	In order to avoid border increase of comets during their rotation, during every iteration I take current angle, reset it,
	//	refresh the comet position and border and then I return the old angle and refresh it.
	mAsteroid.move(mVelocity * time.asSeconds());
	mPosition = mAsteroid.getPosition();
	float old_rotation = mAsteroid.getRotation();

	mAsteroid.setRotation(0);
	mBounds = mAsteroid.getGlobalBounds();
	mAsteroid.setRotation(old_rotation);
	mAsteroid.rotate(mRotation * time.asSeconds());
}

void CometWars_Game_Asteroid::setPosition(sf::Vector2f param)
{
	mPosition = param;
	mAsteroid.setPosition(mPosition);
}

void CometWars_Game_Asteroid::setVelocity(sf::Vector2f param)
{
	mVelocity = param;
}

void CometWars_Game_Asteroid::changeTexRect(sf::IntRect param)
{
	mTextureRect = param;
}

void CometWars_Game_Asteroid::changeDamageStatus()
{	
	mDamageState = static_cast<CW::AsteroidDamage>(mDamageState + 1);
	if (mDamageState != CW::Dead)
	{
		//	It assumes that astroid is Major type:
		sf::IntRect temp_rect = mAsteroid.getTextureRect();
		mTextureRect = sf::IntRect(temp_rect.left + 50, temp_rect.top, temp_rect.width, temp_rect.height);
		mAsteroid.setTextureRect(mTextureRect);
	}
}

const CW::AsteroidDamage CometWars_Game_Asteroid::getDamage() const
{
	return mDamageState;
}
