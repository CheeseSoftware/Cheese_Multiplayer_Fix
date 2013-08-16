#pragma once
#include "Item.h"
class NormalItem : public Item
{
public:
	NormalItem(std::string name, std::string textureName);
	~NormalItem(void);
};

