#pragma once

#include "ITextureContainer.h"

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

class TextureContainer : public virtual ITextureContainer
{
private:
#ifdef CLIENT
	//std::vector<sf::Texture> textureList;
	//std::vector<sf::Sprite*> spriteList;

	std::map<std::string, sf::Texture*> textureList;//
	std::map<std::string, sf::Sprite*> spriteList;//
#else
	std::vector<std::string> textureList;
#endif
public:
	TextureContainer(void);
	~TextureContainer(void);
	//virtual bool AddTexture(std::string fileName, int textureType) override;
	virtual bool AddSpriteSheet(std::string fileName, int spriteWidth, int spriteHeight) override;
	//CLIENT_(  )
#ifdef CLIENT
	virtual sf::Sprite **getTextures(std::string textureName) override;
#endif
};

#endif