#pragma once

#ifdef _SERVER
#include <SFML\System.hpp>
#else
#include <SFML\Graphics.hpp>
#endif

//#define APP(a) (*reinterpret_cast<App*>(&a))

#ifdef _SERVER
#define SERVER(...) __VA_ARGS__
#define CLIENT(VOID)
#else
#define SERVER(VOID)
#define CLIENT(...) __VA_ARGS__
#endif

class App
CLIENT(: public sf::RenderWindow)
{
	sf::Clock frameTimer;
	float frameTime;
SERVER(
	float sleptTime;)

public:
CLIENT(
	App(sf::VideoMode);)

	float getFrameTime();
	float getDeltaTime();

	void Update();
	sf::Clock &getFrameTimer();
};
//#else
//#include <SFML\Graphics.hpp>
//typedef sf::RenderWindow App;
//#define APP(a) a
//#endif