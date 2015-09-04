#include "GameObject.h"

GameObject::GameObject(std::string m_objectName, OBJECT_TYPE objectType, Vector3 objectPosition) : m_bStatic(false),
	isAlive(false),
	isVisible(false),
	isCollidable(false),
	isLightAffected(false),
	isFogAffected(false),
	makesNoise(false),
	m_boundingBox(0.0f,0.0f,0.0f, 0.0f,0.0f,0.0f),
	mass(0.0f),
	m_objectPosition(0,0,0),
	m_objectVelocity(0,0,0),
	m_objectType(objectType)
{
	this->setName(m_objectName);
	this->setObjectType(objectType);
	this->setPosition(objectPosition);
	textures.push_back("Images//unknown.tga");
}

GameObject::~GameObject()
{
	//todo delete object
}

BoundingBox & GameObject::getBoundingBox()
{
	return this->m_boundingBox;
}

void GameObject::setStatic(bool status)
{
	this->m_bStatic = status;
}

bool GameObject::isStatic()
{
	return m_bStatic;
}

void GameObject::setPosition(Vector3 pos)
{
	this->m_objectPosition.x = pos.x;
	this->m_objectPosition.y = pos.y;
	this->m_objectPosition.z = pos.z;
}

Vector3 GameObject::getPosition()
{
	return this->m_objectPosition;
}

void GameObject::setVelocity(Vector3 vel)
{
	this->m_objectVelocity.x = vel.x;
	this->m_objectVelocity.y = vel.y;
	this->m_objectVelocity.z = vel.z;
}

Vector3 GameObject::getVelocity()
{
	return this->m_objectVelocity;
}

Mesh* GameObject::getMesh(int i)
{
	return this->m_objectMesh[i];
}

int GameObject::getMeshSize()
{
	return this->m_objectMesh.size();
}

void GameObject::setObjectType(OBJECT_TYPE type)
{
	this->m_objectType = type;
}

OBJECT_TYPE GameObject::getObjectType()
{
	return this->m_objectType;
}