#pragma once

#ifdef _SERVER
#include <SFML\System.hpp>
#else
#include <SFML\Graphics.hpp>
//#include <TGUI/TGUI.hpp>
#endif

#define APP(a) (*reinterpret_cast<App*>(&a))

class App
#ifndef _SERVER
	: public sf::RenderWindow
#endif
{
	sf::Clock frameTimer;
	float frameTime;
#ifdef _SERVER
	float sleptTime;
#endif
public:
#ifndef _SERVER
	App(sf::VideoMode);
#endif
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