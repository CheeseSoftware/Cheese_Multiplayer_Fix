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

MainMenu::MainMenu(Game *game) : AMenuState()//void MainMenu::Initialize()
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";

	std::stringstream ss;
	ss << "Member of first" << std::endl;
	//pos = new gui::Label(50, 50, 200, 50, new sf::String(ss.str()), font, 10, 10);
	//sf::String *text = new sf::String("hello world");
	gui::Label *label = new gui::Label(50, 50, 200, 50, new sf::String(":P\n"), font, 10, 10);
	//label->setColor(sf::Color::Green);
	//label->setCharacterSize(48);
	//label->setStyle(0);
	label->setPositionType(PositionType::middleCenter);
	menuItemContainer->Add(label);

	gui::Button *button = new gui::Button(0, 0, 80, 24, new sf::String("START!"), font, 8, 8);
	button->setOnLMBClickFunctionCallback(
		[=](App &app, const sf::Event event, int x, int y)
	{
		game->SetGameState(new PlayState(app));
	});
	button->setPositionType(PositionType::middleCenter);
	//[](App &app, const sf::Event event, int x, int y){});

	menuItemContainer->Add(button);
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
