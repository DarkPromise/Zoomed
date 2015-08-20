#include "ModelHandler.h"
#include "MyMath.h"

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

	for(unsigned int i = 0; i < m_itemList.size(); ++i)
	{
		delete m_itemList[i];
	}
	m_itemList.clear();
}

void ModelHandler::Init() //Anything that moves in the game
{
	Math::InitRNG();

	player = new Player("Josh");
	player->setPosition(Vector3(256, 256, 0));

	camera.Init(Vector3(-256,-256,416),Vector3(-256,-256,0),Vector3(0,1,0));
	
	m_status = STATE_MENU;
	currentWorld = WORLD_MAINMENU;

	// MAIN MENU
	World* newWorld = new World(WORLD_MAINMENU);
	m_worldList.push_back(newWorld);

	// Give a 10 space buffer to the top and left for corridors

	Room* newRoom = new Room(ROOM_MAINMENU, 800, 1024, 26, 32, 800, 1024,32,TILESET_MAIN_MENU, 10, 10);
	newRoom->LoadMap("MapData//Main_Menu//MainMenu_Foreground.csv","MapData//Main_Menu//MainMenu_Scenery.csv","MapData//Main_Menu//MainMenu_Background.csv","MapData//Main_Menu//MainMenu_Background.csv");
	m_worldList[0]->m_roomList.push_back(newRoom);

	// TEST WORLD
	newWorld = new World(WORLD_TEST);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 10, 20);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 30, 10);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 50, 40);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	m_worldList[1]->m_roomList[2]->generateRoom();

	for (unsigned i = 0; i < m_worldList.size(); i++)
	{
		for (unsigned j = 0; j < m_worldList[i]->m_roomList.size(); j++)
		{
			m_worldList[i]->m_roomList[j]->generateRoom();
		}
	}

	for (unsigned i = 0; i < m_worldList.size(); i++)
	{
		m_worldList[i]->initWorld();
	}
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

	/*object = new GameObject("Main Menu", TYPE_MAP, Vector3((float)(m_worldList[0]->m_roomList[0]->getWorldPositionX()*m_worldList[0]->m_roomList[0]->GetTileSize()), (float)(m_worldList[0]->m_roomList[0]->getWorldPositionY()*m_worldList[0]->m_roomList[0]->GetTileSize()), 0));
	object->addMesh(MeshBuilder::GenerateTileMap("Main Menu Background",Color(0.f,0.f,0.f),m_worldList[0]->m_roomList[0]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Main Menu Scenery",Color(0.f,0.f,0.f),m_worldList[0]->m_roomList[0]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Main Menu Foreground",Color(0.f,0.f,0.f),m_worldList[0]->m_roomList[0]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	m_objectList.push_back(object);*/

	/*object = new GameObject("Puzzle Test Room", TYPE_MAP, Vector3((float)(m_worldList[1]->m_roomList[0]->getWorldPositionX()*m_worldList[1]->m_roomList[0]->GetTileSize()), (float)(m_worldList[1]->m_roomList[0]->getWorldPositionY()*m_worldList[1]->m_roomList[0]->GetTileSize()), 0));
	object->addMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[0]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Test Scenery",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[0]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Test Foreground",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[0]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	m_objectList.push_back(object);

	object = new GameObject("Puzzle Test Room 2", TYPE_MAP, Vector3((float)(m_worldList[1]->m_roomList[1]->getWorldPositionX()*m_worldList[1]->m_roomList[1]->GetTileSize()), (float)(m_worldList[1]->m_roomList[1]->getWorldPositionY()*m_worldList[1]->m_roomList[1]->GetTileSize()), 0));
	object->addMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[1]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Test Scenery",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[1]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Test Foreground",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[1]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	m_objectList.push_back(object);

	object = new GameObject("Puzzle Test Room 3", TYPE_MAP, Vector3((float)(m_worldList[1]->m_roomList[2]->getWorldPositionX()*m_worldList[1]->m_roomList[2]->GetTileSize()), (float)(m_worldList[1]->m_roomList[2]->getWorldPositionY()*m_worldList[1]->m_roomList[2]->GetTileSize()), 0));
	object->addMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[2]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Test Scenery",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[2]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Test Foreground",Color(0.f,0.f,0.f),m_worldList[1]->m_roomList[2]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	m_objectList.push_back(object);*/

	object = new GameObject("Test World", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[1]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[1]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[1]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	m_objectList.push_back(object);

	/*m_meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation("Placeholder", 1, 3, 24.f, 48.f);
	m_meshList[GEO_PLAYER]->textureID = LoadTGA("Images//playerTest.tga");
	SpriteAnimation *sa19 = dynamic_cast<SpriteAnimation*>(m_meshList[GEO_PLAYER]);
	if (sa19)
	{
		sa19->m_anim = new Animation();
		sa19->m_anim->Set(0, 2, 0, 0.25f);
	}*/

	Item * testItem = new Item("Test Item");
	testItem->setDescription("Just a test item :D");
	m_itemList.push_back(testItem);

	std::cout << m_itemList[0]->toString() << std::endl;

	//ITEM INVENTORY TESTING
	this->getPlayer()->getInventory().addItem(m_itemList[0]);                                         //ADD ITEM  
	std::cout << this->getPlayer()->getInventory().getItem(1)->toString() << std::endl; //GET NAME OF ITEM
	this->getPlayer()->getInventory().removeItem(1);                                                       //REMOVE ITEM FROM INVENTORY

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
