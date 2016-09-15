#ifndef MENU_DATA_H
#define MENU_DATA_H

#include "Menu_Enumerations.h"
#include "StateCategory.h"
#include "Resources.h"
#include "MusicPlayer.h"
class Options;
class Data;


class MenuData
{
	friend class Options;
	Data&					mData;
	Resources&				mRes;
	Menus::SubStates		mCurrentSubState;

	//	Dodati vrednosti za menije ovde.
	//	Svaki meni je odvojen enumeracijom.
	//	Svaki meni ima sopstene konejnere za vrednosti. 
	//	Sve vrednsoti se deklarisu i definisu kada se "Meni" stanje podigne.
	//	"Meni Data" komunicira sa "DataStorage".
	//	"Meni Data" prenosi vrednosti u menije i njihove komponente.
	//	Komponente ne znaju za postojanje "Meni Data" i "Data Storage"

	//	Razmere:
	float			mScale_coef;
	//	Velicina Slova:
	std::map<Menus::Char_sizes, float>				mChar_Sizes;
	//	Velicine Objekata:
	std::map<Menus::Objects_sizes, sf::Vector2f>		mObject_Sizes;
	//	Rastojanja:
	std::map<Menus::Distances, float>			mDistances;
	//	Kljucne Pozicije:
	std::map<Menus::Key_positions, sf::Vector2f>			mKeyPositions;
	//	Kontejner za padajuci meni:
	std::vector<std::string>				mVideo_mode_names, mAA_levels;
	//	Kontejner za tex_rects:
	std::vector<sf::IntRect>				mCheck_tex_rects;
	//	Kontejner za zvukove:
	std::map<Menus::Sounds, sf::Sound>		mSounds;
	
public:
	MenuData(Data&);
	~MenuData();
	void					ChangeState(eState);
	void					ChangeSubState(Menus::SubStates);
	void					Close();
	const sf::Vector2i		MouseCoord() const;
	Resources&							getResources();
	bool								mRefreshed;	//	Okidac za osvezavanje.
	void					refresh();
	void					Play_Sound(Menus::Sounds);
	MusicPlayer&			getMusicPlayer();


	const Menus::SubStates		getCurrentSubState() const;
	const float					getScale_coef() const;
	const float					getMenu_Char_Sizes(Menus::Char_sizes) const;
	const sf::Vector2f			getMenu_Object_Sizes(Menus::Objects_sizes) const;
	const float					getMenu_Distances(Menus::Distances) const;
	const sf::Vector2f			getMenu_Key_Positions(Menus::Key_positions) const;

	const std::vector<std::string>&		get_Video_mode_names_cont() const;
	const std::vector<std::string>&		get_AA_levels_cont() const;
	const std::vector<sf::IntRect>&		get_Check_tex_rects() const;
};


#endif