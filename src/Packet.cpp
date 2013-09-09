#include "Packet.h"
#include "Player.h"

Packet::Packet(void)
	: sf::Packet()
{
	Player *p = new Player(0, 0, 16, 16, false, "", 0, "");
	int noob = 0;
	//this << noob;s
}


Packet::~Packet(void)
{
}

sf::Packet& operator<<(sf::Packet& packet, Player player)
{
	return packet << player.getPosition().x << player.getPosition().y << player.getSize().x << player.getSize().y << player.getAngle() << player.getTextureName() << player.getTextureId();
}

sf::Packet& operator>>(sf::Packet& packet, Player player)
{
	float x;
	float y;
	float xSize;
	float ySize;
	float angle;
	std::string textureName;
	short textureId;
	
	packet >> x >> y >> xSize >> ySize >> angle >> textureName >> textureId;
	player.setPosition(x, y);
	player.setSize(xSize, ySize);
	player.setAngle(angle);
	return packet;
}
