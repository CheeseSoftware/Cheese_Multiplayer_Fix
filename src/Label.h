#pragma once

#ifndef Label_H_INCLUDED
#define Label_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include "MenuItem.h"
#include "GameState.h"
#include "App.h"

class Label : public MenuItem
{
public:
	std::string text;

	Label(int x, int y, int width, int height, std::function<GameState*(App&)> &clickEvent, std::string text);
	~Label();
	virtual GameState *EventUpdate(App& app, const sf::Event& event, GameUtilityInterface* gameUtilityInterface);
    virtual void Draw(App &app);
};

#endif