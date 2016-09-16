#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "StateCategory.h"
#include "Resources.h"
class Data;

class MusicPlayer
{
	Data*					mData;
	ID						mMusicState, mPreviousMusicState;
	sf::Music				mMusic;
	bool					is_music_playing;
	void					Play_Music(ID);
	float					stored_volume;
	bool					is_volume_decreasing;
public:
	MusicPlayer(Data*);
	void					Music_function(ID);
	void					Refresh_volume();
	void					Change_Music_status(bool);
	const bool				is_Music_Playing() const;

};


#endif
