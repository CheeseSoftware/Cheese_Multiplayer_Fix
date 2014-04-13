#pragma once
#include <string>
#include <functional>
#include <SFML\Network.hpp>

#include "SSound.h"
#include "SMusic.h"

#include "MessageType.h"

class App;
class ISoundable;

class ISoundHandler
{
public:
	virtual void UpdateSounds(const sf::Vector2f &position)=0;

	virtual bool LoadSound(std::string)=0;
	//virtual bool LoadMusic(std::string)=0;


#ifdef SERVER
	inline sf::Packet &operator<<(sf::Packet &packet)
	{
		packet << MessageType::SoundHandlerInit;
	}
#else
	virtual SSound *PlaySound(App &app, ISoundable *source, std::string name, float volume, bool loop)=0;
	virtual SMusic *PlayMusic(App &app, ISoundable *source, std::string name, float volume, bool loop)=0;

	virtual void stopSounds(ISoundable *source)=0;

	virtual void setVolume(float volume)=0;
	virtual float getVolume()=0;
#endif
};