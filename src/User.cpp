#include "User.h"
#include "Creature.h"

User::User(int id, std::string name) : CreatureController(id, name)
{

}

#ifdef SERVER

#else
void User::HandleEvent(App &app, const sf::Event &event, GameState* gameState)
{

}
#endif