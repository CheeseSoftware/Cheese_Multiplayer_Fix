#ifdef CLIENT

#include <iostream>

#include "GameClient.h"
#include "GameState.h"
#include "App.h"
#include "PlayState.h"
#include "MainMenu.h"
#include "TextureContainer.h"

int GameClient::LoadGameTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0)
{
	if (spriteWidth == 0 && spriteHeight == 0)
		return textureContainer->AddTexture("textures\\game\\" + path, 0);
	else
		return textureContainer->AddSpriteSheet("textures\\game\\" + path, spriteWidth, spriteHeight);
}

int GameClient::LoadGameSound(std::string path)
{
	return soundHandler->LoadSound("audio\\game\\" + path);
}

// Public:	*	*	*	*	*	*	*	*	*	*	*	*

GameClient::GameClient()
{

}

GameClient::~GameClient()
{

}


void GameClient::Run()
{
	app = new App(sf::VideoMode(1152,720));

	m_gameState = nullptr;
	Restart();

	while (app->isOpen())
	{
		sf::Event event;
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
			

			m_gameState->EventUpdate(*app, *this, event);
			// Pass the event to all the objects (if there would be objects)
            //app.handleEvent(event);
		}

		app->Update(); 
		m_gameState->Update(*app, *this);

		app->clear();

		m_gameState->Draw(*app);

		app->display();
	}

}

void GameClient::Exit()
{
	m_gameState = nullptr;
}

void GameClient::Restart()
{
	if (m_gameState)
		delete m_gameState;

	m_gameState = new MainMenu(this);//new PlayState(*app);//
}

#pragma region texturures_Sounds_fonts_scripts
	int GameClient::LoadTexture(std::string path, int spriteWidth = 0, int spriteHeight = 0)
	{
		if (spriteWidth == 0 || spriteHeight == 0)
			return textureContainer->AddTexture("textures\\" + path, 0);
		else
			return textureContainer->AddSpriteSheet("textures\\" + path, spriteWidth, spriteHeight); 
	}

	int GameClient::LoadSound(std::string path)
	{
		return soundHandler->LoadSound("audio\\" + path);
	}


	int GameClient::ReloadGameTexture(int id, std::string path, int spriteWidth = 0, int spriteHeight = 0)
	{
		return id;
	}

	int GameClient::ReloadGameSound(int id, std::string path)
	{
		return id;
	}


	void GameClient::DrawTexture(int id, double x, double y)
	{
		app->draw(textureContainer->getTextures(id));
	}

	void GameClient::PlaySound(void *source, int id, float volume, bool loop, std::function<sf::Vector2f()> position = nullptr)
	{
		if (position)
			soundHandler->PlaySound(app, source, id, volume, loop, position);
		else
			soundHandler->PlaySound(app, source, id, volume, loop);
	}

	void GameClient::PlayMusic(void *source, std::string path, float volume, bool loop, std::function<sf::Vector2f()> position = nullptr)
	{
		if (position)
			soundHandler->PlayMusic(app, source, "audio\\music\\" + path, volume, loop, position);
		else
			soundHandler->PlayMusic(app, source, "audio\\music\\" + path, volume, loop);
	}

#pragma endregion 
#endif