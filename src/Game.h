#pragma once
#include <string>
#include <functional>
#include <SFML\System.hpp>

class GameState;
class App;

class Game :  ISoundHandler
{
protected:
	GameState *m_gameState;

#pragma region texturures_Sounds_fonts_scripts
	virtual int LoadGameTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0)=0;
	virtual int LoadGameSound(std::string path)=0;
	//virtual int LoadGameMusic(std::string)=0;
#pragma endregion
public:
	virtual void Run()=0;

	void SetGameState(GameState *gameState, bool keepMemory=false);
	virtual void Exit()=0;
	virtual void Restart()=0;

#pragma region texturures_Sounds_fonts_scripts
	virtual int LoadTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0)=0;
	virtual int LoadSound(std::string path)=0;
	//virtual int LoadMusic(std::string)=0;

	virtual int ReloadGameTexture(int id, std::string path, int spriteWidth = 0, int spriteHeight = 0)=0;
	virtual int ReloadGameSound(int id, std::string path)=0;
#ifdef CLIENT
	virtual void DrawTexture(int id, double x, double y)=0;
	virtual void PlaySound(void *source, int id, float volume, bool loop, std::function<sf::Vector2f()> = nullptr)=0;
	virtual void PlayMusic(void *source, std::string path, bool loop, std::function<sf::Vector2f()> = nullptr)=0;
#else


#endif
#pragma endregion
};