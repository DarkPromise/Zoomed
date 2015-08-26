#include "Player.h"
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
	if(m_itemList.size() < PLAYER_INVENTORY_SIZE)
	{
		this->m_itemList.push_back(item); //JUST INCASE FOR FUTURE ADDONS
	}
	else
	{
		if(item->getItemType() == ITEM_TYPE_CONSUMABLE)
		{
			m_itemList[0] = item;
		}
		else if(item->getItemType() == ITEM_TYPE_EQUIPMENT)
		{
			m_itemList[1] = item;
		}
	}
}

Item* Inventory::getItem(int slot)
{
	return this->m_itemList[slot - 1];
}

void Inventory::removeItem(int slot)
{
	delete m_itemList[slot-1]; //Deleting the pointer
	m_itemList[slot-1] = new Item(); //Reset the item
}

void Inventory::useItem(int slot, Player * player)
{
	if((slot-1) < m_itemList.size()) //Check if item exists in slot
	{
		switch(m_itemList[slot - 1]->getItemID()) //Get Item ID
		{
		case ITEM_REDUCE_NOISE_POTION:
			break;
		case ITEM_REDUCED_NOISE_GAIN_POTION:
			break;
		case ITEM_SIGHT_POTION:
			break;
		case ITEM_REDUCED_FEAR_GAIN_POTION:
			break;
		case ITEM_REDUCE_FEAR_POTION:
			player->getCurrFear() -= 40.f;
			break;
		case ITEM_SUPPRESS_FEAR_POTION:
			break;
		case ITEM_COMPASS:
			break;
		case ITEM_MAP:
			break;
		case ITEM_SAFETY_CHARM:
			break;
		case ITEM_EQUIPMENT_BOOTS:
			break;
		case ITEM_EQUIPMENT_GLASSES:
			break;
		case ITEM_EQUIPMENT_ARMOR:
			break;
		case ITEM_EQUIPMENT_INVISCLOAK:
			break;
		}
		removeItem(slot); //Remove Item after using it
	}
}