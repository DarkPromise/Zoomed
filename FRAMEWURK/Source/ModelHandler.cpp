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
	for(unsigned int i = 0; i < m_objectList.size(); ++i)
	{
		delete m_objectList[i];
	}
	m_objectList.clear();

	for(unsigned int i = 0; i < NUM_GEOMETRY; ++i)
	{
		delete m_meshList[i];
	}
}

void ModelHandler::Init() //Anything that moves in the game
{
	player = new Player("Josh");
	player->setPosition(Vector3(0,0,0));

	camera.Init(Vector3(0,0,416),Vector3(0,0,0),Vector3(0,1,0));

	m_status = STATE_MENU;
	currentMap = MAP_MAIN_MENU;

	CMap * newMap = new CMap();
	newMap->Init( 800, 1024, 26, 32, 800, 1024,32,TILESET_MAIN_MENU);
	newMap->setMapID(MAP_MAIN_MENU);
	newMap->LoadMap("MapData//Main_Menu//MainMenu_Foreground.csv","MapData//Main_Menu//MainMenu_Scenery.csv","MapData//Main_Menu//MainMenu_Background.csv","MapData//MapData//Main_Menu//MainMenu_Background.csv");
	m_mapList.push_back(newMap);
}

bool ModelHandler::InitObjects()
{
	GameObject * object = new GameObject("Test Object");
	object->addMesh(MeshBuilder::GenerateQuad("Test Object",Color(0.f,0.f,1.f),10.f));
	//object->getMesh(<you can put in index>)->textureArray = LoadTGA....
	object->setPosition(Vector3(0.f,0.f,0.f));
	m_objectList.push_back(object);
	return true;
}

void ModelHandler::Update(const double dt)
{
	camera.Update(dt);
	player->update(dt,m_mapList[currentMap]);
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
