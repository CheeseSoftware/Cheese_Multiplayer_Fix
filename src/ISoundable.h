#include <SFML\System.hpp>

class ISoundable
{
public:
	virtual float getDistance(sf::Vector2f other)=0;
	//virtual void PlaySound(Game *game, ...)
	//virtual void PlayMusic(Game *game, ...)
};