#include "GUIItem.h"


#ifndef _SERVER
#include "GUIItem.h"

GUIItem::GUIItem(int x, int y, int sizeX, int sizeY)
	: Selectable()
{
	x = x;
	y = y;
	sizeX = sizeX;
	sizeY = sizeY;
}


GUIItem::~GUIItem(void)
{
}

void GUIItem::Draw(App &app, float x, float y) const
{

}

GameState *GUIItem::EventUpdate(App& app, const sf::Event& event, GameState* gameState)
{
	return gameState;
}
#endif
