#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "StateCategory.h"
#include "Resources.h"
class Data;

//		Ova klasa sluzi samo za pustanje muzike u zavisnosti od trenutnog stanja aplikacije, ali je autonomna u odnosu na njih, tj.
//		klasa pazi koje je trenutno stanje i na osnovu toga menja svoje stanje kada je potrebno. Klasa menja muziku samo kada njeno
//		stanje to omoguci.


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