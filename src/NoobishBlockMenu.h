#ifndef _SERVER
#pragma once
#include <stack>
#include "App.h"
#include "GameUtilityInterface.h"

#pragma once

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
	std::pair<Block*, unsigned short> **blockMenu;
public:
	//>.<NoobishBlockMenu();
	NoobishBlockMenu(World *world, GameUtilityInterface* gameUtilityInterface);

	void EventUpdate(App &app, const sf::Event &event, GameUtilityInterface* gameUtilityInterface);
    void Draw(App &app, GameUtilityInterface *gameUtilityInterface);
};
#endif