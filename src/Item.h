#pragma once
#include <iostream>
#include <string>
class Item
{
public:
	Item(void);
	~Item(void);
	virtual std::string getName() { return name; };
	virtual void setName(std::string s) { name = s; };
	virtual std::string getTextureName() { return textureName; };
	virtual void setTextureName(std::string s) { textureName = s; };
	virtual inline bool operator==(Item& lhs){ if(getName() == lhs.getName()) return true; return false;}
	virtual inline bool operator!=(Item& lhs){return !operator==(lhs);}
private:
	std::string name;
	std::string textureName;
};

