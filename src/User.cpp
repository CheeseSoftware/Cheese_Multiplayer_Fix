#include "User.h"
#include "Creature.h"

User::User(int id) : CreatureController(id)
{

}

#ifdef SERVER

#else
void User::HandleEvent(App &app, const sf::Event &event, GameState* gameState)
{

}
#endif