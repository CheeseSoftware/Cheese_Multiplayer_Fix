#ifdef CLIENT
#pragma once

#include <map>
#include <queue>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#include "App.h"

class World;
class GameUtility;
class Game;

template<class T>
class EventHandler
{
	std::map<void*,std::function<void(App&, Game *game, const sf::Event&, T)>> callbackList; 
public:
	void EventUpdate(App& app, Game *game, const sf::Event& event, T t)
	{
		for (auto it : callbackList)
		{
			it.second(app, game, event, t);
		}
	}
	void AddEventCallback(void *source, std::function<void(App&, Game *game, const sf::Event&, T)> callback)
	{
		callbackList.emplace(source, callback);
	}
	void RemoveEventCallback(void *source)
	{
		auto it = callbackList.find(source);
		if (it != callbackList.end())
		{
			callbackList.erase(it);
		}
	}
};

#endif