#ifdef _SERVERd
#pragma once

#include <map>
#include <queue>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

class App;
class World;
class GameUtility;

class EventHandler
{
	std::map<void*,std::function<void(App&, const sf::Event&, GameUtility*)>> callbackList;
public:
	void EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility);
	void AddEventCallback(void *source, std::function<void(App&, const sf::Event&, GameUtility*)> callback);
	void RemoveEventCallback(void *source);
};
#endif