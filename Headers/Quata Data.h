#ifndef QUATA_DATA_H
#define QUATA_DATA_H

#include "DataStorage.h"
#include "Quata Enumerations.h"
#include "MusicPlayer.h"


class QuataData
{
	Qua::SubState					mCurrentSubState;
	Data&						mData;
	sf::Vector2f					Mouse_Coordinates;
	UINT						seed;
	std::default_random_engine			random_generator;

	std::map<Qua::Quata_Key_Positions, sf::Vector2f>		Key_Positions;
	std::map<Qua::Quata_Char_Sizes, float>				Character_Sizes;
	std::map<Qua::Quata_Obj_Sizes, sf::Vector2f>			Object_Sizes;
	std::map<Qua::Quata_Distances, float>				Distances;
	std::map<Qua::Quata_Zones, sf::FloatRect>			Zones;
	std::map<Qua::Quata_Texts, std::string>				Texts;
	std::map<Qua::Quata_Texture_rects, sf::IntRect>			Texture_rects;
	std::map<Qua::Quata_Speeds, float>				Speeds;
	std::map<Qua::Quata_UI_Components, UINT>			Scores;

	std::map<Qua::Sounds, sf::Sound>				mSounds;

public:
	//
	explicit				QuataData(Data&);
	~QuataData();
	void					update_mouse();
	bool					victory();
	void					changeSubState(Qua::SubState);
	void					Exit();	

	void		set_Texts(const Qua::Quata_Texts, std::string);
	void		set_Score(const Qua::Quata_UI_Components, UINT);
	void		Play_Sound(Qua::Sounds);

	const sf::Vector2f					get_Object_Size(Qua::Quata_Obj_Sizes) const;
	const sf::Vector2f					get_Key_Position(Qua::Quata_Key_Positions) const;
	const float						get_Character_Size(Qua::Quata_Char_Sizes) const;
	const float						get_Distance(Qua::Quata_Distances) const;
	const float						get_Speed(Qua::Quata_Speeds) const;
	const sf::FloatRect					get_Zone(Qua::Quata_Zones) const;
	const std::string					get_Text(Qua::Quata_Texts) const;
	const sf::IntRect					get_Texture_rects(Qua::Quata_Texture_rects) const;
	const UINT						get_Score(Qua::Quata_UI_Components) const;
	const Qua::SubState					getCurrentSubstate() const;
	const sf::Vector2f					get_Mouse_Coordinates() const;
	std::default_random_engine&				get_Random_Engine();
	Resources&						get_Resources();
	MusicPlayer&						getMusicPlayer();
};

#endif
