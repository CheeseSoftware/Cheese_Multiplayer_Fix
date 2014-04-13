#pragma once

#include <string>
#ifdef CLIENT
#include <SFML\Graphics.hpp>
#endif

class ITextureContainer
{
public:
	//virtual bool AddTexture(std::string fileName, int textureType)=0;
	virtual bool AddSpriteSheet(std::string fileName, int spriteWidth, int spriteHeight)=0;
	//CLIENT_(  )
#ifdef CLIENT
	virtual sf::Sprite **getTextures(std::string textureName)=0;
#endif
};