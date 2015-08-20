#include "Item.h"

Item::Item(std::string itemName, ITEM_ID itemID)
{
	this->m_itemName = itemName;
	this->m_itemID = itemID;
}

Item::~Item(void)
{
}

void Item::renameItem(std::string reName)
{
	this->m_itemName = reName;
}

std::string Item::toString()
{
	return this->m_itemName;
}

ITEM_ID Item::getItemID()
{
	return this->m_itemID;
}

void Item::setDescription(std::string itemDescription)
{
	this->m_itemDescription = itemDescription;
}

std::string Item::getDescription()
{
	return this->m_itemDescription;
}


