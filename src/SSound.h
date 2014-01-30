#ifdef CLIENT
#pragma once
#include <SFML\Audio.hpp>

struct SSound
{
	sf::Sound sound;
	float volume;
};
#endif