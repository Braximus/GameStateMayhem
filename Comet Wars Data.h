#ifndef COMETWARS_DATA_H
#define COMETWARS_DATA_H

#include "Comet Wars Enumerations.h"
#include "DataStorage.h"
#include "MusicPlayer.h"

class CometWarsData
{

	Data&									mData;
	CW::SubStates							mCurrentSubState;
	bool									mRestart_Switch;
	UINT									seed;
	std::default_random_engine				random_generator;
	sf::Vector2f							mMouse_Coordinates;
	float									mScale_coefficient;
	UINT									mScore;
	int										mLives;
	UINT									mNumber_of_Ast;

	std::map<CW::Key_Positions, sf::Vector2f>			mKey_Positions; 
	std::map<CW::Distances,float>						mDistances;
	std::map<CW::Character_size, float>					mCharacter_sizes;
	std::map<CW::Texts, std::string>					mTexts;
	std::map<CW::Zones, sf::FloatRect>					mZones;
	std::map<CW::Sounds, sf::Sound>						mSounds;
	std::map<CW::Object_Speed, float>					mSpeed;		//	Brzine broda, asteroida i metkova		(mogu da stavim i std::vector<float> da stavim razlicite brzine za asteroide)
	std::map<CW::Components_size, sf::Vector2f>			mSizes;		//	Velicine broda, asteroida i metkova
	std::map<CW::AsteroidType, sf::IntRect>				mComet_Texture_rects;		//	Tipovi tekstura asteroida
	std::map<CW::ShipType, sf::IntRect>					mShip_Texture_rects;
	std::map<CW::Misc_Tex_rects, sf::IntRect>			mMisc_Texture_rects;
	std::map<CW::UI_Components, sf::Vector2f>			mUI_Positions;
public:
	explicit						CometWarsData(Data&);
	~CometWarsData();
	//	Operations
	CW::End							mEndType;
	void							update_mouse();
	void							change_Cursor(sf::IntRect);
	bool							setEnd();
	void							ChangeSubState(CW::SubStates);
	void							setNumber_of_Comets(UINT);
	void							change_Score(UINT);
	void							remove_life();
	void							Exit();
	void							Restart();
	void							Play_Sound(CW::Sounds);
	//	Getter Functions
	const CW::SubStates							getCurrentSubState() const;	//	Da namestim i getprevious substate
	Resources&									getResources();
	const sf::Vector2f							getMouse_position() const;
	std::default_random_engine&					get_random_engine();
	const sf::Vector2f							getKey_Position(CW::Key_Positions);
	const float									getCharacter_Size(CW::Character_size);
	const float									getDistance(CW::Distances);
	const float									getScale_Coefficient();
	const std::string							getText(CW::Texts);
	const sf::Vector2f							getUI_Position(CW::UI_Components) const;
	const sf::FloatRect							getZone(CW::Zones);
	const UINT									getScore() const;
	const std::map<CW::Zones, sf::FloatRect >&	getZone_map();
	const sf::Vector2f							getObj_Sizes(CW::Components_size) const;
	const sf::IntRect							getComet_Texture_rect(CW::AsteroidType) const;
	const sf::IntRect							getShip_Texture_rect(CW::ShipType) const;
	const sf::IntRect							getMisc_Texture_rect(CW::Misc_Tex_rects) const;
	const UINT									getNumber_of_Comets() const;
	const int									getNumber_of_Lives() const;
	const float									getSpeed(CW::Object_Speed) const;
	MusicPlayer&								getMusicPlayer();


									
};





#endif