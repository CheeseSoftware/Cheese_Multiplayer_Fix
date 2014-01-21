//#ifdef SERVER
#include "App.h"

#define MIN_FRAME_TIME 0.00390625F

CLIENT_(
App::App(sf::VideoMode videoMode) : sf::RenderWindow(videoMode, "Cheese Multiplayer - Alpha")//tgui::Window(videoMode, "Cheese Multiplayer - Alpha")
{
	//globalFont.loadFromFile("TGUI/Fonts/DejaVuSans.ttf");
})

float App::getFrameTime()
{
	//std::cout << frameTime << " " << sleptTime << std::endl;
#ifdef SERVER
	return (frameTime/*+sleptTime*/);
#else
	return (frameTime);
#endif
}

float App::getDeltaTime()
{

	float frameTime2 = getFrameTime();
	return ((frameTime2 > 0.02F)? 0.02F : frameTime2);
}

void App::Update()
{
	long time = 1000000/120-frameTimer.getElapsedTime().asMicroseconds();
	if (time > 0)
		sf::sleep(sf::Time(sf::milliseconds(time/1000)));
	frameTime = frameTimer.getElapsedTime().asSeconds();
	
/*SERVER_(
	if (frameTime < MIN_FRAME_TIME)
	{
		sleptTime = MIN_FRAME_TIME-frameTime;
		sf::sleep(sf::milliseconds(sleptTime));
	}
	else
	{
		sleptTime = 0;
	})*/

	frameTimer.restart();
}


sf::Clock& App::getFrameTimer()
{
	return frameTimer;
}