#ifndef BREAKTROUGH_ACTIVE_POWERUPS_H
#define BREAKTROUGH_ACTIVE_POWERUPS_H

#include "BreakTrough UI Objects.h"
class BreakTrough_Data;

class BrkTr_Active_PowerUps : public BrkTr_UI_Objects
{
	const sf::Font&					mFont;
	const sf::Texture&				mStored_texture;
	UINT						mStored_char_size;
	float						mStored_distance;
	sf::Vector2f					mStored_size;
	std::map<Break::PowerUp_ID, std::string>	mStored_names;
	
	
	std::vector<Break::PowerUp_ID>				mIDs;
	std::map<Break::PowerUp_ID, sf::Time>			mTimers;
	std::map<Break::PowerUp_ID, float>			mTotal_times;
	std::map<Break::PowerUp_ID, sf::RectangleShape>		mVisual_Total_times;
	std::map<Break::PowerUp_ID, sf::RectangleShape>		mVisual_Remaining_times;
	std::map<Break::PowerUp_ID, sf::Text>			mPowerUp_name;	
	sf::Text						mDescription;


	std::vector<sf::FloatRect>			mPW_Blocks;
	sf::RectangleShape				mBackground;
	sf::VertexArray					m_Vertices;
public:
	BrkTr_Active_PowerUps(BreakTrough_Data&);
	void		draw(sf::RenderTarget& target, sf::RenderStates state) const;
	void		update(sf::Time& time);

	void		add_PowerUp(Break::PowerUp_ID);
	void		remove_PowerUp(Break::PowerUp_ID);
	void		remove_all_PowerUps();
	const float get_remaining_time(Break::PowerUp_ID) const;
};


#endif
