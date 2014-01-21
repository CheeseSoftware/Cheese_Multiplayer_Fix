#pragma once

class TextureContainer;
#ifndef TEXTURECONTAINER_H_INCLUDED
#define TEXTURECONTAINER_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#ifdef CLIENT
#include <SFML\Graphics.hpp>
#endif

#include "App.h"

class TextureContainer
{
private:
#ifdef CLIENT
	std::map<std::string, sf::Sprite*> textureList;
#else
	std::vector<std::string> textureList;
#endif
public:
	TextureContainer(void);
	~TextureContainer(void);
	bool AddTexture(std::string fileName, int textureType);
	bool AddSpriteSheet(std::string fileName, int spriteWidth, int spriteHeight);
	CLIENT_( sf::Sprite *getTextures(std::string textureName); )
};

#endif