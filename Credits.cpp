#include "stdafx.h"
#include "Credits.h"
#include "Menu_Data.h"

Credits::Credits(MenuData& data)
	:mData(data)
{
	mCurrentSelection = None;
	mPreviousSelection = None;
	refresh();

}


void Credits::draw(sf::RenderTarget& target, sf::RenderStates state)  const
{
	state.transform *= getTransform();
	state.texture = NULL;
	target.draw(mLabel, state);
	target.draw(mBack, state);
}

void Credits::update(sf::Time&)
{
	if (!mData.mRefreshed)
	{
		refresh();
	}
	if (mCurrentSelection != mPreviousSelection)
	{
		if (mCurrentSelection != None)
		{
			mData.Play_Sound(Menus::snd_Hover);
		}
		mPreviousSelection = mCurrentSelection;
	}
}

void Credits::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			mData.ChangeSubState(Menus::Main_Menu);
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{

		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mCurrentSelection == Back)
			{
				mData.Play_Sound(Menus::snd_Escape);
				mData.ChangeSubState(Menus::Main_Menu);
			}
		}
	}
	


}

void Credits::handleRealTimeInput()
{
	bool is_it_outside = true;
	if (mBack.check_Bounds((static_cast<sf::Vector2f>(mData.MouseCoord()))))
	{
		is_it_outside = false;
		mBack.ToggleSelection_ByColor(true);
		mCurrentSelection = Back;
	}
	else
	{
		mBack.ToggleSelection_ByColor(false);
	}


	if (is_it_outside)
	{
		mCurrentSelection = None;
	}
}

void Credits::refresh()
{
	sf::Color color = sf::Color(32, 128, 128, 128);
	
	mBack = Button(" Back", mData.getResources().getFont(ID_Global), mData.getMenu_Char_Sizes(Menus::ch_Medium));
	mBack.set_Size(mData.getMenu_Object_Sizes(Menus::size_Button));
	mBack.set_Position(sf::Vector2f((mData.getMenu_Object_Sizes(Menus::size_Button).x / 2) + mData.getMenu_Distances(Menus::dis_Long), mData.getMenu_Key_Positions(Menus::kp_BottomLeft_Corner).y - (mData.getMenu_Distances(Menus::dis_Long) + mData.getMenu_Distances(Menus::dis_Near) + (mData.getMenu_Object_Sizes(Menus::size_Button).y / 2))));
	mBack.set_Bounds();
	mBack.set_Colors(color, sf::Color::Cyan);

	mLabel = Label(mData.getResources().getFont(ID_Global), " Music Used: \n Trevor Lentz - Lines of Code\n Kim Lightyear - Starlight\n Music was downloaded from Opengameart.org.\n\n I made sound effects using ChipTone web program.\n" ,mData.getMenu_Char_Sizes(Menus::ch_Small));
	mLabel.set_Size(mData.getMenu_Object_Sizes(Menus::size_HugeLabel));
	mLabel.set_Position(sf::Vector2f( mData.getMenu_Distances(Menus::dis_Long) + mData.getMenu_Object_Sizes(Menus::size_HugeLabel).x / 2, mData.getMenu_Object_Sizes(Menus::size_HugeLabel).y));
	mLabel.set_Color(sf::Color::Cyan, sf::Color::Cyan);

	mData.mRefreshed = true;
}