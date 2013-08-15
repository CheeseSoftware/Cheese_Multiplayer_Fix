#pragma once
#include <iostream>
#include <string>
#include "Item.h"
class Inventory
{
public:
	Inventory(int slots, int slotCapacity);
	~Inventory(void);
	int getSlots() { return this->slots; };
	int getSlotCapacity() { return this->slotCapacity; };
	int getFreeSlot();
	int getSlot(Item* item);
	Item *getItem(int slot);
	int getItemCount(int slot);
	int getItemCount(Item* item);
	Item* getItemByName(std::string name);
	std::pair<Item*, int>** getItems();
	bool RemoveItem(Item* item, int amount);
	bool RemoveItem(int slot, int amount);
	bool RemoveItem(int slot);
	bool AddItem(Item* item, int amount);
	bool AddItem(int slot, int amount);
	bool Contains(Item* item);
private:
	std::pair<Item*, int>** storedItems;
	int slots;
	int slotCapacity;
};

