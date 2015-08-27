#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "AxisAlignedBoundingBox.h"

class Object
{
public:
	Object() {}
	~Object() {} //TODO delete object

	void setObjectID(int id)
	{
		this->m_objectID = id;
	}

	int getObjectID()
	{
		return m_objectID;
	}

	void setName(std::string name)
	{
		this->m_objectName = name;
	}

	std::string ToString()
	{
		return m_objectName;
	}
private:
	int m_objectID;
	std::string m_objectName;
};

#endif