#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <iostream>

#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "MeshBuilder.h"
#include "World.h"
#include "Geometry.h"
#include "LoadTGA.h"
#include "Item.h"
#include "Gui.h"
#include "EnemyMelee.h"
#include "EnemyFriend.h"

/************************************************

SHOULD CONTAIN EVERYTHING ELSE.

************************************************/
enum GAME_STATE
{
	STATE_MENU,
	STATE_INSTRUCTIONS,
	STATE_GAMESTART,
	STATE_EXIT
};

enum AI_STATE
{

};

class ModelHandler
{
public:
	ModelHandler();
	~ModelHandler();

	ModelHandler *getInstance()
	{
		return this;
	}

	Camera getCamera();

	void Init();
	bool InitObjects();
	void Update(const double dt);

	Game getEnvironment();
	Player *getPlayer();

	//Enemy Code
	double EnemyDelay;

	Enemy* Evil;
	Enemy* Friend;

	std::vector<Enemy*> m_enemyList;


	GAME_STATE m_status;

	WORLD_ID currentWorld;

	//vector<GameObject*> m_buttonList; //GUI Class <- Create

	vector<GameObject*> m_objectList;
	//Mesh* m_meshList[NUM_GEOMETRY];

	//vector<CMap*> m_mapList;
	vector<World*> m_worldList;
	vector<Item*> m_itemList;
	vector<Gui*> m_guiList;


private:
	Player  *player;
	Camera camera;
	Game theEnvironment; //Contains gravity, current conditions(wind) etc.
};

#endif
