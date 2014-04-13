#ifdef CLIENT
#pragma once

#include "Game.h"
#include "SoundHandler.h"
#include "TextureContainer.h"

class GameClient : public Game, virtual SoundHandler, public TextureContainer
{
	App *app;

protected:
#pragma region texturures_Sounds_fonts_scripts
	//TextureContainer *textureContainer;
	//SoundHandler *soundHandler;

	//virtual int LoadGameTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0);
	//virtual int LoadGameSound(std::string path);
	//virtual int LoadMusic(std::string)=0;
#pragma endregion

public:
	GameClient();
	~GameClient();

	virtual void Run();
	virtual void Exit();
	virtual void Restart();

#pragma region texturures_Sounds_fonts_scripts
//	virtual bool LoadSound(std::string) override;
//	virtual bool LoadMusic(std::string) override;
#ifdef CLIENT
	//virtual SSound *PlaySound(App &app, void *source, std::string name, float volume, bool loop) override;
	//virtual SSound *PlaySound(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position) override;
	//virtual SMusic *PlayMusic(App &app, void *source, std::string name, float volume, bool loop) override;
	//virtual SMusic *PlayMusic(App &app, void *source, std::string name, float volume, bool loop, std::function<sf::Vector2f()> position) override;

	//virtual void stopSounds(void *source) override;

	//virtual void setVolume(float volume) override;
	//virtual float getVolume()=0;
#else
//...
#endif
#pragma endregion 
};
#endif