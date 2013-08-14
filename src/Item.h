#pragma once
#include <iostream>
class Item
{
public:
	Item(void);
	~Item(void);
	virtual std::string getName();
private:
	std::string name;
};

