#include "GUIItem.h"


#ifndef _SERVER
#include "GUIItem.h"

GUIItem::GUIItem(int x, int y)
	: Selectable()
{
	m_x = x;
	m_y = y;
}


GUIItem::~GUIItem(void)
{
}

void GUIItem::Draw(App &app, float x, float y)
{

}

GameState *GUIItem::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
{
	return gameState;
}
#endif
