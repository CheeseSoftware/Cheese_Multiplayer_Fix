#pragma once

#ifndef AMenuState_H_INCLUDED
#define AMenuState_H_INCLUDED

#include "GameState.h"
#include "EventHandler.h"
#include "MenuItemContainer.h"

class AMenuState : public GameState
{
protected:
    //std::vector<MenuItem*> menuItems;
	//std::vector<PositionItem> menuItems;
	//EventHandler<GameState*> eventHandler;
	gui::MenuItemContainer *menuItemContainer;
public:
	AMenuState();
	~AMenuState();
    //virtual void Initialize();
    virtual void EventUpdate(App &app, Game &game, const sf::Event &event);
    virtual GameState *Update(App &app, Game &game)=0;
    virtual void Draw(App &app);
    //virtual void Shutdown();
};

#endif // AMenuState_H_INCLUDED
