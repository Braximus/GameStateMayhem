#ifndef RESOURCES_H
#define RESOURCES_H

//#include "SFML\Graphics.hpp"
//#include <memory>

enum ID
{
	ID_Global,
	ID_Menu,
	ID_Quata,
	ID_Quata_table,
	ID_CometWars,
	ID_BreakTrough
};


class Resources
{
	//------Teksture------//
	std::map<ID, sf::Texture>		mTextures;
	//--------Font--------//
	std::map<ID, sf::Font>			mFont;
	//-------Muzika-------//
	// Muziku cu detaljno da namestim kada bude doslo vreme, za sada neka bude ovako
	std::map<ID, std::string>			mMusic_Title;
	float							mMusicVolume;
	const unsigned int				getMusicContainerSize() const;
	void							LoadMusicTitles();
	//-------Zvuci--------//
	std::map<std::string, sf::SoundBuffer>	mSoundBuffers;	
	float									mSoundVolume;
	bool									is_sound_on;
public:
	Resources();
	//------Teksture------//
	void							LoadTexture(const std::string& name, ID id);
	void							UnloadTexture(ID);
	const sf::Texture&				getTexture(ID id) const;
	//--------Font--------//
	const sf::Font&					getFont(ID id) const;
	void							LoadFont(const std::string& name, ID id);
	void							UnloadFont(ID);
	//-------Muzika-------//
	const float						getMusicVolume() const;
	void							setMusicVolume(float);
	const std::string				getMusicTitle(ID) const;
	//--------Zvuci-------//
	const bool						IsSoundOn() const;
	void							SoundSwitch(bool);
	const sf::SoundBuffer&			getSoundBuffer(const std::string& name) const;
	const float						getSoundVolume() const;
	void							setSoundVolume(float);
	void							LoadSound(const std::string& name);
	void							UnloadSounds();	



};






#endif