#ifdef CLIENT
#pragma once
#include "App.h"
#include "CreatureController.h"
#include "GameUtility.h"
#include "GameState.h"
#include "EventHandler.h"
#include <SFML\Graphics.hpp>
#include "MenuItemContainer.h"
#include "Label.h"
#include "Minimap.h"
#include "SoundHandler.h"

class World;
class InGameUI;
class Camera;
class NoobishBlockMenu;
class TextureContainer;
class Connection;
class BlockRegister;

class PlayState : public GameUtility
{
	NoobishBlockMenu *noobishBlockMenu;
	Connection *connection;
	EventHandler<GameUtility*> evsentHandler;

	//std::map<int, CreatureController> creatureControllers;

    sf::Clock fpsClock;
	sf::View hudView;
	sf::Font *font;

	gui::MenuItemContainer *hud;
	gui::Label *pos;
	gui::Minimap *minimap;

	//SoundHandler soundHandler;

	void ProcessPackets(GameUtility *gameUtility);
public:
	PlayState(App &app);
	~PlayState();
	virtual bool Load();
    virtual void EventUpdate(App &app, Game &game, const sf::Event &event);
    virtual GameState *Update(App &app, Game &game);
    virtual void Draw(App &app);
};
#endif
