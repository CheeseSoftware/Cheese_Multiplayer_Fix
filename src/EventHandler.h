#ifndef _SERVER
#pragma once

#include <map>
#include <queue>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#include "App.h"

//class App;
class World;
class GameUtility;

template<class T> //auto(App&, const sf::Event&, GameUtility*)
class EventHandler
{
	std::map<void*,std::function<void(App&, const sf::Event&, T)>> callbackList;
public:
	void EventUpdate(App&, const sf::Event&, T t)
	{
		for (auto it : callbackList)
		{
			it.second(app, event, gameUtility);
		}
	}
	void AddEventCallback(void *source, std::function<void(App&, const sf::Event&, T)> callback)
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