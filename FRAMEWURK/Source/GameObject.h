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
	TYPE_TEXT,
	TYPE_TEXTBOX,
};

enum OBJECT_LIST
{
	OBJ_PLAYER,
	OBJ_AXES,
	OBJ_MAINMENU,
	OBJ_PUZZLE,
	OBJ_MECH,
	OBJ_SIGHT01,
	OBJ_SIGHT02,
	OBJ_SIGHT03,
	OBJ_FRIEND01,
	OBJ_FRIEND02,
	OBJ_FRIEND03,
	OBJ_SCHOOL01,
	OBJ_FONTONRYOU,
	OBJ_FONTBASIS33,
	OBJ_ENEMY,
	OBJ_ENEMYSISTER,
	OBJ_ENEMYFATHER,
	OBJ_DASHER,
	OBJ_GHOST,
	OBJ_TEXTBOX1, // unfinished
	OBJ_TEXTBOX2,
	OBJ_MECH1,
	OBJ_MECH2,
	OBJ_MECH3,
	OBJ_MECH4
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