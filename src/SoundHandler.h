#ifndef _SERVER
#pragma once
#include <SFML\Audio.hpp>
#include <vector>
#include <map>
#include <string>

class SoundHandler
{
	std::map<std::string, sf::SoundBuffer*> soundBufferContainer;

	std::map<void*, std::vector<sf::Sound*>> soundContainer;
	std::map<void*, std::vector<sf::Music*>> musicContainer;
public:
	SoundHandler();
	~SoundHandler();

	void Update();
	bool LoadSound(std::string);
	sf::Sound *PlaySound(void *source, std::string name, bool loop);
	sf::Music *PlayMusic(void *source, std::string name, bool loop);
	void stopSounds(void *source);
};
#endif