#pragma once
#include <string>
#include <functional>
#include <SFML\Network.hpp>

#include "SSound.h"
#include "SMusic.h"

#include "MessageType.h"

class App;

class ISoundHandler
{
public:
	virtual bool LoadSound(std::string)=0;
	virtual bool LoadMusic(std::string)=0;

/*#ifdef SERVER
	virtual std::map<std::string, std::string> getSoundFiles()=0;
	virtual std::map<std::string, std::string> getMusicFiles()=0
#endif*/

#ifdef SERVER
	inline sf::Packet &operator<<(sf::Packet &packet)
	{
		packet << MessageType::SoundHandlerInit
	}
#else
	virtual SSound *PlaySound(App &app, void *source, std::string name, float volume, bool loop)=0;
	virtual SSound *PlaySound(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position)=0;
	virtual SMusic *PlayMusic(App &app, void *source, std::string name, float volume, bool loop)=0;
	virtual SMusic *PlayMusic(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position)=0;

	virtual void stopSounds(void *source)=0;

	virtual void setVolume(float volume)=0;
	virtual float getVolume()=0;
#endif
};