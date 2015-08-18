#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <iostream>

#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "MeshBuilder.h"
#include "Map.h"

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

	Camera getCamera();

	void Init();
	void Update(const double dt);

	Game getEnvironment();
	Player  *getPlayer();

	GAME_STATE m_status;

	MAP_ID currentMap;

	vector<GameObject*> m_buttonList; //GUI Class <- Create
	vector<Mesh*> m_boundingBoxList; //Keep track of bounding boxes in model
	vector<CMap*> m_mapList;
private:
	Player  *player;
	Camera camera;
	Game theEnvironment; //Contains gravity, current conditions(wind) etc.
};

#endif
