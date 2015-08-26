#include "Item.h"

Item::Item(std::string itemName, ITEM_ID itemID, const char * itemPath, ITEM_TYPE itemType) :
m_itemDuration(0.f)
{
	this->m_itemName = itemName;
	this->m_itemID = itemID;
	this->m_itemType = itemType;

	m_itemMesh = MeshBuilder::GenerateQuad(itemName,Color(0.f,0.f,0.f),1.f);
	//Rendering in 2D
	m_itemMesh->textureID = LoadTGA(itemPath);
}

Item::~Item(void)
{
	delete m_itemMesh;
	m_itemMesh = NULL;
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

Mesh* Item::getMesh()
{
	return this->m_itemMesh;
}

void Item::setDuration(float duration)
{
	this->m_itemDuration = duration;
}

float Item::getDuration(Item * item)
{
	switch(item->m_itemID)
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
	return this->m_itemDuration;
}
