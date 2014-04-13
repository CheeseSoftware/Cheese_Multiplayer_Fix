#pragma once
//#include <SFML\Audio.hpp>
#include <vector>
#include <map>
#include <string>

#include "ISoundHandler.h"
#ifdef CLIENT
#include "SSound.h"
#include "SMusic.h"
#endif

class App;
class ISoundable;

class SoundHandler : public virtual ISoundHandler
{
#ifdef CLIENT
	std::map<std::string, sf::SoundBuffer*> m_soundBufferContainer;

	std::map<ISoundable*, std::vector<SSound*>> m_soundContainer;;
	std::map<ISoundable*, std::vector<SMusic*>> m_musicContainer;

	float m_volume;

	//float CalculateVolume(const sf::Vector2f &a, const sf::Vector2f &b);
	float CalculateVolume(float distance) const;
#endif
public:
	SoundHandler();
	~SoundHandler();

	virtual void UpdateSounds(const sf::Vector2f &position) override;

	virtual bool LoadSound(std::string) override;

#ifdef CLIENT
	virtual SSound *PlaySound(App &app, ISoundable *source, std::string name, float volume, bool loop) override;
	virtual SMusic *PlayMusic(App &app, ISoundable *source, std::string name, float volume, bool loop) override;
	//void moveSounds(void *source, sf::Vector2f);
	virtual void stopSounds(ISoundable *source) override;

	//getSoundId() //bra för att skicka ljudpacket?

	virtual void setVolume(float volume) override;
	virtual float getVolume() override;
#endif
};