#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	std::cout << "Model Handler Initialized" << std::endl;
}

ModelHandler::~ModelHandler(void)
{
	for(unsigned int i = 0; i < m_worldList.size(); ++i)
	{
		delete m_worldList[i];
	}
	m_worldList.clear();

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
	player->setPosition(Vector3(256, 256, 0));

	camera.Init(Vector3(0,0,416),Vector3(0,0,0),Vector3(0,1,0));
	
	m_status = STATE_MENU;
	currentWorld = WORLD_MAINMENU;

	World* newWorld = new World(WORLD_MAINMENU);
	m_worldList.push_back(newWorld);

	Room* newRoom = new Room(ROOM_MAINMENU);
	newRoom->Init(800, 1024, 26, 32, 800, 1024,32,TILESET_MAIN_MENU);
	newRoom->LoadMap("MapData//Main_Menu//MainMenu_Foreground.csv","MapData//Main_Menu//MainMenu_Scenery.csv","MapData//Main_Menu//MainMenu_Background.csv","MapData//MapData//Main_Menu//MainMenu_Background.csv");
	m_worldList[0]->m_roomList.push_back(newRoom);	
}

bool ModelHandler::InitObjects()
{
	GameObject * object = new GameObject("Test Object");
	object->addMesh(MeshBuilder::GenerateQuad("Test Object",Color(0.f,0.f,1.f),32.f));
	object->setPosition(Vector3(0.f,0.f,0.f));
	m_objectList.push_back(object);

	object = new GameObject("Axes");
	object->addMesh(MeshBuilder::GenerateAxes("Axes", 100000, 100000, 100000));
	m_objectList.push_back(object);

	object = new GameObject("Main Menu", TYPE_MAP);
	object->addMesh(MeshBuilder::GenerateTileMap("Main Menu Background",Color(0.f,0.f,0.f),m_worldList[0]->m_roomList[0]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MainMenu.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Main Menu Scenery",Color(0.f,0.f,0.f),m_worldList[0]->m_roomList[0]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MainMenu.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Main Menu Foreground",Color(0.f,0.f,0.f),m_worldList[0]->m_roomList[0]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MainMenu.tga");
	m_objectList.push_back(object);

	/*m_meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation("Placeholder", 1, 3, 24.f, 48.f);
	m_meshList[GEO_PLAYER]->textureID = LoadTGA("Images//playerTest.tga");
	SpriteAnimation *sa19 = dynamic_cast<SpriteAnimation*>(m_meshList[GEO_PLAYER]);
	if (sa19)
	{
		sa19->m_anim = new Animation();
		sa19->m_anim->Set(0, 2, 0, 0.25f);
	}*/

	return true;
}

void ModelHandler::Update(const double dt)
{
	camera.Update(dt);
	player->update(dt,m_worldList[currentWorld], m_worldList[currentWorld]->getRoom(player->getPosition().x, player->getPosition().y));
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
