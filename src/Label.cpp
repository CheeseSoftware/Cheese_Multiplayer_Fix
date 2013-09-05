#ifndef _SERVER
#include <SFML\Graphics.hpp>
#include "MenuItem.h"
#include "Label.h"
#include "GameState.h"


Label::Label(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent, std::string text) : MenuItem(x, y, width, height, clickEvent)
{

}


Label::~Label()
{

}

GameState *Label::EventUpdate(App& app, const sf::Event& event, GameUtilityInterface* gameUtilityInterface)
{
	return MenuItem::EventUpdate(app, event, gameUtilityInterface);
}

void Label::Draw(App &app)
{

}
#endif