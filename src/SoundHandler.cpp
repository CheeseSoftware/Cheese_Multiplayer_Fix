#ifdef CLIENT
#include "SoundHandler.h"

SoundHandler::SoundHandler()
{

}

SoundHandler::~SoundHandler()
{
	/*for (auto soundVector : soundContainer)
	{
		for (auto s: soundVector.second)
		{
			delete s;
		}
	}

	for (auto musicVector : musicContainer)
	{
		for (auto s: musicVector.second)
		{
			delete s;
		}
	}*/

}

void SoundHandler::Update()
{

}

bool LoadSound(std::string name)
{
	return false;
}

sf::Sound *SoundHandler::PlaySound(void *source, std::string name, bool loop)
{
	//auto soundBuffer = soundBufferContainer.find(name);

	//if (soundBuffer != soundBufferContainer.end())
	{
		//sf::Sound *sound = new sf::Sound(soundBuffer->second);
		//sound->setLoop(loop);
		//sound->play();
		//soundContainer[source].push_back(sound);
		//return sound;
	}
	return nullptr;
}

sf::Music *SoundHandler::PlayMusic(void *source, std::string name, bool loop)
{
	//sf::Music *music;// = new sf::Music();
	//if (music->openFromFile(name))
	{
		//music->setLoop(loop);
		//music->play();
		//return music;
	}
	return nullptr;
}

void SoundHandler::stopSounds(void *source)
{

}
#endif