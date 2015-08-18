#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	std::cout << "Model Handler Initialized" << std::endl;
}

ModelHandler::~ModelHandler(void)
{
	for(unsigned int i = 0; i < m_mapList.size(); ++i)
	{
		delete m_mapList[i];
	}
	m_mapList.clear();
}

void ModelHandler::Init() //Anything that moves in the game
{
	player = new Player("Josh");
	player->setPosition(Vector3(0,0,0));

	camera.Init(Vector3(0,0,10),Vector3(0,0,0),Vector3(0,1,0));

	m_status = STATE_MENU;

	CMap * newMap = new CMap();
	newMap->Init( 800, 1024, 26, 32, 800, 1024,32,TILESET_MAIN_MENU);
	newMap->setMapID(MAP_MAIN_MENU);
	newMap->LoadMap("MapData//MainMenu.csv","MapData//MainMenu.csv","MapData//MainMenu.csv","MapData//MainMenu.csv");
	m_mapList.push_back(newMap);
}

void ModelHandler::Update(const double dt)
{
	camera.Update(dt);
	player->update(dt);
}

Camera ModelHandler::getCamera()
{
	return this->camera;
}

Game ModelHandler::getEnvironment()
{
	return this->theEnvironment;
}

Player * ModelHandler::getPlayer()
{
	return this->player;
}
