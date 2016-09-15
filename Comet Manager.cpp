#include "stdafx.h"
#include "Comet Manager.h"
#include "Comet Wars Data.h"
#include "Debug.h"

Comet_Manager::Comet_Manager(CometWarsData& data)
	:mData(data)
{

}

std::deque<CometWars_Game_Objects*> Comet_Manager::pass_pointers()
{
	std::deque<CometWars_Game_Objects*> temp_deque;
	for (auto& it : mComets)
	{
		temp_deque.push_back(&it);
	}
	return temp_deque;	
}

void Comet_Manager::update(sf::Time& time)
{

	for (auto& it : mComets)
	{
		it.update(time);
	}
	mData.setNumber_of_Comets(getNumber_of_comets());
	DebugClass::numbers[0] = mData.getNumber_of_Comets();
}

void Comet_Manager::restart()
{
	mComets.clear();
}

void Comet_Manager::create_comet(bool is_mini_comet)
{
	CometWars_Game_Asteroid a_comet(mData, is_mini_comet);
	mComets.push_back(a_comet);
}

void Comet_Manager::delete_comet()
{
	mComets.erase(std::remove_if(mComets.begin(), mComets.end(), 
		[&](CometWars_Game_Asteroid obj)
		{
			if (obj.is_marked())
			{
				return true;
			}
			else
			{
				return false;
			}
		}		
	), mComets.end());
}

const CW::AsteroidDamage Comet_Manager::damage_comet(UINT param)
{
	mComets.at(param).changeDamageStatus();
	if (mComets.at(param).getDamage() == CW::Dead)
	{
		mComets.at(param).mark_for_deletion();
	}
	return mComets.at(param).getDamage();
}

void Comet_Manager::setComet_Position(UINT indice, sf::Vector2f position)
{
	mComets.at(indice).setPosition(position);
}

const sf::Vector2f Comet_Manager::getComet_Position(UINT param) const
{
	return mComets.at(param).getPosition();
}

const sf::FloatRect Comet_Manager::getComet_Bounds(UINT param) const
{
	return mComets.at(param).getBounds();
}

const bool Comet_Manager::isMini_Comet(UINT param) const
{
	return mComets.at(param).mini_comet;
}

const UINT Comet_Manager::getNumber_of_comets() const
{
	return mComets.size();
}
