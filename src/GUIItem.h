#ifndef _SERVER
#pragma once
#include "Selectable.h"
#include "IMenuItem.h"

class GUIItem : public gui::Selectable
{
public:
	GUIItem(int x, int y);
	~GUIItem(void);
	virtual void OnLeftClick(App &app, const sf::Event &event, GameState *gameState)=0;
	virtual void OnRightClick(App &app, const sf::Event &event, GameState *gameState)=0;
	virtual GameState *EventUpdate(App &app, const sf::Event &event, GameState *gameState)=0;
	virtual void Draw(App &app, float x, float y)=0;
	sf::Vector2f getPosition() { return sf::Vector2f(m_x, m_y); }
	//sf::Vector2f getSize() { return sf::Vector2f(sizeX, sizeY); }
private:
	int m_x;
	int m_y;
};
#endif

