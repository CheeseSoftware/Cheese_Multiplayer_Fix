#ifndef _SERVER

#include <iostream>
#include <vector>
#include "MainMenu.h"
#include "AMenuState.h"
#include <sstream>

#include "GameState.h"
#include "Label.h"
#include "Text.h"

MainMenu::MainMenu() : AMenuState()//void MainMenu::Initialize()
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";

	std::stringstream ss;
	ss << "Member of first" << std::endl;
	//pos = new gui::Label(50, 50, 200, 50, new sf::String(ss.str()), font, 10, 10);
	//sf::String *text = new sf::String("hello world");
	gui::Label *label = new gui::Label(50, 50, 200, 50, new sf::String(ss.str()), font, 10, 10);
	//label->setColor(sf::Color::Green);
	//label->setCharacterSize(12);
	//label->setStyle(0);
	menuItemContainer->Add(label);
}

MainMenu::~MainMenu()// : AMenuState()//void MainMenu::Shutdown()
{
	AMenuState::~AMenuState();
}

void MainMenu::EventUpdate(App &app, Game &game, const sf::Event &event)
{
    AMenuState::EventUpdate(app, game, event);
}

GameState *MainMenu::Update(App &app, Game &game)
{
    AMenuState::Update(app, game);
    return this;
}

void MainMenu::Draw(App &app)
{
	AMenuState::Draw(app);
    //MenuState::Draw(app);
    //menuItems.
}
#endif
