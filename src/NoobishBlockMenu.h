#ifndef _SERVER
#include <stack>

class App;
class World;
class TextureContainer;
class Block;

namespace sf
{
	class Event;
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