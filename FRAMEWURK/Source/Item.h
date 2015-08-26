#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <GL\glew.h>   //For LoadTGA GLuint, unless I change LoadTGA to unsigned int
#include "LoadTGA.h"
#include "MeshBuilder.h"

enum ITEM_TYPE
{
	ITEM_TYPE_CONSUMABLE,
	ITEM_TYPE_EQUIPMENT,
	ITEM_TYPE_DEFAULT
};

enum ITEM_ID //Used for Item Effect
{ 
	ITEM_REDUCE_NOISE_POTION,
	ITEM_REDUCED_NOISE_GAIN_POTION,
	ITEM_SIGHT_POTION,
	ITEM_REDUCED_FEAR_GAIN_POTION,
	ITEM_REDUCE_FEAR_POTION,
	ITEM_SUPPRESS_FEAR_POTION,

	ITEM_COMPASS,
	ITEM_MAP,
	ITEM_SAFETY_CHARM,

	ITEM_EQUIPMENT_BOOTS,
	ITEM_EQUIPMENT_GLASSES,
	ITEM_EQUIPMENT_ARMOR,
	ITEM_EQUIPMENT_INVISCLOAK,

	ITEM_DEFAULT,
};

class Item
{
public:
	Item(std::string itemName = "Default Item", ITEM_ID itemID = ITEM_DEFAULT, const char * = "Images//Items//unknown.tga", ITEM_TYPE itemType = ITEM_TYPE_DEFAULT);
	~Item(void);

	void renameItem(std::string reName);
	std::string toString();
	void setDescription(std::string itemDescription);
	std::string getDescription();
	ITEM_ID getItemID();
	Mesh* getMesh();
	void setDuration(float duration); //Considering all items have a fix duration (unless hack)
	float getDuration(Item * item);
private:
	std::string m_itemName;
	std::string m_itemDescription;
	std::string m_itemImagePath;
	ITEM_ID m_itemID;
	ITEM_TYPE m_itemType;
	float m_itemDuration;
	Mesh * m_itemMesh;
};

#endif

