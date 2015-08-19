#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Object.h"
#include "Geometry.h"
#include "MeshBuilder.h"

#include <vector>

using std::vector;

class GameObject : public Object
{
public:
	GameObject(std::string m_objectName);
	~GameObject();

	float mass;
	bool isAlive;
	bool isVisible;
	bool isCollidable;
	bool isLightAffected;
	bool isFogAffected;
	bool makesNoise;
	vector<std::string> textures;

	BoundingBox &getBoundingBox();
	
	bool isStatic();

	operator bool()
	{
		return isAlive;
	}

	void setPosition(Vector3 pos);
	Vector3 getPosition();

	void setVelocity(Vector3 velocity);
	Vector3 getVelocity();

	void addMesh(Mesh* mesh)
	{
		m_objectMesh.push_back(mesh);
	}

	Mesh* getMesh(int i = 0)
	{
		return this->m_objectMesh[i];
	}

	void setStatic(bool status);
protected:
	Vector3 m_objectPosition;
	Vector3 m_objectVelocity;

	BoundingBox m_boundingBox;
	std::vector<Mesh*> m_objectMesh;
private:
	bool m_bStatic;
};

#endif