#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Object.h"
#include "Geometry.h"
#include "MeshBuilder.h"

#include <vector>

using std::vector;

enum OBJECT_TYPE
{
	TYPE_PLAYER = 0,
	TYPE_ENEMY,
	TYPE_MAP,
	TYPE_OBJECT,
	TYPE_LIGHT_STENCIL,
};

class GameObject : public Object
{
public:
	GameObject(std::string m_objectName, OBJECT_TYPE objectType = TYPE_OBJECT, Vector3 objectPosition = Vector3(0, 0, 0));
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

	void setMesh(Mesh* mesh, int index)
	{
		m_objectMesh[index] = mesh;
	}

	Mesh* getMesh(int i = 0);
	int getMeshSize();

	void setObjectType(OBJECT_TYPE type);
	OBJECT_TYPE getObjectType();

	void setStatic(bool status);
protected:
	Vector3 m_objectPosition;
	Vector3 m_objectVelocity;

	BoundingBox m_boundingBox;
	std::vector<Mesh*> m_objectMesh;

	OBJECT_TYPE m_objectType;
private:
	bool m_bStatic;
};

#endif