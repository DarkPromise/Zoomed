#ifndef INVENTORY_H
#define INVENTORY_H

class Player; //Forward Declaration

#include "Item.h"
#include <vector>
#include <iostream>

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	void addItem(Item* item);
	Item* getItem(int slot);
	void removeItem(int slot);
	void useItem(int slot, Player * player);

private:
	std::vector<Item*> m_itemList;
};

#endif

