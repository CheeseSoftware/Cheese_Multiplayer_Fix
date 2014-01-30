#ifdef CLIENT
#include <SFML\Audio.hpp>
#include <functional>

#include "SoundHandler.h"
#include "App.h"


SoundHandler::SoundHandler()
{

}

SoundHandler::~SoundHandler()
{
	for (auto soundVector : m_soundContainer)
	{
		for (auto s: soundVector.second)
		{
			//s->sound.stop();
			delete s;
		}
	}

	for (auto soundVector : m_posSoundContainer)
	{
		for (auto s: soundVector.second.second)
		{
			delete s;
		}
	}

	for (auto musicVector : m_musicContainer)
	{
		for (auto s: musicVector.second)
		{
			s->music.stop();
			delete s;
		}
	}

	for (auto musicVector : m_posMusicContainer)
	{
		for (auto s: musicVector.second.second)
		{
			delete s;
		}
	}

	for (auto soundBuffer : m_soundBufferContainer)
	{
		delete soundBuffer.second;
	}

}

float SoundHandler::CalculateVolume(const sf::Vector2f &a, const sf::Vector2f &b)
{
	float deltaX = a.x - b.x;
	float deltaY = a.y - b.y;
	float volume = 128.f*sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	volume = (volume < 1.f)? m_volume:m_volume*volume;
	return volume;
}

//public:

void SoundHandler::Update(const sf::Vector2f &position)
{
	for (auto soundVector : m_soundContainer)
	{
		for(auto rit = soundVector.second.rbegin(); rit != soundVector.second.rend(); ++rit)
		{
			if ((*rit)->sound.getStatus() == sf::SoundSource::Status::Stopped)
			{
				delete *rit;
				soundVector.second.erase(--(rit.base()));
			}
		}
	}

	for (auto soundVector : m_posSoundContainer)
	{
		for(auto rit = soundVector.second.second.rbegin(); rit != soundVector.second.second.rend(); ++rit)
		{
		//for (auto s: soundVector.second.second)
		//{
			if ((*rit)->sound.getStatus() == sf::SoundSource::Status::Stopped)
			{
				(*rit)->sound.stop();
				delete (*rit);
				soundVector.second.second.erase(--(rit.base()));
				continue;
			}

			(*rit)->sound.setVolume((*rit)->volume*CalculateVolume(position, soundVector.second.first()));
		}
	}

	for (auto musicVector : m_musicContainer)
	{
		for(auto rit = musicVector.second.rbegin(); rit != musicVector.second.rend(); ++rit)
		{
			if ((*rit)->music.getStatus() == sf::SoundSource::Status::Stopped)
			{
				delete *rit;
				musicVector.second.erase(--(rit.base()));
			}
		}
	}

	for (auto musicVector : m_posMusicContainer)
	{
		for(auto rit = musicVector.second.second.rbegin(); rit != musicVector.second.second.rend(); ++rit)
		{
			if ((*rit)->music.getStatus() == sf::SoundSource::Status::Stopped)
			{
				delete *rit;
				musicVector.second.second.erase(--(rit.base()));
				continue;
			}

			(*rit)->music.setVolume((*rit)->volume*CalculateVolume(position, musicVector.second.first()));
		}
	}
}

bool SoundHandler::LoadSound(std::string name)
{
	if (m_soundBufferContainer.find(name) == m_soundBufferContainer.end())
	{
		sf::SoundBuffer *soundBuffer = new sf::SoundBuffer;

		if (soundBuffer->loadFromFile("audio\\" + name))
		{
			m_soundBufferContainer.insert(std::pair<std::string, sf::SoundBuffer*>(name, soundBuffer));
		}
	}
}

SSound *SoundHandler::PlaySound(App &app, void *source, std::string name, float volume, bool loop)
{
	auto soundBuffer = m_soundBufferContainer.find(name);

	if (soundBuffer != m_soundBufferContainer.end())
	{
		SSound *sound = new SSound();
		sound->sound = sf::Sound(*soundBuffer->second);
		sound->sound.setLoop(loop);
		sound->sound.setVolume(volume*m_volume);
		sound->sound.play();

		sound->volume = volume;

		if (m_soundContainer.find(source) == m_soundContainer.end())
			m_soundContainer.insert(std::pair<void*,std::vector<SSound*>>(source, std::vector<SSound*>()));

		m_soundContainer[source].push_back(sound);
		return sound;
	}

	return nullptr;
}

SSound *SoundHandler::PlaySound(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position)
{
	auto soundBuffer = m_soundBufferContainer.find(name);
	sf::Vector2f pos = position();

	if (soundBuffer != m_soundBufferContainer.end())
	{
		SSound *sound = new SSound();
		sound->sound = sf::Sound(*soundBuffer->second);
		sound->sound.setLoop(loop);
		sound->sound.setVolume(volume*CalculateVolume(app.getView().getCenter(), pos));
		sound->sound.play();

		sound->volume = volume;

		if (m_posSoundContainer.find(source) == m_posSoundContainer.end())
			m_posSoundContainer.insert(std::pair<void*,std::pair<std::function<sf::Vector2f()>,std::vector<SSound*>>>
			(source, std::pair<std::function<sf::Vector2f()>, std::vector<SSound*>>
				(position, std::vector<SSound*>())));

		m_posSoundContainer[source].second.push_back(sound);

		return sound;
	}

	return nullptr;
}

SMusic *SoundHandler::PlayMusic(App &app, void *source, std::string name, float volume, bool loop)
{
	SMusic *music = new SMusic();
	if (music->music.openFromFile(name))
	{
		music->music.setLoop(loop);
		music->music.setVolume(volume*m_volume);
		music->music.play();

		music->volume = volume;

		if (m_musicContainer.find(source) == m_musicContainer.end())
			m_musicContainer.insert(std::pair<void*,std::vector<SMusic*>>(source, std::vector<SMusic*>()));

		m_musicContainer[source].push_back(music);

		return music;
	}
	return nullptr;
}

SMusic *SoundHandler::PlayMusic(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position)//sf::Vector2f pos)
{
	SMusic *music = new SMusic();
	sf::Vector2f pos = position();
	if (music->music.openFromFile(name))
	{
		music->music.setLoop(loop);
		music->music.setVolume(volume*CalculateVolume(app.getView().getCenter(), pos));
		music->music.play();

		music->volume = volume;


		if (m_musicContainer.find(source) == m_musicContainer.end())
			m_posMusicContainer.insert(std::pair<void*,std::pair<std::function<sf::Vector2f()>,std::vector<SMusic*>>>
			(source, std::pair<std::function<sf::Vector2f()>, std::vector<SMusic*>>
				(position, std::vector<SMusic*>())));

		m_posMusicContainer[source].second.push_back(music);

		return music;
	}
	return nullptr;
}

void SoundHandler::stopSounds(void *source)
{

}

void SoundHandler::setVolume(float volume)
{
	m_volume = volume;

	for (auto soundVector : m_soundContainer)
	{
		for (auto s: soundVector.second)
		{
			s->sound.setVolume(s->volume*m_volume);
		}
	}

	for (auto musicVector : m_musicContainer)
	{
		for (auto s: musicVector.second)
		{
			s->music.setVolume(s->volume*m_volume);
		}
	}
}

float SoundHandler::getVolume()
{
	return m_volume;
}

#endif