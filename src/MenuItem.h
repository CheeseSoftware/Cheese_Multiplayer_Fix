#pragma once
#ifndef _SERVER

#ifndef MENUITEM_H_INCLUDED
#define MENUITEM_H_INCLUDED

#include <functional>
#include "App.h"

class GameUtilityInterface;
class GameState;

class MenuItem
{
protected:
    int x;
    int y;
    int width;
    int height;
    bool selected;
    bool down;
	bool clicked;
	std::function<GameState*(App&)> clickEvent;

	MenuItem();
public:
	MenuItem(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent);
	~MenuItem();
	virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtilityInterface* gameUtilityInterface);
	//virtual void OnClick(App&, const sf::Event&, GameUtilityInterface*);
    //virtual GameState *Update(App &app);
    virtual void Draw(App &app)=0;
};

#endif // MENUITEM_H_INCLUDED
#endif // !_SERVER