#include "NormalItem.h"


NormalItem::NormalItem(std::string name, std::string textureName)
	: Item()
{
	this->setName(name);
	this->setTextureName(textureName);
}


NormalItem::~NormalItem(void)
{
}
