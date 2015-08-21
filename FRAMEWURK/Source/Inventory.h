#ifndef INVENTORY_H
#define INVENTORY_H

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
	void useItem(Item * item);

private:
	std::vector<Item*> m_itemList;
};

#endif

