#ifndef APPLICATION_H
#define APPLICATION_H


#include "Debug.h"
#include "DataStorage.h"
#include "MusicPlayer.h"
#include "StateManager.h"
#include "State.h"
#include "User.h"

class App
{
	sf::RenderWindow				mWindow;				
	sf::Event					mEvent;					
	sf::Time					mTimeSinceLastUpdate;	
	sf::Time					mCurrentTime;
	sf::Clock					Clock;
	static const sf::Time				mFixedTime;				
	//--------------------------//
	DebugClass					mDebug;					
	//--------------------------//
	Data						mData;					
	//--------------------------//
	StateManager					mState;					
	//--------------------------//
	User						mUser;					
public:
	App();
	void						run();
	void						update(sf::Time mFixedTime);
	void						eventProcess();
	void						render();
};

#endif
