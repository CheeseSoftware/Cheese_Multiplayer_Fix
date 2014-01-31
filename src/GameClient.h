#ifdef CLIENT
#pragma once

#include "Game.h"

class GameClient : public Game
{
	App *app;

protected:
#pragma region texturures_Sounds_fonts_scripts
	TextureContainer *textureContainer;
	SoundHandler *soundHandler;

	virtual int LoadGameTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0);
	virtual int LoadGameSound(std::string path);
	//virtual int LoadMusic(std::string)=0;
#pragma endregion

public:
	GameClient();
	~GameClient();

	virtual void Run();
	virtual void Exit();
	virtual void Restart();

#pragma region texturures_Sounds_fonts_scripts
	virtual int LoadTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0);
	virtual int LoadSound(std::string path);

	virtual int ReloadGameTexture(int id, std::string path, int spriteWidth = 0, int spriteHeight = 0);
	virtual int ReloadGameSound(int id, std::string path);
#ifdef CLIENT
	virtual void DrawTexture(int id, double x, double y);
	virtual void PlaySound(void *source, int id, float volume, bool loop, std::function<sf::Vector2f()> = nullptr);
	virtual void PlayMusic(void *source, std::string path, float volume, bool loop, std::function<sf::Vector2f()> = nullptr);
	//virtual void ExecuteScript(int id)=0;
#else

#endif
#pragma endregion 
};
#endif