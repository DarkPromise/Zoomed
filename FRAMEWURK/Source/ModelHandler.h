#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <iostream>

#include "Define.h"
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
#include "EnemyFather.h"
#include "EnemyDasher.h"
#include "EnemyGhost.h"
#include "Sound.h"
#include "Textbox.h"

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

	EnemyFriend* getFriend();
	EnemyFather* getFather();
	EnemyDasher* getDash()
	{
		return this->Dash;
	}
	EnemyGhost* getGhost()
	{
		return this->Ghost;
	}

	std::vector<Enemy*> m_enemyList;

	GAME_STATE m_status;

	WORLD_ID currentWorld;

	Sound* sound;
	//vector<GameObject*> m_buttonList; //GUI Class <- Create

	vector<GameObject*> m_objectList;
	//Mesh* m_meshList[NUM_GEOMETRY];

	//vector<CMap*> m_mapList;
	vector<World*> m_worldList;
	vector<Item*> m_itemList;
	vector<Gui*> m_guiList;

	int &getCurrLevel()
	{
		return m_currLevel;
	}

	CTextBox* getTextBox()
	{
		return this->TextBox;
	}
private:
	Player  *player;
	EnemyFriend* Friend;
	EnemyFather* Father;
	EnemyDasher * Dash;
	EnemyGhost * Ghost;

	CTextBox* TextBox;

	int m_currLevel;

	Camera camera;
	Game theEnvironment; //Contains gravity, current conditions(wind) etc.
};

#endif
