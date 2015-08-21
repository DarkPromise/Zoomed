#include "Item.h"

Item::Item(std::string itemName, ITEM_ID itemID, const char * itemPath)
{
	this->m_itemName = itemName;
	this->m_itemID = itemID;

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
