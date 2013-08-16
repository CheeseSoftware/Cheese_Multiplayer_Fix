#ifndef _SERVER
#pragma once
#include <stack>
#include "App.h"

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
	NoobishBlockMenu(World *world);

	void EventUpdate(App &app, const sf::Event &event, World *world);
    void Draw(App &app, TextureContainer &tC);
};
#endif