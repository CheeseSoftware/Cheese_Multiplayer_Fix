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

template<class T>
class EventHandler
{
	std::map<void*,std::function<void(App&, const sf::Event&, T)>> callbackList; 
public:
	void EventUpdate(App& app, const sf::Event& event, T t)
	{
		for (auto it : callbackList)
		{
			it.second(app, event, t);
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