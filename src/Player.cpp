#include "Player.h"
#include <tuple>
#include "World.h"
#include "Camera.h"
#include "Projectile.h"
#include "MessageType.h"
#include "App.h"
#include "Block.h"
#include "GameUtility.h"
#include "Inventory.h"

Player::Player(int id, float X, float Y, short sizeX, short sizeY, bool IsClientControlling, std::string spriteName, int spriteIndex, std::string Name) 
	: Creature(id, X, Y, sizeX, sizeY, 1024, 8192, 0.8125, spriteName, spriteIndex, IsClientControlling)
{
	name = Name;
	cameraDelay = 0;
	right = true;
	down = false;
	left = false;
	up = false;
	lmb = false;
	inventory = new Inventory(8, 4, 64);
	currentChunkX = 0;
	currentChunkY = 0;
	currentChunkXOld = 0;
	currentChunkYOld = 0;

#ifdef CLIENT
	//auto eventUpdate =  [this](App &app, sf::Event &event, World *world, std::queue<sf::Packet> *packetDataList) { EventUpdate(app, event, world, packetDataList); };
	//eventHandler.AddEventCallback(this, eventUpdate);
#endif
}

/*#ifdef SERVER
void Player::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList)
#else
void Player::Update(App &app, World *world, std::queue<sf::Packet> *packetDataList, Camera *camera, EventHandler &eventHandler)
#endif*/
void Player::Update(App &app, GameUtility *GameUtility)
{
	//std::cout << "xpos: " << x << " ypos:" << y << " xspeed:" << speedX << " yspeed:" << speedY << std::endl;
#ifdef CLIENT
	//if (y > 809200)
	//	y = 0;

	if (isClientControlling)
	{
		currentChunkXOld = currentChunkX;
		currentChunkYOld = currentChunkY;
		currentChunkX = floor(x/16.f+0.5)/16;
		currentChunkY = floor(y/16.f+0.5)/16;
		if(GameUtility->getCurrentWorld() != nullptr && currentChunkX != currentChunkXOld || currentChunkY != currentChunkYOld)
		{
			//Now request chunks from server! We have moved to a different chunk!
			sf::Packet chunkPacket = sf::Packet();
			chunkPacket << (sf::Uint16)RequestChunks;
			for(long x = currentChunkX - 6; x < currentChunkX + 6; x++)
			{
				for(long y = currentChunkY - 6; y < currentChunkY + 6; y++)
				{
					if(GameUtility->getCurrentWorld()->getChunk(x, y) == nullptr)
					{
						//std::cout << "requesting chunk: x:" << x << " y:" << y << std::endl;
						chunkPacket << (sf::Int32)x << (sf::Int32) y;
					}
				}
			}
			GameUtility->SendPacket(chunkPacket);
		}

		if (GameUtility->getCamera().getEntity() != this)
		{
			if (cameraDelay <= 0)
			{
				GameUtility->getCamera().setCameraAt(this);
				cameraDelay = 0.5;
			}
			else
			{
				cameraDelay -= app.getDeltaTime();
			}
		}
	}
#endif

	Creature::Update(app, GameUtility);
	/*#ifdef SERVER
	Creature::Update(app, world, packetDataList);
	#else
	Creature::Update(app, world, packetDataList, camera, eventHandler);
	#endif*/
}

#ifdef CLIENT

void Player::EventUpdate(App &app, const sf::Event &event, GameUtility* gameUtility)
{
	if (isClientControlling)
	{
		bool
			rDown = right,
			dDown = down,
			lDown = left,
			uDown = up;

		switch(event.type)
		{
		case sf::Event::KeyPressed:
			switch(event.key.code)
			{
			case sf::Keyboard::D:
Right:
				rDown = true;
				break;
			case sf::Keyboard::S:
Down:
				dDown = true;
				break;
			case sf::Keyboard::A:
Left:
				lDown = true;
				break;
			case sf::Keyboard::W:
Up:
				uDown = true;
				break;

			case sf::Keyboard::Space:
				if (true)//(speedX == 0 || speedY == 0)
				{
					float xSpeed2 = 0;
					float ySpeed2 = 0;

					if (currentBlock.first != nullptr)
					{
						currentBlock.first->CreatureJump(app, this, xSpeed2, ySpeed2, currentBlock.second);
					}

					if (xSpeed2 != 0 && speedX != 0)
						break;
					else if (ySpeed2 != 0 && speedY != 0)
						break;

					if (CheckCollision(app, gameUtility->getCurrentWorld(), gameUtility, (xSpeed2 > 0)? -1:1, (ySpeed2 > 0)? -1:1))
					{
						if (speedX == 0)
							speedX = xSpeed2;

						if (speedY == 0)
							speedY = ySpeed2;
					}

					if (currentBlock.first != nullptr)
						currentBlock.first->OnEntityHover(app, this, xSpeed2, ySpeed2, speedX, speedY, currentBlock.second);

					if (isClientControlling)
					{
						sf::Packet packet;
						packet << (sf::Uint16)MessageType::CreatureMove << x << y << speedX << speedY << angle << horizontal << vertical;
						gameUtility->SendPacket(packet);
					}
				}
				break;
			case sf::Keyboard::Q:
				{
					float deltaX = sf::Mouse::getPosition().x - x + gameUtility->getCamera().getLeftX();//(sf::Mouse::getPosition().x - app.getPosition().x + app.getView().getCenter().x - app.getView().getSize().x/2) - x;
					float deltaY = sf::Mouse::getPosition().y - y + gameUtility->getCamera().getTopY();//(sf::Mouse::getPosition().y - app.getPosition().y + app.getView().getCenter().y - app.getView().getSize().y/2) - y;

					double angle = atan2(deltaY, deltaX) * 180 / 3.1415926536;

					if (angle < 0)
						angle = angle + 360;

					double deltaSpeedX = cos(angle*3.1415926536)*speedX;
					double deltaSpeedY = sin(angle*3.1415926536)*speedY;

					if (angle > 180)
						deltaSpeedX *= -1;

					if (angle < 90 || angle > 270)
						deltaSpeedY *= -1;


					Projectile *projectile = new Projectile(0, x+(sizeX>>1), y+(sizeY>>1), 32, 32, angle, 1024, 0.03125F, "arrow.png", 0, false);
					gameUtility->getCurrentWorld()->AddEntity(projectile);
				}
				break;

			case sf::Keyboard::Right:
				goto Right;

			case sf::Keyboard::Down:
				goto Down;

			case sf::Keyboard::Left:
				goto Left;

			case sf::Keyboard::Up:
				goto Up;
			}
			break;

		case sf::Event::KeyReleased:
			switch(event.key.code)
			{
			case sf::Keyboard::D:
RightR:
				rDown = false;
				break;
			case sf::Keyboard::S:
DownR:
				dDown = false;
				break;
			case sf::Keyboard::A:
LeftR:
				lDown = false;
				break;
			case sf::Keyboard::W:
UpR:
				uDown = false;
				break;

			case sf::Keyboard::Right:
				goto RightR;

			case sf::Keyboard::Down:
				goto DownR;

			case sf::Keyboard::Left:
				goto LeftR;

			case sf::Keyboard::Up:
				goto UpR;
			}
			break;

		case sf::Event::MouseButtonPressed:
			switch(event.key.code)
			{
			case sf::Mouse::Left:
				//inventory->AddItem(new NormalItem("Cow", "cowtexture"), 2);
				//inventory->AddItem(new NormalItem("Goat", "cofsafwtexture"), 8);
				//inventory->AddItem(new NormalItem("Chicken", "cowtexture"), 20);
				//inventory->get(std::cout);

				if(!lmb && (lmb=true))


					lmb = true;
				break;

			case sf::Mouse::Right:
				break;
			}

		case sf::Event::MouseButtonReleased:
			{
				lmb = false;
			}
			break;
		}
		KeyUpdate(rDown, dDown, lDown, uDown, gameUtility);
	}
}

void Player::Draw(App &app, GameUtility *gameUtility)
{

	//inventory->Draw(16, 16, app, gameUtility->getTextureContainer()); 
	Creature::Draw(app, gameUtility);
}
#endif

void Player::KeyUpdate(bool Right, bool Down, bool Left, bool Up, GameUtility* gameUtility)
{
	if (Right != right || Down != down || Left != left || Up != up)
	{
		horizontal = 0;
		vertical = 0;

		if (Right)  horizontal += speed;
		if (Down)   vertical += speed;
		if (Left)   horizontal -= speed;
		if (Up)     vertical -= speed;

		//std::cout << "bools: " <<  Right << " " << Down<< " " << Left<< " " << Up<< " " << std::endl;
		//std::cout << "variables: " <<  horizontal << " " << vertical << " " << speedX << " " << speedY << std::endl;

		right = Right;
		down = Down;
		left = Left;
		up = Up;

		if (isClientControlling)
		{
			sf::Packet packet;
			packet << (sf::Uint16)MessageType::CreatureMove << x << y << speedX << speedY << angle << horizontal << vertical;
			gameUtility->SendPacket(packet);
		}
	}
}

void Player::setCameraDelay(float delay)
{
	cameraDelay = delay;
}

const char *const Player::getTextureName()
{
	return "smileys.png";
}

short Player::getTextureId()
{
	return 0;
}