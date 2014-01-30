#ifdef CLIENT
#pragma once
//#include <SFML\Audio.hpp>
#include <vector>
#include <map>
#include <string>

#include "SSound.h"
#include "SMusic.h"

class App;

class SoundHandler
{
	std::map<std::string, sf::SoundBuffer*> m_soundBufferContainer;

	std::map<void*, std::vector<SSound*>> m_soundContainer;
	std::map<void*, std::vector<SMusic*>> m_musicContainer;

	std::map<void*, std::pair<std::function<sf::Vector2f()>,std::vector<SSound*>>> m_posSoundContainer;
	std::map<void*, std::pair<std::function<sf::Vector2f()>, std::vector<SMusic*>>> m_posMusicContainer;

	float m_volume;

	float CalculateVolume(const sf::Vector2f &a, const sf::Vector2f &b);
public:
	SoundHandler();
	~SoundHandler();

	void Update(const sf::Vector2f &position);

	bool LoadSound(std::string);

	SSound *PlaySound(App &app, void *source, std::string name, float volume, bool loop);
	SSound *PlaySound(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position);
	SMusic *PlayMusic(App &app, void *source, std::string name, float volume, bool loop);
	SMusic *PlayMusic(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position);

	//void moveSounds(void *source, sf::Vector2f);
	void stopSounds(void *source);

	//getSoundId() //bra för att skicka ljudpacket?

	void setVolume(float volume);
	float getVolume();
};
#endif