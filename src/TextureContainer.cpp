#include <iostream>
#ifndef _SERVER
#include <SFML\Graphics.hpp>
#endif
#include "TextureContainer.h"


TextureContainer::TextureContainer(void)
{
	AddSpriteSheet("slot.png", 32, 32);
	AddSpriteSheet("Block0.png", 16, 16);
	AddSpriteSheet("BlockBackground.png", 16, 16);
	AddSpriteSheet("BlockSolid.png", 16, 16);
	AddSpriteSheet("BlockGravity.png", 16, 16);
	AddSpriteSheet("BlockChest.png", 16, 16);
	AddSpriteSheet("arrow.png", 32, 8);
	AddSpriteSheet("graywizard.png", 16, 26);
	AddSpriteSheet("smileys.png", 16, 16);
	AddSpriteSheet("stone.png", 1024, 1024);
	AddSpriteSheet("dirt.png", 512, 512);
	AddSpriteSheet("Background.png", 512, 512);
}


TextureContainer::~TextureContainer(void)
{

}

bool TextureContainer::AddSpriteSheet(std::string fileName, int spriteWidth, int spriteHeight)
{
#ifndef _SERVER
	//CLIENT(
		sf::Image image;
	bool success = image.loadFromFile(fileName);

	if (!success)
	{
		std::cout << "Failed to load " << fileName << '\n';
	}

	int width = image.getSize().x/spriteWidth;
	int height = image.getSize().y/spriteHeight;

	sf::Sprite *sprite = new sf::Sprite[width*height];
	sf::Image *tempImage;

	std::cout << width << " " << height << std::endl;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tempImage = new sf::Image();
			tempImage->create(spriteWidth, spriteHeight);
			tempImage->copy(image, 0, 0, sf::IntRect(x * spriteWidth, y * spriteHeight, (x + 1) * spriteWidth, (y + 1) * spriteHeight), false);
			//tempImage->setSmooth(false);
			sf::Texture *toSet = new sf::Texture();
			toSet->create(spriteWidth, spriteHeight);
			toSet->update(*tempImage, 0, 0);
			sprite[x + (y*width)].setTexture(*toSet);
		}
	}
	textureList.emplace(fileName, sprite);
	std::cout << "Added texturesheet " << fileName << std::endl;
	return success;
	//)
#endif
		return false;
}

/*bool TextureContainer::AddSprite(std::string fileName)
{
	sf::Texture *texture = new sf::Texture();
	bool success = texture->loadFromFile(fileName);

	if (!success)
	{
		std::cout << "Failed to load " << fileName << '\n';
	}
	int width = texture->getSize().x;
	int height = texture->getSize().y;

	sf::Sprite *sprite = new sf::Sprite[width*height];
	sprite->setTexture(*texture);
	textureList.emplace(fileName, sprite);
	std::cout << "Added texture " << fileName << std::endl;
}*/

//CLIENT(
#ifndef _SERVER
	sf::Sprite *TextureContainer::getTextures(std::string textureName)
{
	auto it = textureList.find(textureName);
	return (it == textureList.end()) ? nullptr : it->second;
}//)
#endif