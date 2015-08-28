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

	for(unsigned int i = 0; i < m_itemList.size(); ++i)
	{
		delete m_itemList[i];
	}
	m_itemList.clear();

	for(unsigned i = 0; i < m_guiList.size(); ++i)
	{
		delete m_guiList[i];
	}
	m_guiList.clear();
}

void ModelHandler::Init() //Anything that moves in the game
{
	Math::InitRNG();

	player = new Player("Josh");
	player->setPosition(Vector3(32,-32, 0));

	camera.Init(Vector3(-256,-256,416),Vector3(-256,-256,0),Vector3(0,1,0));
	
	m_status = STATE_MENU;
	currentWorld = WORLD_SIGHT_TUTORIAL;

	// MAIN MENU
	World* newWorld = new World(WORLD_MAINMENU);
	m_worldList.push_back(newWorld);

	// Give a 10 space buffer to the top and left for corridors

	Room* newRoom = new Room(ROOM_MAINMENU, 800, 1024, 26, 32, 800, 1024,32,TILESET_MAIN_MENU, 10, 30, 0);
	newRoom->LoadMap("MapData//Main_Menu//MainMenu_Foreground.csv","MapData//Main_Menu//MainMenu_Scenery.csv","MapData//Main_Menu//MainMenu_Background.csv","MapData//Main_Menu//MainMenu_Background.csv");
	m_worldList[0]->m_roomList.push_back(newRoom);

	// TEST WORLD
	newWorld = new World(WORLD_TEST);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 10, 30, 0);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 30, 40, 1);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 50, 70, 2);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_MECH);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_MECH, 928, 768, 29, 24, 928, 768,32,TILESET_POOL, 10, 30, 0);
	newRoom->addExit(EXIT_LEFT);
	newRoom->LoadMap("MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv");
	m_worldList[2]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_MECH, 928, 768, 29, 24, 928, 768,32,TILESET_POOL, 80, 80, 1);
	newRoom->addExit(EXIT_RIGHT);
	newRoom->LoadMap("MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv");
	m_worldList[2]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_FRIENDS_TUTORIAL);
	m_worldList.push_back(newWorld);
	
	newRoom = new Room(ROOM_TUTORIAL_FRIENDS, 896, 1408, 44, 28, 896, 1408,32,TILESET_BLUE, 20, 20, 0);
	//newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Friends//Friends_Tutorial_Foreground.csv","MapData//Friends//Friends_Tutorial_Scenery.csv","MapData//Friends//Friends_Tutorial_Background.csv","MapData//Friends//Friends_Tutorial_Background.csv");
	m_worldList[3]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_SIGHT_TUTORIAL);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_TUTORIAL_FRIENDS, 800, 1024, 32, 25, 800, 1024,32,TILESET_RED, 20, 20, 0);
	//newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT2//tutorial//lib_foreground.csv","MapData//NIGHT2//tutorial//lib_scenery.csv","MapData//NIGHT2//tutorial//lib_backgorund.csv","MapData//NIGHT2//tutorial//lib_backgorund.csv");
	m_worldList[4]->m_roomList.push_back(newRoom);

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

	//Enemy Code
	Evil = new EnemyMelee;
	Evil->SetPos(32,-32);
	Evil->SetData(m_worldList[currentWorld]->collisionData);
	Evil->SetDelay(0.1);
	
}

bool ModelHandler::InitObjects()
{
	GameObject * object = new GameObject("Test Animation");
	object->addMesh(MeshBuilder::GenerateSpriteAnimation("Test Animation",1,3,24.f,48.f));
	object->getMesh()->textureArray[0] = LoadTGA("Images//playerTest.tga");    //Current State 
	m_objectList.push_back(object);
	SpriteAnimation *playerAnimation = dynamic_cast<SpriteAnimation*>(m_objectList[0]->getMesh());
	if(playerAnimation)
	{
		playerAnimation->m_anim = new Animation();
		playerAnimation->m_anim->Set(0,2,0,0.1f);
	}

	object = new GameObject("Axes");
	object->addMesh(MeshBuilder::GenerateAxes("Axes", 100000, 100000, 100000));
	m_objectList.push_back(object);

	//DON'T PUSH ANYTHING ELSE

	object = new GameObject("Main Menu", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[0]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[0]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[0]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	m_objectList.push_back(object);

	object = new GameObject("Test Puzzle World", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[1]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[1]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[1]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	m_objectList.push_back(object);

	object = new GameObject("Test Mech World", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[2]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_POOL.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[2]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_POOL.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[2]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_POOL.tga");
	m_objectList.push_back(object);

	object = new GameObject("Friends Tutorial", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[3]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[3]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[3]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	m_objectList.push_back(object);

	object = new GameObject("Sight Tutorial", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[4]->backgroundData,32,48));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[4]->sceneryData,32,48));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[4]->foregroundData,32,48));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	m_objectList.push_back(object);

	object = new GameObject("Game Text Foxscript",TYPE_TEXT);
	object->addMesh(MeshBuilder::GenerateText("Game Text Foxscript",16,16));
	object->getMesh()->textureID = LoadTGA("Images//Fonts//foxscript.tga");
	m_objectList.push_back(object);

	object = new GameObject("Game Text Basis", TYPE_TEXT);
	object->addMesh(MeshBuilder::GenerateText("Game Text Basis",16,16));
	object->getMesh()->textureID = LoadTGA("Images//Fonts//basis33.tga");
	m_objectList.push_back(object);

	object = new GameObject("Enemy", TYPE_ENEMY, Vector3(Evil->GetPos_x(),Evil->GetPos_y(),0.f));
	object->addMesh(MeshBuilder::GenerateQuad("Enemy",Color(1.f,0.f,0.f),32.f));
	m_objectList.push_back(object);

	Item * testItem = new Item("Test Item 1",ITEM_REDUCE_FEAR_POTION);
	testItem->setDescription("Just a test item :D");
	m_itemList.push_back(testItem);

	testItem = new Item("Test Item 2");
	testItem->setDescription("Equipment Test");
	m_itemList.push_back(testItem);

	//std::cout << m_itemList[0]->toString() << std::endl;

	//ITEM INVENTORY TESTING
	this->getPlayer()->getInventory().addItem(m_itemList[0]);                                         //ADD ITEM (Consumable)
	this->getPlayer()->getInventory().addItem(m_itemList[1]);                                         //ADD ITEM (Equipment)
	//std::cout << this->getPlayer()->getInventory().getItem(1)->toString() << std::endl; //GET NAME OF ITEM
	//this->getPlayer()->getInventory().removeItem(1);                                                       //REMOVE ITEM FROM INVENTORY

	Gui * newGui = new Gui("Test Border","Images//UI//Item_Border.tga");
	m_guiList.push_back(newGui);

	newGui = new Gui("Fear Border","Images//UI//Fear_Border.tga");
	m_guiList.push_back(newGui);

	newGui = new Gui("Fear","Images//UI//Fear.tga");
	m_guiList.push_back(newGui);

	return true;
}

void ModelHandler::Update(const double dt)
{
	camera.Update(dt);

	/*std::cout << "Start" << std::endl;
	for(int i = 0; i < m_worldList[currentWorld]->sceneryData.size(); ++i)
		{
			for(int j = 0; j < m_worldList[currentWorld]->sceneryData[i].size(); ++j)
			{
				std::cout << Mszm_worldList[currentWorld]->collisionData[i][j] << " ";
			}
			std::cout << std::endl;
		}
	std::cout << "End" << std::endl;

	system("pause");*/

	player->update(dt,m_worldList[currentWorld], m_worldList[currentWorld]->getRoom(player->getPosition().x, player->getPosition().y));
	//std::cout << (player->getPosition().x) << " " << (player->getPosition().y) << std::endl;
	//std::cout << (int)((player->getPosition().x)/32) << " "  << (int)((player->getPosition().y)/32) << std::endl;

	if (m_worldList[currentWorld]->UpdateWorld)
	{
		if (currentWorld == WORLD_FRIENDS_TUTORIAL)
		{
			m_objectList[currentWorld+2]->setMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[currentWorld]->sceneryData,32,32), 1);
			m_objectList[currentWorld+2]->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
		}
		m_worldList[currentWorld]->UpdateWorld = false;
	}


	//Enemy Code
	Evil->Update(player, dt); 
	m_objectList[9]->setPosition(Vector3(Evil->GetPos_x(),Evil->GetPos_y(),0));
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
