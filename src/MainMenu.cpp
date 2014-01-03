#ifndef _SERVER

#include <iostream>
#include <vector>
#include "MainMenu.h"
#include "MenuState.h"
#include "GameState.h"
#include "Label.h"
#include "Text.h"

MainMenu::MainMenu() : MenuState()//void MainMenu::Initialize()
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";
	sf::String *text = new sf::String("hello world");
	gui::Label *label = new gui::Label(50, 50, 200, 50, text, font, 10, 10);
	//label->setColor(sf::Color::Green);
	//label->setCharacterSize(12);
	//label->setStyle(0);
	menuItemContainer->Add(label);
}

MainMenu::~MainMenu()// : MenuState()//void MainMenu::Shutdown()
{
	MenuState::~MenuState();
}

void MainMenu::EventUpdate(App &app, Game &game, const sf::Event &event)
{
    MenuState::EventUpdate(app, game, event);
}

GameState *MainMenu::Update(App &app, Game &game)
{
    MenuState::Update(app, game);
    return this;
}

void MainMenu::Draw(App &app)
{
	MenuState::Draw(app);
    //MenuState::Draw(app);
    //menuItems.
}
#endif
