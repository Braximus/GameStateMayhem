#ifndef CREDITS_H
#define CREDITS_H

#include "Menu_Substates_Base_Class.h"
#include "Label.h"
#include "Buttons.h"

class MenuData;

class Credits : public Menu_SubStates
{
	enum Selection
	{
		None,
		Back
	} mCurrentSelection, mPreviousSelection;


	MenuData&		mData;
	Button			mBack;
	Label			mLabel;

public:
	explicit		Credits(MenuData& data);
	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void					update(sf::Time&);
	void					handleEvents(sf::Event&);
	void					handleRealTimeInput();
	void					refresh();


};






#endif