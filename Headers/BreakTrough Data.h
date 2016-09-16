#ifndef BREAKTROUGH_DATA_H
#define BREAKTROUGH_DATA_H

#include "BreakTrough Enumerations.h"
#include "DataStorage.h"
#include "MusicPlayer.h"

class BreakTrough_Data
{
	//	Main data:
	Data&							m_Data;
	std::default_random_engine		m_Random_engine;		
	Break::SubStates				m_CurrentSubState;
	sf::Vector2i					m_Mouse_Coordinates;

	//	General things:
	std::map<Break::Key_Positions, sf::Vector2f>		m_Key_Positions;
	std::map<Break::Sizes, sf::Vector2f>				m_Component_Sizes;
	std::map<Break::Character_sizes, UINT>				m_Character_Sizes;
	std::map<Break::Distances, float>					m_Distances;
	std::map<Break::Components, sf::Vector2f>			m_Component_Positions;
	std::map<Break::UI_Components, sf::Vector2f>		m_UI_Component_Positions;
	std::map<Break::Bool_Switches, bool>				m_Switches;
	std::map<Break::Speeds, float>						m_Speeds;
	std::map<Break::Texts, std::string>					m_Texts;
	std::map<Break::Score_increase, UINT>				m_Score_Increase;
	std::map<Break::UINT_Numbers, UINT>					m_Quantities;
	//	Containers for textures
	std::map<Break::Paddle_Type, sf::IntRect>			m_Paddle_TextureRect;		//	Default texture coords.
	std::map<Break::Block_ID, sf::IntRect>				m_Block_TextureRect;		//	Default texture coords.
	std::map<Break::PowerUp_ID, sf::IntRect>			m_PowerUp_TextureRect;		//	Default texture coords.
	std::map<Break::Misc_Textures, sf::IntRect>			m_Miscellaneous_TextrureRect;
	//	Sounds
	std::map<Break::Sounds, sf::Sound>					m_Sounds;

public:
	//	Main Functions:
	explicit			BreakTrough_Data(Data&);
	~BreakTrough_Data();
	void						Exit();
	void						Change_SubState(Break::SubStates);
	bool						Set_TheEnd();
	void						Change_Level(UINT);
	Resources&					get_Resources();

	//	Getters		
	const sf::Vector2f			get_Key_Position(Break::Key_Positions) const;
	const sf::Vector2f			get_Component_Sizes(Break::Sizes) const;
	const UINT					get_Character_Sizes(Break::Character_sizes) const;
	const float					get_Distances(Break::Distances) const;
	const sf::Vector2f			get_Components_Positions(Break::Components) const;
	const sf::Vector2f			get_UI_Components_Positions(Break::UI_Components) const;
	const bool					get_Switches(Break::Bool_Switches) const;
	const float					get_Speed(Break::Speeds) const;
	const std::string			get_Text(Break::Texts) const;
	const UINT					get_Score_increase(Break::Score_increase) const;
	const sf::IntRect			get_TextureRect(Break::Paddle_Type) const;
	const sf::IntRect			get_TextureRect(Break::Block_ID) const;
	const sf::IntRect			get_TextureRect(Break::PowerUp_ID) const;
	const sf::IntRect			get_TextureRect(Break::Misc_Textures) const;
	const UINT					get_Object_Quantities(Break::UINT_Numbers) const;
	const Break::SubStates		get_Current_Substate() const;
	const sf::Vector2i			get_Mouse_Coordinates() const;
	//	Miscellaneous functions
	void						set_Object_Quantities(Break::UINT_Numbers, const UINT);
	void						Play_Sound(Break::Sounds);
	void						update_Mouse();

	std::default_random_engine& get_Random_Engine();
	MusicPlayer&				getMusicPlayer();



};


#endif
