#include "stdafx.h"
#include "BreakTrough Active PowerUps.h"
#include "BreakTrough Data.h"

BrkTr_Active_PowerUps::BrkTr_Active_PowerUps(BreakTrough_Data& data)
	: mFont(data.get_Resources().getFont(ID_Global))
	, mStored_texture(data.get_Resources().getTexture(ID_BreakTrough))
{

	mStored_names.insert(std::pair<Break::PowerUp_ID, std::string>(Break::pID_Fast_Ball, data.get_Text(Break::txt_pow_Fast_Ball)));
	mStored_names.insert(std::pair<Break::PowerUp_ID, std::string>(Break::pID_Slow_Ball, data.get_Text(Break::txt_pow_Slow_Ball)));
	mStored_names.insert(std::pair<Break::PowerUp_ID, std::string>(Break::pID_Sticky_Paddle, data.get_Text(Break::txt_pow_Sticky_Paddle)));
	mStored_names.insert(std::pair<Break::PowerUp_ID, std::string>(Break::pID_Stretch_Paddle, data.get_Text(Break::txt_pow_Big_Paddle)));
	mStored_names.insert(std::pair<Break::PowerUp_ID, std::string>(Break::pID_Shrink_Paddle, data.get_Text(Break::txt_pow_Small_Paddle)));
	mStored_names.insert(std::pair<Break::PowerUp_ID, std::string>(Break::pID_Laser_Paddle, data.get_Text(Break::txt_pow_Laser_Paddle)));

	mTotal_times.insert(std::pair<Break::PowerUp_ID, float>(Break::pID_Fast_Ball, 30));
	mTotal_times.insert(std::pair<Break::PowerUp_ID, float>(Break::pID_Slow_Ball, 30));
	mTotal_times.insert(std::pair<Break::PowerUp_ID, float>(Break::pID_Sticky_Paddle, 45));
	mTotal_times.insert(std::pair<Break::PowerUp_ID, float>(Break::pID_Stretch_Paddle, 45));
	mTotal_times.insert(std::pair<Break::PowerUp_ID, float>(Break::pID_Shrink_Paddle, 45));
	mTotal_times.insert(std::pair<Break::PowerUp_ID, float>(Break::pID_Laser_Paddle, 15));

	mStored_distance = data.get_Distances(Break::dis_Medium);
	mStored_char_size = data.get_Character_Sizes(Break::ch_Small);
	mStored_size = data.get_Component_Sizes(Break::size_Timer);

	sf::Vector2f mBlock_size = data.get_Component_Sizes(Break::size_ActivePowerUp_Block);
	sf::Vector2f pos(data.get_UI_Components_Positions(Break::cUI_PowerUp_Timers));

	sf::FloatRect rkt = sf::FloatRect(pos, mBlock_size);
	mPW_Blocks.push_back(rkt);
	rkt = sf::FloatRect(sf::Vector2f(pos.x, pos.y + mBlock_size.y), mBlock_size);
	mPW_Blocks.push_back(rkt);
	rkt = sf::FloatRect(sf::Vector2f(pos.x, pos.y + 2 * mBlock_size.y), mBlock_size);
	mPW_Blocks.push_back(rkt);

	mBackground.setOutlineColor(sf::Color::Yellow);
	mBackground.setOutlineThickness(-1);
	mBackground.setFillColor(sf::Color(32,32,32,255));
	mBackground.setSize(sf::Vector2f(2*data.get_Distances(Break::dis_Medium) + mBlock_size.x, 3 * mBlock_size.y));
	mBackground.setPosition(mPW_Blocks.at(0).left - data.get_Distances(Break::dis_Near), mPW_Blocks.at(0).top);

	sf::Vector2f size = data.get_Component_Sizes(Break::size_Deco_Bolt);
	sf::Vector2f bs = mBackground.getSize();
	sf::Vector2f bp = mBackground.getPosition();

	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(32);	

	sf::IntRect tx = data.get_TextureRect(Break::t_Decoration_Feature_Corner1);

	for (UINT i = 0; i < m_Vertices.getVertexCount(); i += 4)
	{
		if (i == 0)
		{
			pos = sf::Vector2f(bp.x - size.x, bp.y - size.y);
		}
		else if (i == 4)
		{
			pos = sf::Vector2f(bp.x + bs.x, bp.y - size.y);
		}
		else if (i == 8)
		{
			pos = sf::Vector2f(bp.x + bs.x, bp.y + bs.y);
		}
		else if (i == 12)
		{
			pos = sf::Vector2f(bp.x - size.x, bp.y + bs.y);
		}
		else if (i == 16)
		{
			size = sf::Vector2f(data.get_Component_Sizes(Break::size_Deco_Vertical_border).x, bs.y);//data.get_Component_Sizes(Break::size_Deco_Vertical_border);
			tx = data.get_TextureRect(Break::t_Decoration_Feature_Vertical2);
			pos = sf::Vector2f(bp.x - size.x, bp.y);
		}
		else if (i == 20)
		{
			pos = sf::Vector2f(bp.x + bs.x, bp.y);
		}
		else if (i == 24)
		{
			size = sf::Vector2f(bs.x, data.get_Component_Sizes(Break::size_Deco_Horizontal_border).y);//data.get_Component_Sizes(Break::size_Deco_Horizontal_border);
			tx = data.get_TextureRect(Break::t_Decoration_Feature_Horizontal2);
			pos = sf::Vector2f(bp.x, bp.y - size.y);
		}
		else if (i == 28)
		{
			pos = sf::Vector2f(bp.x, bp.y + bs.y);
		}

		m_Vertices[i].position = pos;
		m_Vertices[i + 1].position = sf::Vector2f(pos.x + size.x, pos.y);
		m_Vertices[i + 2].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
		m_Vertices[i + 3].position = sf::Vector2f(pos.x, pos.y + size.y);

		m_Vertices[i].texCoords = sf::Vector2f(tx.left, tx.top);
		m_Vertices[i + 1].texCoords = sf::Vector2f(tx.left + tx.width, tx.top);
		m_Vertices[i + 2].texCoords = sf::Vector2f(tx.left + tx.width, tx.top + tx.height);
		m_Vertices[i + 3].texCoords = sf::Vector2f(tx.left, tx.top + tx.height);
	}

	mDescription.setFont(mFont);
	mDescription.setCharacterSize(data.get_Character_Sizes(Break::ch_Medium_Small));
	mDescription.setString(data.get_Text(Break::txt_ActivePows));
	mDescription.setColor(sf::Color::Yellow);
	sf::FloatRect bounds = mDescription.getLocalBounds();
	mDescription.setOrigin(0, 0);
	sf::FloatRect b = mPW_Blocks.at(0);
	mDescription.setPosition(b.left, b.top);
}

void BrkTr_Active_PowerUps::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	
	state.transform *= getTransform();
	state.texture = &mStored_texture;
	target.draw(mBackground, state);
	target.draw(mDescription, state);
	target.draw(m_Vertices, state);
	for (const auto& it : mPowerUp_name)
	{
		target.draw(it.second, state);
	}
	for (const auto& it : mVisual_Total_times)
	{
		target.draw(it.second, state);
	}
	for (const auto& it : mVisual_Remaining_times)
	{
		target.draw(it.second, state);
	}
}

void BrkTr_Active_PowerUps::update(sf::Time& time)
{
	for (auto& i : mIDs)
	{	
		bool erase = false;
		mTimers.at(i) -= time;
		
		//	For every element, I have to calculate how much time is left in percentage and afterwards i need to 
		//	adjust the width of "time left" rectangle using those percentage.
		float procenat = 100 * (mTimers.at(i).asSeconds() / mTotal_times.at(i));
		if (procenat < 0)
		{
			procenat = 0;
			erase = true;
		}
		float nova = (mStored_size.x * procenat) / 100 ;	
		mVisual_Remaining_times.at(i).setSize(sf::Vector2f(nova, mStored_size.y));
		
		if (erase)
		{
			//	Here the power up is erased and the loop is stopped in order to prevent "iterator not incementable" error
			remove_PowerUp(i);
			break;
		}
	}

}

void BrkTr_Active_PowerUps::add_PowerUp(Break::PowerUp_ID param)
{
	//	So, every power up object is made from these components: 

	sf::Time							time;			//	Remainting time.
	sf::RectangleShape						rect1, rect2;		//	Graphical reperesentation of time:  rect1 - remaining time; rect2 - full time
	sf::Text							name;			//	Name
	sf::FloatRect							bo;			//	Border
	//	Iterators for every single container.
	std::map<Break::PowerUp_ID, sf::Time>::iterator			it1;			
	std::map<Break::PowerUp_ID, sf::RectangleShape>::iterator	it2;
	std::map<Break::PowerUp_ID, sf::Text>::iterator			it3;
	std::vector<Break::PowerUp_ID>::iterator			it4;

	//	First, I need to check wheter the new power up is contradictory with already existing power ups:
	for (Break::PowerUp_ID i : mIDs)
	{
		if (param == Break::pID_Fast_Ball || param == Break::pID_Slow_Ball)
		{
			if (i != param && (i == Break::pID_Fast_Ball || i == Break::pID_Slow_Ball))
			{
				remove_PowerUp(i);
				break;
			}
		}
		else if (param == Break::pID_Laser_Paddle || param == Break::pID_Shrink_Paddle || param == Break::pID_Sticky_Paddle || param == Break::pID_Stretch_Paddle)
		{
			if (i != param && (i == Break::pID_Laser_Paddle || i == Break::pID_Shrink_Paddle || i == Break::pID_Sticky_Paddle || i == Break::pID_Stretch_Paddle))
			{
				remove_PowerUp(i);
				break;
			}
		}
	}

	//	Then I check if the current power up already exists.
	it4 = std::find_if(mIDs.begin(), mIDs.end(), [&](Break::PowerUp_ID obj)
	{
		if (obj == param)
			return true;
		else
			return false;
	});

	//	If not, then it is pushed into container.
	if (it4 == mIDs.end())
	{
		mIDs.push_back(param);
		it4 = mIDs.end() - 1;
	}
	
	//	I take the distance from the start of the container.
	UINT distance = std::distance(mIDs.begin(), it4);
	distance++;
	bo = mPW_Blocks.at(distance);

	//	Then I am giving him a name and a full time depending on a power up type.
	name.setFont(mFont);
	name.setCharacterSize(mStored_char_size);
	name.setString(mStored_names.at(param));
	time = sf::seconds(mTotal_times.at(param));

	//	Afterwards, i check every containter if it is already active, using iterators.
	//	If it is active, then it needs to get refreshed.
	//	If it isn't active, then it need to be put inside the container.

	it1 = mTimers.find(param);
	if (it1 == mTimers.end())
	{
		mTimers.insert(std::pair<Break::PowerUp_ID, sf::Time>(param, time));
	}
	else
	{
		it1->second = time;
	}
	
	sf::FloatRect bounds = name.getLocalBounds();
	name.setOrigin(0, 0);

	name.setPosition(bo.left, bo.top);
	it3 = mPowerUp_name.find(param);
	if (it3 == mPowerUp_name.end())
	{
		mPowerUp_name.insert(std::pair<Break::PowerUp_ID, sf::Text>(param, name));
	}

	rect2.setSize(mStored_size);
	rect2.setFillColor(sf::Color::Red);
	bounds = rect2.getLocalBounds();
	rect2.setOrigin(0, bounds.top + bounds.height / 2);
	rect2.setPosition(name.getPosition().x + mStored_distance, name.getPosition().y + 2*mStored_distance);
	it2 = mVisual_Total_times.find(param);
	if (it2 == mVisual_Total_times.end())
	{
		mVisual_Total_times.insert(std::pair<Break::PowerUp_ID, sf::RectangleShape>(param, rect2));
	}
	else
	{
		it2->second = rect2;
	}

	rect1.setSize(mStored_size);
	rect1.setFillColor(sf::Color::Green);
	bounds = rect1.getLocalBounds();
	rect1.setOrigin(0, bounds.top + bounds.height / 2);
	rect1.setPosition(name.getPosition().x + mStored_distance, name.getPosition().y + 2*mStored_distance);
	it2 = mVisual_Remaining_times.find(param);
	if (it2 == mVisual_Remaining_times.end())
	{
		mVisual_Remaining_times.insert(std::pair<Break::PowerUp_ID, sf::RectangleShape>(param, rect1));
	}
	else
	{
		it2->second = rect1;
	}
}

//	Function for deletion of power ups.
//	If there is more than one power up, and if remaining time of second power up is still ticking,
//	then I need to adjust the position of the graphical representation of the power up, to take the place of the first - now deleted - power up
void BrkTr_Active_PowerUps::remove_PowerUp(Break::PowerUp_ID param)
{
	mPowerUp_name.erase(param);
	mTimers.erase(param);
	mVisual_Remaining_times.erase(param);
	mVisual_Total_times.erase(param);

	mIDs.erase(std::remove_if(mIDs.begin(), mIDs.end(), [&](Break::PowerUp_ID obj)
	{
		if (obj == param)
			return true;
		else
			return false; 
	}	), mIDs.end());

	for (std::vector<Break::PowerUp_ID>::iterator it = mIDs.begin(); it != mIDs.end(); ++it)
	{
		UINT distance = std::distance(mIDs.begin(), it);
		sf::FloatRect bounds = mPW_Blocks.at(distance + 1);
		mPowerUp_name.at(*it).setPosition(bounds.left, bounds.top);
		mVisual_Total_times.at(*it).setPosition(mPowerUp_name.at(*it).getPosition().x + mStored_distance, mPowerUp_name.at(*it).getPosition().y + 2*mStored_distance);
		mVisual_Remaining_times.at(*it).setPosition(mPowerUp_name.at(*it).getPosition().x + mStored_distance, mPowerUp_name.at(*it).getPosition().y + 2*mStored_distance);
	}
}

//	Function for deleteting all of power ups.
//	Used when the level is completed or when player looses a life.
void BrkTr_Active_PowerUps::remove_all_PowerUps()
{
	mTimers.clear();
	mPowerUp_name.clear();
	mVisual_Remaining_times.clear();
	mVisual_Total_times.clear();
	mIDs.clear();
}

const float BrkTr_Active_PowerUps::get_remaining_time(Break::PowerUp_ID param) const
{
	return mTimers.at(param).asSeconds();
}
