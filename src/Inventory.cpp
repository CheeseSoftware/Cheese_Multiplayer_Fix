#include "Inventory.h"


Inventory::Inventory(int slots, int slotCapacity)
{
	this->slots = slots;
	this->slotCapacity = slotCapacity;
	storedItems = new std::pair<Item*, int>*[slots]();
}


Inventory::~Inventory(void)
{
}

int Inventory::getFreeSlot()
{
	for (int i = 0; i < slots; i++)
	{
		if(storedItems[i] == nullptr)
			return i;
	}
	return -1;
}

int Inventory::getSlot(Item* item) //jämför pekare, inte bra, måste fixas!
{
	for (int i = 0; i < slots; i++)
	{
		if(storedItems[i]->first == item)
			return i;
	}
	return -1;
}

Item* Inventory::getItem(int slot)
{
	return storedItems[slot]->first;
}

int Inventory::getItemCount(int slot)
{
	return storedItems[slot]->second;
}

int Inventory::getItemCount(Item* item) //jämför pekare, inte bra, måste fixas!
{
	int total = 0;
	for (int i = 0; i < slots; i++)
	{
		if(storedItems[i]->first == item)
			total += storedItems[i]->second;
	}
	return total;
}

Item* Inventory::getItemByName(std::string name)
{
	for (int i = 0; i < slots; i++)
	{
		if(storedItems[i]->first->getName() == name)
			return storedItems[i]->first;
	}
	return nullptr;
}

std::pair<Item*, int>**  Inventory::getItems()
{
	return storedItems;
}

bool Inventory::RemoveItem(Item* item, int amount) //jämför pekare, inte (bra), måste fixas!
{
	int left = amount;
	for (int i = 0; i < slots; i++)
	{
		if(storedItems[i]->first == item)
		{
			if(storedItems[i]->second >= left)
			{
				storedItems[i]->second -= left;
				return true;
			}
			else
			{
				left -= storedItems[i]->second;
				delete storedItems[i];
			}
		}
	}
	return false;
}

bool Inventory::RemoveItem(int slot, int amount)
{
	if(storedItems[slot]->second >= amount)
		storedItems[slot]->second -= amount;
	else
		storedItems[slot]->second = 0;
}

bool Inventory::RemoveItem(int slot)
{
	delete storedItems[slot];
}

bool Inventory::AddItem(Item* item, int amount)
{
	int left = amount;
	for (int i = 0; i < slots; i++)
	{
		if(storedItems[i]->first == item && storedItems[i]->second + amount <= getSlotCapacity())
		{
			storedItems[i]->second += amount;
			return true;
		}
	}
	for (int i = 0; i < slots; i++)
	{
		if(left != 0)
		{
			if(left <= getSlotCapacity())
				storedItems[getFreeSlot()] = new std::pair<Item*, int>(item, left);
			else
			{
				storedItems[getFreeSlot()] = new std::pair<Item*, int>(item, getSlotCapacity());
				left -= getSlotCapacity();
			}

		}
		else
			break;
	}
	return true;
}

bool Inventory::AddItem(int slot, int amount)
{
	if(storedItems[slot]->second + amount <= getSlotCapacity())
		storedItems[slot]->second += amount;
	else
		storedItems[slot]->second = getSlotCapacity();
}