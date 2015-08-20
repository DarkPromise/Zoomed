#ifndef ITEM_H
#define ITEM_H

#include <string>

enum ITEM_ID //Used for Item Effect
{ 
	ITEM_REDUCE_NOISE_POTION,
	ITEM_REDUCED_NOISE_GAIN_POTION,
	ITEM_SIGHT_POTION,
	ITEM_REDUCED_FEAR_GAIN_POTION,
	ITEM_REDUCE_FEAR_POTION,
	ITEM_SUPPRESS_FEAR_POTION,

	ITEM_EQUIPMENT_BOOTS,
	ITEM_EQUIPMENT_GLASSES,
	ITEM_EQUIPMENT_ARMOR,
	ITEM_EQUIPMENT_INVISCLOAK,
};

class Item
{
public:
	Item(std::string itemName, ITEM_ID itemID);
	~Item(void);

	void renameItem(std::string reName);
	std::string toString();
	void setDescription(std::string itemDescription);
	std::string getDescription();
	ITEM_ID getItemID();

private:
	std::string m_itemName;
	std::string m_itemDescription;
	ITEM_ID m_itemID;

};

#endif

