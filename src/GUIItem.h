#pragma once
#include "Selectable.h"
#include "IMenuItem.h"

class GUIItem : public gui::Selectable
{
public:
	GUIItem(int x, int y, int sizeX, int sizeY);
	~GUIItem(void);
	virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState)=0;
	virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState)=0;
	virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState)=0;
	virtual void Draw(App &app, float x, float y) const=0;
	std::pair<int, int> getPosition() { return std::pair<int, int>(x, y); }
	std::pair<int, int> getSize() { return std::pair<int, int>(sizeX, sizeY); }
private:
	int x;
	int y;
	int sizeX;
	int sizeY;
};

