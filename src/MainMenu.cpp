#ifndef _SERVER

#include <iostream>
#include <vector>
#include "MainMenu.h"
#include "MenuState.h"
#include "GameState.h"
//#include "Label.h"
#include "Text.h"

MainMenu::MainMenu() : MenuState()//void MainMenu::Initialize()
{

	lambda = [this]()
	{
		std::cout << "XD";
	};

 //   menuItems.push_back(new Label(13,37,16,16,lambda));
    std::cout << "TESTING" << std::endl;
	//menuItems.push_back(new gui::Label(0, 0,
	//	[&](App& app, const sf::Event& event, GameState *gameState) { return nullptr; },
	//	"lol")); //GameState*(App&, const sf::Event&, GameState *gameState)

	sf::Font *font = new sf::Font;
	if (!font->loadFromFile("font.ttf"))
		throw "font.ttf not found";
	sf::Text *text = new sf::Text();//(std::string("test"), font, 12);
	text->setString(*(new std::string("test")));
	text->setFont(*font);
	text->setColor(sf::Color::Green);
	text->setCharacterSize(12);
	text->setStyle(0);
	menuItemContainer->Add(new gui::Text(text), 0, 0);
	/*PositionItem *i = new PositionItem();
	i->x = 0;
	i->y = 0;
	i->menuItem = new gui::Text(text);//*i = { 0, 0, new gui::Text(text) };
	menuItemContainer.Add(i);//menuItems.push_back(*i);*/
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
