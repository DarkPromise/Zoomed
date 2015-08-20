#include "Inventory.h"

Inventory::Inventory(void)
{
}

Inventory::~Inventory(void)
{
}

void Inventory::addItem(Item * item)
{
	m_itemList.push_back(item);
}

Item* Inventory::getItem(int slot)
{
	return this->m_itemList[slot];
}

void Inventory::removeItem(int slot)
{
	delete m_itemList.at(slot);
	m_itemList.erase(m_itemList.begin() + slot);
}

void Inventory::useItem(Item * item)
{
	switch(item->getItemID())
	{
	case ITEM_REDUCE_NOISE_POTION:
		{
		}
		break;
	default:
		break;
	}
}