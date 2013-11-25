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
	sf::Font font = sf::Font();
	if (!font.loadFromFile("font.ttf"))
		throw "font.ttf not found";
	sf::String text = sf::String("hello world");
	gui::Label *label = new gui::Label(50, 50, text, font);
	label->setColor(sf::Color::Green);
	//label->setCharacterSize(12);
	//label->setStyle(0);
	menuItemContainer->Add(label);
}

MainMenu::~MainMenu()// : MenuState()//void MainMenu::Shutdown()
{
	MenuState::~MenuState();
}

void MainMenu::EventUpdate(App &app, const sf::Event &event)
{
    MenuState::EventUpdate(app, event);
}

GameState *MainMenu::Update(App &app)
{
    MenuState::Update(app);
    return this;
}

void MainMenu::Draw(App &app)
{
	MenuState::Draw(app);
    //MenuState::Draw(app);
    //menuItems.
}
#endif
