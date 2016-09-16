#ifndef RESOURCES_H
#define RESOURCES_H


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
	//------Textures------//
	std::map<ID, sf::Texture>		mTextures;
	//--------Font--------//
	std::map<ID, sf::Font>			mFont;
	//-------Music-------//

	std::map<ID, std::string>		mMusic_Title;
	float					mMusicVolume;
	const unsigned int			getMusicContainerSize() const;
	void					LoadMusicTitles();
	//-------Sounds--------//
	std::map<std::string, sf::SoundBuffer>	mSoundBuffers;	
	float					mSoundVolume;
	bool					is_sound_on;
public:
	Resources();
	//------Textures------//
	void							LoadTexture(const std::string& name, ID id);
	void							UnloadTexture(ID);
	const sf::Texture&				getTexture(ID id) const;
	//--------Font--------//
	const sf::Font&					getFont(ID id) const;
	void							LoadFont(const std::string& name, ID id);
	void							UnloadFont(ID);
	//-------Music-------//
	const float						getMusicVolume() const;
	void							setMusicVolume(float);
	const std::string				getMusicTitle(ID) const;
	//-------Sounds--------//
	const bool						IsSoundOn() const;
	void							SoundSwitch(bool);
	const sf::SoundBuffer&			getSoundBuffer(const std::string& name) const;
	const float						getSoundVolume() const;
	void							setSoundVolume(float);
	void							LoadSound(const std::string& name);
	void							UnloadSounds();	
};
#endif
