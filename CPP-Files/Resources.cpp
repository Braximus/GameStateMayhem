#include "stdafx.h"
#include "Resources.h"

Resources::Resources()
{
	//	Global resoures are loaded in constructor and last as long as the program works.
	LoadFont("Font/OpenSans-Regular.ttf", ID_Global);
	LoadTexture("Teksture/Cursors.png", ID_Global);
	setMusicVolume(50);
	LoadMusicTitles();
	setSoundVolume(80);
	is_sound_on = true;
}

//------Texture------//

void Resources::LoadTexture(const std::string& name, ID id)
{
	sf::Texture texture;
	if (!texture.loadFromFile(name))
	{
		std::cerr << "Error loading texutre!" << std::endl;		
	}
	else
	{
		texture.setSmooth(true);
		mTextures.insert(std::pair<ID, sf::Texture>(id, texture));
	}
}

void Resources::UnloadTexture(ID id)
{
	mTextures.erase(id);
}

const sf::Texture& Resources::getTexture(ID id) const
{
	return mTextures.find(id)->second;
}

//--------Font--------//

void Resources::LoadFont(const std::string& name, ID id)
{
	sf::Font font;
	if (!font.loadFromFile(name))
	{
		std::cerr << "Error loading font" << std::endl;
	}
	else
	{
		mFont.insert(std::pair<ID, sf::Font>(id, font));
	}
}

void Resources::UnloadFont(ID id)
{
	mFont.erase(id);
}

const sf::Font& Resources::getFont(ID id) const
{
	return mFont.find(id)->second;
}

//-------Music-------//

void Resources::LoadMusicTitles()
{
	//	All music tracks will be loaded on start of the program.
	mMusic_Title.insert(std::pair<ID, std::string>(ID_Menu, "Sounds/Trevor Lentz - Lines of code.flac"));
	mMusic_Title.insert(std::pair<ID, std::string>(ID_Global, "Sounds/Trevor Lentz - Lines of code.flac"));
	mMusic_Title.insert(std::pair<ID, std::string>(ID_CometWars, "Sounds/Kim Lightyear - Starlight.flac"));
	mMusic_Title.insert(std::pair<ID, std::string>(ID_Quata, "Sounds/Kim Lightyear - Starlight.flac"));
	mMusic_Title.insert(std::pair<ID, std::string>(ID_BreakTrough, "Sounds/Trevor Lentz - Lines of code.flac"));
}

const float Resources::getMusicVolume() const
{
	return mMusicVolume;
}

void Resources::setMusicVolume(float vol)
{
	mMusicVolume = vol;
}

const unsigned int Resources::getMusicContainerSize() const
{
	return mMusic_Title.size();
}

const std::string Resources::getMusicTitle(ID param) const
{
	return mMusic_Title.at(param);
}


void Resources::LoadSound(const std::string& name)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(name))
	{
		std::cerr << "Error loading sound into sound buffer" << std::endl;
	}
	else
	{
		mSoundBuffers.insert(std::pair<std::string, sf::SoundBuffer>(name, buffer));
	}
}

void Resources::UnloadSounds()
{
	mSoundBuffers.clear();
}

const bool Resources::IsSoundOn() const
{
	return is_sound_on;
}

void Resources::SoundSwitch(bool param)
{
	is_sound_on = param;
}

const sf::SoundBuffer& Resources::getSoundBuffer(const std::string& name) const
{
	return mSoundBuffers.find(name)->second;
}

void Resources::setSoundVolume(float vol)
{
	mSoundVolume = vol;
}

const float Resources::getSoundVolume() const
{
	return mSoundVolume;
}
