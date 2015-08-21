#include "Inventory.h"

Inventory::Inventory(void)
{
	
}

Inventory::~Inventory(void)
{
	for(unsigned i = 0; i < m_itemList.size(); ++i)
	{
		delete m_itemList[i];
	}
	m_itemList.clear();
}

void Inventory::addItem(Item * item)
{
	this->m_itemList.push_back(item);
	//std::cout << "Added " << item->toString() << " to inventory" << std::endl;
}

Item* Inventory::getItem(int slot)
{
	return this->m_itemList[slot - 1];
}

void Inventory::removeItem(int slot)
{
	delete m_itemList.at(slot - 1);
	m_itemList.erase(m_itemList.begin() + slot - 1);
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