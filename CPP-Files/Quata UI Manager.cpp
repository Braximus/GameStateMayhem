#include "stdafx.h"
#include "Quata UI Manager.h"
#include "Quata Data.h"

Quata_UI_Manager::Quata_UI_Manager(QuataData& data)
	:mData(data)
{
	is_pause_on = false;
	is_SplashScreen_on = false;

	Quata_UI_Text	txt(mData, sf::Vector2f(mData.get_Key_Position(Qua::kp_UpperCenter_Screen).x - mData.get_Distance(Qua::dis_Medium), mData.get_Key_Position(Qua::kp_UpperCenter_Screen).y + mData.get_Distance(Qua::dis_Medium)));
	txt.set_Text_Color(sf::Color::Green);
	mScores.insert(std::pair<Qua::Quata_UI_Components, Quata_UI_Text>(Qua::cu_Score1, txt));

	Quata_UI_Text txt2(mData, sf::Vector2f(mData.get_Key_Position(Qua::kp_UpperCenter_Screen).x + mData.get_Distance(Qua::dis_Medium), mData.get_Key_Position(Qua::kp_UpperCenter_Screen).y + mData.get_Distance(Qua::dis_Medium)));
	txt2.set_Text_Color(sf::Color::Red);
	mScores.insert(std::pair<Qua::Quata_UI_Components, Quata_UI_Text>(Qua::cu_Score2, txt2));

	Quata_UI_Text txt3(mData, sf::Vector2f(mData.get_Key_Position(Qua::kp_UpperCenter_Screen).x - mData.get_Object_Size(Qua::size_Playground).x / 2, mData.get_Key_Position(Qua::kp_UpperCenter_Screen).y + mData.get_Distance(Qua::dis_Medium)));
	txt3.set_Text(mData.get_Character_Size(Qua::ch_Medium), mData.get_Text(Qua::txt_Player1_name));
	txt3.set_Text_Color(sf::Color::Green);
	mTexts.insert(std::pair<Qua::Quata_Texts, Quata_UI_Text>(Qua::txt_Player1_name, txt3));

	Quata_UI_Text txt4(mData, sf::Vector2f(mData.get_Key_Position(Qua::kp_UpperCenter_Screen).x + mData.get_Object_Size(Qua::size_Playground).x / 2 - mData.get_Distance(Qua::dis_VeryFar), mData.get_Key_Position(Qua::kp_UpperCenter_Screen).y + mData.get_Distance(Qua::dis_Medium)));
	txt4.set_Text(mData.get_Character_Size(Qua::ch_Medium), mData.get_Text(Qua::txt_Player2_name));
	txt4.set_Text_Color(sf::Color::Red);
	mTexts.insert(std::pair<Qua::Quata_Texts, Quata_UI_Text>(Qua::txt_Player2_name, txt4));

}

std::deque<Quata_UI_Objects*> Quata_UI_Manager::pass_pointers()
{
	std::deque<Quata_UI_Objects*>	temp_deque;
	Quata_UI_Objects*				temp_ptr;
	for (auto& it : mTexts)
	{
		temp_deque.push_back(&it.second);
	}
	for (auto& it : mScores)
	{
		temp_deque.push_back(&it.second);
	}

	if (is_SplashScreen_on)
	{
		temp_ptr = pSplashScreen.get();
		temp_deque.push_back(std::move(temp_ptr));
	}

	if (is_pause_on)
	{
		temp_ptr = pPause.get();
		temp_deque.push_back(std::move(temp_ptr));;
	}
	
	return temp_deque;
}

void Quata_UI_Manager::change_score(Qua::Quata_UI_Components type)
{
	if (type == Qua::cu_Score1 || type == Qua::cu_Score2)
	{
		std::string new_score = std::to_string(mData.get_Score(type));
		mScores.at(type).refresh_Text(new_score);
	}
}

void Quata_UI_Manager::create_Pause()
{
	pPause.reset(new Quata_Pause(mData));
	is_pause_on = true;
}

void Quata_UI_Manager::pause_interact(sf::Vector2f mouse_pos)
{
	if (is_pause_on)
	{
		pPause->interact(mouse_pos);
	}
}

const bool  Quata_UI_Manager::is_mouse_hovering_in_pause() const
{
	if (is_pause_on)
	{
		return pPause->is_hovering();
	}
	return false;
}

const Qua::Button_Selection Quata_UI_Manager::pause_response() const
{
	if (is_pause_on)
	{
		return pPause->response();
	}
	return Qua::None;
}

void Quata_UI_Manager::delete_Pause()
{
	pPause.release();
	is_pause_on = false;
}

void Quata_UI_Manager::create_SplashScreen(std::string param)
{
	pSplashScreen.reset(new Quata_SplashScreen(mData, param));
	is_SplashScreen_on = true;
}

void Quata_UI_Manager::delete_SplashScreen()
{
	pSplashScreen.release();
	is_SplashScreen_on = false;
}
