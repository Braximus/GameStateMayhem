#include "stdafx.h"
#include "MusicPlayer.h"
#include "DataStorage.h"

MusicPlayer::MusicPlayer(Data* dat)
	:mData(dat)
{	
	mMusicState = ID_Menu;
	mPreviousMusicState = ID_Global;
	is_music_playing = true;
	is_volume_decreasing = false;
};

void MusicPlayer::Play_Music(ID param)
{

	if (!mMusic.openFromFile(mData->getResources().getMusicTitle(param)))
	{
		std::cout << "No music track!" << std::endl;
	};
	mMusic.setLoop(true);
	mMusic.play();

	if (param == ID::ID_BreakTrough)
	{
		mMusic.stop();
	}

}

void MusicPlayer::Music_function(ID param)
{
	if (is_music_playing)
	{
		mMusicState = param;
		if (mPreviousMusicState != mMusicState)
		{
			if (!is_volume_decreasing)
			{
				is_volume_decreasing = true;
			}
			stored_volume = mMusic.getVolume();
			stored_volume -= 1;
			if (stored_volume <= 0)
			{
				stored_volume = 0;
				mPreviousMusicState = mMusicState;
				Play_Music(param);
				is_volume_decreasing = false;
			}
			mMusic.setVolume(stored_volume);						
		}

		if (!is_volume_decreasing)
		{
			stored_volume += 1;
			if (stored_volume >= mData->getResources().getMusicVolume())
			{
				stored_volume = mData->getResources().getMusicVolume();
				is_volume_decreasing = true;
			}
			mMusic.setVolume(stored_volume);
		}
	}
}

void MusicPlayer::Refresh_volume()
{
	mMusic.setVolume(mData->getResources().getMusicVolume());
}

void MusicPlayer::Change_Music_status(bool is_playing)
{
	is_music_playing = is_playing;
	if (!is_music_playing)
	{
		mMusic.setVolume(0);
		stored_volume = 0;
		is_volume_decreasing = false;
		mMusic.stop();
	}
	else
	{
		Play_Music(mMusicState);
	}
}

const bool MusicPlayer::is_Music_Playing() const
{
	return is_music_playing;

}
