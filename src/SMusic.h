#ifdef CLIENT
#pragma once
#include <SFML\Audio.hpp>

struct SMusic
{
	sf::Music music;
	float volume;
};
#endif