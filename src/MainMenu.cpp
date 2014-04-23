#ifdef CLIENT

#include <iostream>
#include <vector>
#include <sstream>

#include "MainMenu.h"
#include "AMenuState.h"
#include "PlayState.h"
#include "GameState.h"
#include "Label.h"
#include "Text.h"
#include "Button.h"
#include "MenuItemContainer.h"
#include "Game.h"
#include "LoadState.h"

MainMenu::MainMenu(Game *game) : AMenuState()//void MainMenu::Initialize()
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";

	gui::Label *label = new gui::Label(0, 50, game->getTextures("label.png")[0], new sf::String("Cheese Edits"), font, 10, 10);
	label->setPositionType(PositionType::centerTop);
	menuItemContainer->Add(label);

	gui::Button *button_mp = new gui::Button(0, 0, game->getTextures("label.png")[0], new sf::String("Multiplayer"), font, 8, 8);
	button_mp->setPositionType(PositionType::middleCenter);
	button_mp->setOnLMBClickFunctionCallback([=](App &app, const sf::Event event, int x, int y)
	{
		game->SetGameState(new PlayState(app, game));
	});
	menuItemContainer->Add(button_mp);

	gui::Button *button_sp = new gui::Button(0, 40, game->getTextures("label.png")[0], new sf::String("Singleplayer"), font, 8, 8);
	button_sp->setPositionType(PositionType::middleCenter);
	button_sp->setOnLMBClickFunctionCallback([=](App &app, const sf::Event event, int x, int y)
	{
		button_sp->setText("Not implemented, idiot!");
	});
	menuItemContainer->Add(button_sp);

	gui::Button *button_settings = new gui::Button(0, 80, game->getTextures("label.png")[0], new sf::String("Settings"), font, 8, 8);
	button_settings->setPositionType(PositionType::middleCenter);
	button_settings->setOnLMBClickFunctionCallback([=](App &app, const sf::Event event, int x, int y)
	{
		button_settings->setText("Not implemented, fool!");
	});
	menuItemContainer->Add(button_settings);

	
}

MainMenu::~MainMenu()
{
	std::cout << "snordestructor\n";
	AMenuState::~AMenuState();
}

void MainMenu::EventUpdate(App &app, Game *game, const sf::Event &event)
{
	AMenuState::EventUpdate(app, game, event);
}

GameState *MainMenu::Update(App &app, Game *game)
{
	AMenuState::Update(app, game);
	return this;
}

void MainMenu::Draw(App &app, Game *game)
{
	AMenuState::Draw(app, game);
}
#endif
