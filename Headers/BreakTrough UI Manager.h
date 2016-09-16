#ifndef BREAKTROUGH_UI_MANAGER_H
#define BREAKTROUGH_UI_MANAGER_H

#include "BreakTrough UI Objects.h"
#include "BreakTrough Active PowerUps.h"
#include "BreakTrough Lives.h"
#include "BreakTrough Overlay Text.h"
#include "BreakTrough Score.h"
#include "BreakTrough Pause.h"
class BreakTrough_Data;

class BreakTrough_UI_Manager
{
	BreakTrough_Data&		mData;
	BrkTr_UI_Lives			mLives;
	BrkTr_UI_Score			mScore;
	BrkTr_Active_PowerUps		mActivePower_Ups;

	std::unique_ptr<BrkTr_Overlay>			pOverlay;
	std::unique_ptr<BreakTrough_Pause>		pPause;
	
	bool					show_overlay, show_pause;
public:
	BreakTrough_UI_Manager(BreakTrough_Data&);
	std::deque<BrkTr_UI_Objects*>		pass_pointers();
	void			show_or_hide_Overlay(bool);
	void			set_Overlay_text(std::string);
	void			update(sf::Time&);

	void			add_life();
	void			remove_life();
	
	void			show_or_hide_Pause(bool);
	void			interact_pause(sf::Vector2f);
	const bool		is_mouse_hovering_in_pause_menu() const;
	const Break::Button_Selection	Pause_response() const;

	void			add_PowerUp(Break::PowerUp_ID);
	void			remove_all_PowerUps();
	
	const float		get_remaining_PowerUp_time(Break::PowerUp_ID) const;

	void			change_score(UINT param);	
};
#endif
