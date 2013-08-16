#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Item.h"
class TextureContainer;
class Camera;
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
	int AddItem(Item* item, int amount);
	int AddItem(int slot, int amount);
	bool Contains(Item* item);
	void Draw(int xBlock, int yBlock, sf::RenderWindow& window, Camera& camera, TextureContainer& tC);
	std::ostream& get(std::ostream &out);
private:
	std::pair<Item*, int>** storedItems;
	int slots;
	int slotCapacity;
};

