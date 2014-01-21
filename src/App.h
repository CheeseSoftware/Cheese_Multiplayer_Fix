#pragma once

#ifdef SERVER
#include <SFML\System.hpp>
#else
#include <SFML\Graphics.hpp>
#endif

//#define APP(a) (*reinterpret_cast<App*>(&a))

#ifdef SERVER
#define SERVER_(...) __VA_ARGS__
#define CLIENT_(VOID)
#else
#define SERVER_(VOID)
#define CLIENT_(...) __VA_ARGS__
#endif

class App
CLIENT_(: public sf::RenderWindow)
{
	sf::Clock frameTimer;
	float frameTime;
SERVER_(
	float sleptTime;)

public:
CLIENT_(
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