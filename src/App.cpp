//#ifdef _SERVER
#include "App.h"

#define MIN_FRAME_TIME 0.00390625F

#ifndef _SERVER
App::App(sf::VideoMode videoMode) : sf::RenderWindow(videoMode, "Cheese Multiplayer - Alpha")//tgui::Window(videoMode, "Cheese Multiplayer - Alpha")
{
	//globalFont.loadFromFile("TGUI/Fonts/DejaVuSans.ttf");
}
#endif

float App::getFrameTime()
{
	//std::cout << frameTime << " " << sleptTime << std::endl;
#ifdef _SERVER
	return (frameTime+sleptTime)/1000000;
#else
	return (frameTime)*0.000001;
#endif
}

float App::getDeltaTime()
{
	float frameTime = getFrameTime();

	return (frameTime > 0.1)? 0.1 : frameTime;
}

void App::Update()
{
	frameTime = frameTimer.getElapsedTime().asMicroseconds();

#ifdef _SERVER
	if (frameTime < MIN_FRAME_TIME)
	{
		sleptTime = MIN_FRAME_TIME-frameTime;
		sf::sleep(sf::milliseconds(sleptTime));
	}
	else
	{
		sleptTime = 0;
	}
#endif

	frameTimer.restart();
}


sf::Clock& App::getFrameTimer()
{
	return frameTimer;
}