#ifdef CLIENT
#pragma once
#include <stack>
#include "App.h"
#include "GameUtility.h"
#include "MenuItemContainer.h"
#include "Label.h"
#include <string>
#include <sstream>

class World;
class TextureContainer;
class Block;

namespace sf
{
	class Packet;
}

class NoobishBlockMenu
{
	int selected;
	int layer;
	std::pair<Block*, unsigned short> **blockMenu;
	
public:
	//>.<NoobishBlockMenu();
	NoobishBlockMenu(World *world, GameUtility* gameUtility);

	void EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility);
	void Draw(App &app, GameUtility *gameUtility);
};
#endif