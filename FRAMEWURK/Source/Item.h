#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	Item(void);
	~Item(void);

	void toString();
	std::string getDescription();
	int getItemID();

private:
	std::string m_itemName;
	std::string m_itemDescription;
	int m_itemID;

};

#endif

