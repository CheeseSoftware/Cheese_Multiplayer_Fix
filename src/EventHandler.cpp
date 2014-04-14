#ifdef f_SERVER
#include "EventHandler.h"
#include "App.h"
#include "World.h"

template<class T>
void EventHandler::EventUpdate(App &app, Game *game, const sf::Event &event, GameUtility* gameUtility)
{
	for (auto it : callbackList)
	{
		it.second(app, event, gameUtility);
	}
}


template<class T>
void EventHandler::AddEventCallback(void* source, std::function<void(App&, const sf::Event&, GameUtility*)> callback)
{
	callbackList.emplace(source, callback);
}

template<class T>
void EventHandler::RemoveEventCallback(void* source)
{
	auto it = callbackList.find(source);
	if (it != callbackList.end())
	{
		callbackList.erase(it);
	}
}
#endif