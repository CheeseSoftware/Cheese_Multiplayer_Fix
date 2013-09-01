#ifndef _SERVER
#pragma once

#include <map>
#include <queue>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

class App;
class World;
class GameUtilityInterface;

class EventHandler
{
	std::map<void*,std::function<void(App&, const sf::Event&, GameUtilityInterface*)>> callbackList;
public:
	void EventUpdate(App &app, const sf::Event &event, GameUtilityInterface* gameUtilityInterface);
	void AddEventCallback(void *source, std::function<void(App&, const sf::Event&, GameUtilityInterface*)> callback);
	void RemoveEventCallback(void *source);
};
#endif