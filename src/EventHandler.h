#ifndef _SERVER
#pragma once

#include <map>
#include <queue>p
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

class App;
class World;

class EventHandler
{
	std::map<void*,std::function<void(App&, const sf::Event&, World*, std::queue<sf::Packet>*)>> callbackList;
public:
	void EventUpdate(App &app, const sf::Event &event, World *world, std::queue<sf::Packet> *packetDataList);
	void AddEventCallback(void *source, std::function<void(App&, const sf::Event&, World*, std::queue<sf::Packet>*)> callback);
	void RemoveEventCallback(void *source);
};
#endif