#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	void addItem(Item* item);
	void removeItem(int itemID);
	void useItem(Item * item);

private:
	std::vector<Item*> m_itemList;
};

#endif

