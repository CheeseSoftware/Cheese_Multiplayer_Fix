#ifndef _SERVER
#include "EventHandler.h"
#include "App.h"
#include "World.h"

void EventHandler::EventUpdate(App &app, const sf::Event &event, World *world, std::queue<sf::Packet> *packetDataList)
{
	for (auto it : callbackList)
	{
		it.second(app, event, world, packetDataList);
	}
}

void EventHandler::AddEventCallback(void* source, std::function<void(App&, const sf::Event&, World*, std::queue<sf::Packet>*)> callback)
{
	callbackList.emplace(source, callback);
}

void EventHandler::RemoveEventCallback(void* source)
{
	auto it = callbackList.find(source);
	if (it != callbackList.end())
	{
		callbackList.erase(it);
	}
}
#endif