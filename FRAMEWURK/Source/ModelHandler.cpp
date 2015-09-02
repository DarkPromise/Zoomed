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

	for(unsigned int i = 0; i < m_enemyList.size(); ++i)
	{
		delete m_enemyList[i];
	}
	m_enemyList.clear();
}

void ModelHandler::Init() //Anything that moves in the game
{
	Math::InitRNG();

	sound = new Sound();

	player = new Player("Josh");
	player->setPosition(Vector3(800,-1248, 0));

	camera.Init(Vector3(-256,-256,416),Vector3(-256,-256,0),Vector3(0,1,0));
	
	m_status = STATE_MENU;
	m_currLevel = 0;
	currentWorld = WORLD_MAINMENU;

	// MAIN MENU
	World* newWorld = new World(WORLD_MAINMENU);
	m_worldList.push_back(newWorld);

	// Give a 10 space buffer to the top and left for corridors

	Room* newRoom = new Room(ROOM_MAINMENU, 800, 1024, 26, 32, 800, 1024,32,TILESET_MAIN_MENU, 10, 50, 0);
	newRoom->LoadMap("MapData//Main_Menu//MainMenu_Foreground.csv","MapData//Main_Menu//MainMenu_Scenery.csv","MapData//Main_Menu//MainMenu_Background.csv","MapData//Main_Menu//MainMenu_Background.csv");
	m_worldList[0]->m_roomList.push_back(newRoom);

	// TEST WORLD
	newWorld = new World(WORLD_TEST);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 10, 50, 0);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 30, 60, 1);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TESTPUZZLE, 512, 512, 16, 16, 512, 512,32,TILESET_ROOMS, 50, 90, 2);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv","MapData//NIGHT3//P_ROOM_ONE_BACKGROUND.csv");
	m_worldList[1]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_MECH);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_MECH, 928, 768, 29, 24, 928, 768,32,TILESET_POOL, 10, 50, 0);
	newRoom->addExit(EXIT_LEFT);
	newRoom->LoadMap("MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv");
	m_worldList[2]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_MECH, 928, 768, 29, 24, 928, 768,32,TILESET_POOL, 80, 100, 1);
	newRoom->addExit(EXIT_RIGHT);
	newRoom->LoadMap("MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv","MapData//MECH//Background.csv");
	m_worldList[2]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_SIGHT_TUTORIAL);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_TUTORIAL_SIGHT, 800, 1024, 32, 25, 800, 1024,32,TILESET_RED, 20, 40, 0);
	//newRoom->addExit(EXIT_UP);
	//newRoom->addExit(EXIT_UP);
	newRoom->LoadMap("MapData//Sight//1//lib_foreground.csv","MapData//Sight//1//lib_scenery.csv","MapData//Sight//1//lib_backgorund.csv","MapData//Sight//1//lib_backgorund.csv");
	m_worldList[3]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_SIGHT_02);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_TWO_01_SIGHT, 800, 1024, 32, 25, 800, 1024,32,TILESET_RED, 20, 40, 0);
	//newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Sight//2//artRoom_foreground.csv","MapData//Sight//2//artRoom_scenery.csv","MapData//Sight//2//artRoom_backgorund.csv","MapData//Sight//2//artRoom_backgorund.csv");
	m_worldList[4]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_TWO_02_SIGHT, 800, 1056, 33, 25, 800, 1056,32,TILESET_RED, 20, 80, 1);
	//newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Sight//2//hiddenRoom_foreground.csv","MapData//Sight//2//hiddenRoom_scenery.csv","MapData//Sight//2//hiddenRoom_backgorund.csv","MapData//Sight//2//hiddenRoom_backgorund.csv");
	m_worldList[4]->m_roomList.push_back(newRoom);
	
	newWorld = new World(WORLD_SIGHT_03);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_THREE_01_SIGHT, 800, 1024, 32, 25, 800, 1024,32,TILESET_RED, 20, 40, 0);
	newRoom->addExit(EXIT_RIGHT);
	newRoom->LoadMap("MapData//Sight//3//arrowRoom_foreground.csv","MapData//Sight//3//arrowRoom_scenery.csv","MapData//Sight//3//arrowRoom_backgorund.csv","MapData//Sight//3//arrowRoom_backgorund.csv");
	m_worldList[5]->m_roomList.push_back(newRoom);
	
	newRoom = new Room(ROOM_THREE_02_SIGHT, 800, 1024, 32, 25, 800, 1024,32,TILESET_RED, 20, 80, 1);
	newRoom->addExit(EXIT_UP);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Sight//3//pianoRoom_foreground.csv","MapData//Sight//3//pianoRoom_scenery.csv","MapData//Sight//3//pianoRoom_backgorund.csv","MapData//Sight//3//pianoRoom_backgorund.csv");
	m_worldList[5]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_THREE_03_SIGHT, 800, 1024, 32, 25, 800, 1024,32,TILESET_RED, 20, 120, 2);
	//newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Sight//3//ritualRoom_foreground.csv","MapData//Sight//3//ritualRoom_scenery.csv","MapData//Sight//3//ritualRoom_backgorund.csv","MapData//Sight//3//ritualRoom_backgorund.csv");
	m_worldList[5]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_FRIENDS_TUTORIAL);
	m_worldList.push_back(newWorld);
	
	newRoom = new Room(ROOM_FRIENDS_TUTORIAL, 896, 1920, 60, 28, 896, 1920,32,TILESET_BLUE, 20, 40, 0);
	//newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Friends//Friends_Tutorial_Foreground.csv","MapData//Friends//Friends_Tutorial_Scenery.csv","MapData//Friends//Friends_Tutorial_Background.csv","MapData//Friends//Friends_Tutorial_Background.csv");
	m_worldList[6]->m_roomList.push_back(newRoom);

	newWorld = new World(WORLD_FRIENDS_LEVEL1);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_FRIENDS_CLASSROOM_SYMMETRY, 576, 992, 18, 31, 576, 992, 32, TILESET_BLUE, 20, 40, 0);
	newRoom->addExit(EXIT_DOWN);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Friends//Classroom//Classroom_1_Foreground.csv","MapData//Friends//Classroom//Classroom_1_Scenery.csv","MapData//Friends//Classroom//Classroom_1_Background.csv","MapData//Friends//Classroom//Classroom_1_Background.csv");
	m_worldList[7]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_FRIENDS_TOILET, 352, 608, 11, 19, 352, 608, 32, TILESET_BLUE, 20, 70, 1);
	newRoom->addExit(EXIT_RIGHT);
	newRoom->LoadMap("MapData//Friends//Toilet//FRIEND_TOLIET_Foreground.csv","MapData//Friends//Toilet//FRIEND_TOLIET_Scenery.csv","MapData//Friends//Toilet//FRIEND_TOLIET_Background.csv","MapData//Friends//Toilet//FRIEND_TOLIET_Background.csv");
	m_worldList[7]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_FRIENDS_ROOM_ONE, 416, 448, 14, 13, 416, 448, 32, TILESET_BLUE, 30, 90, 2);
	newRoom->addExit(EXIT_DOWN);
	newRoom->LoadMap("MapData//Friends//Room1//Room_1_Foreground.csv","MapData//Friends//Room1//Room_1_Scenery.csv","MapData//Friends//Room1//Room_1_Background.csv","MapData//Friends//Room1//Room_1_Background.csv");
	m_worldList[7]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_FRIENDS_ROOM_TWO, 352, 608, 11, 19, 352, 608, 32, TILESET_BLUE, 30, 110, 3);
	newRoom->addExit(EXIT_RIGHT);
	newRoom->addExit(EXIT_LEFT);
	newRoom->LoadMap("MapData//Friends//Room2//Room_2_Foreground.csv","MapData//Friends//Room2//Room_2_Scenery.csv","MapData//Friends//Room2//Room_2_Background.csv","MapData//Friends//Room2//Room_2_Background.csv");
	m_worldList[7]->m_roomList.push_back(newRoom);

	newRoom = new Room(ROOM_FRIENDS_ROOM_THREE, 704, 448, 23, 14, 704, 448, 32, TILESET_BLUE, 50, 70, 4);
	newRoom->addExit(EXIT_UP);
	newRoom->addExit(EXIT_LEFT);
	newRoom->LoadMap("MapData//Friends//Room3//Room_3_Foreground.csv","MapData//Friends//Room3//Room_3_Scenery.csv","MapData//Friends//Room3//Room_3_Background.csv","MapData//Friends//Room3//Room_3_Background.csv");
	m_worldList[7]->m_roomList.push_back(newRoom);

	//School World
	newWorld = new World(WORLD_SCHOOL_LEVEL1);
	m_worldList.push_back(newWorld);

	newRoom = new Room(ROOM_SCHOOL_MAIN, 2336, 1216, 74, 38, 2336, 1216, 32, TILESET_RED, 2, 26, 0);
	//newRoom->addExit(EXIT_RIGHT);
	newRoom->LoadMap("MapData//Night1//Level1//Main//Main_Foreground.csv","MapData//Night1//Level1//Main//Main_Scenery.csv","MapData//Night1//Level1//Main//Main_Background.csv","MapData//Night1//Level1//Main//Main_Background.csv");
	m_worldList[WORLD_SCHOOL_LEVEL1]->m_roomList.push_back(newRoom);

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
		std::cout << i << std::endl;
	}

	//Enemy Code
	Evil = new EnemyMelee;
	Evil->SetPos(32,-32);
	Evil->SetData(m_worldList[currentWorld]->collisionData);
	Evil->SetDelay(0.1);

	Friend = new EnemyFriend();
	Friend->SetPos(736, -1120);
	Friend->SetData(m_worldList[WORLD_FRIENDS_TUTORIAL]->collisionData);
	Friend->SetDelay(player->getMovementDelay());

	Father = new EnemyFather();
	Father->SetData(m_worldList[WORLD_FRIENDS_TUTORIAL]->collisionData);
	Father->SetDelay(0.5);

	EnemyDasher * dash = new EnemyDasher();
	dash->SetPos(1152.f,-480.f);
	dash->SetData(m_worldList[WORLD_SCHOOL_LEVEL1]->collisionData);
	m_enemyList.push_back(dash);

	EnemyGhost* ghost = new EnemyGhost();
	ghost->SetPos(320.f,-2080.f);
	ghost->SetData(m_worldList[WORLD_SCHOOL_LEVEL1]->collisionData);
	m_enemyList.push_back(ghost);
}

bool ModelHandler::InitObjects()
{
	GameObject * object = new GameObject("Player");
	object->addMesh(MeshBuilder::GenerateSpriteAnimation("Player",2,6,32.f,48.f));
	object->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_level1.tga");    //Current State 
	m_objectList.push_back(object);
	SpriteAnimation *playerAnimation = dynamic_cast<SpriteAnimation*>(m_objectList[0]->getMesh());
	if(playerAnimation)
	{
		playerAnimation->m_anim = new Animation();
		playerAnimation->m_anim->Set(0,2,0,0.5f);
	}

	object = new GameObject("Axes");
	object->addMesh(MeshBuilder::GenerateAxes("Axes", 100000, 100000, 100000));
	m_objectList.push_back(object);

	//DON'T PUSH ANYTHING ELSE

	object = new GameObject("Main Menu", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[WORLD_MAINMENU]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_MAINMENU]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_MAINMENU.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_MAINMENU]->foregroundData,32,32));
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

	object = new GameObject("Sight Tutorial", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_TUTORIAL]->backgroundData,32,48));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_TUTORIAL]->sceneryData,32,48));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_TUTORIAL]->foregroundData,32,48));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	m_objectList.push_back(object);

	object = new GameObject("Sight 02", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_02]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_02]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_02]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	m_objectList.push_back(object);
	
	object = new GameObject("Sight 03", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_03]->backgroundData,32,48));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_03]->sceneryData,32,48));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_SIGHT_03]->foregroundData,32,48));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	m_objectList.push_back(object);

	object = new GameObject("Friends Tutorial", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("World Background",Color(0.f,0.f,0.f),m_worldList[WORLD_FRIENDS_TUTORIAL]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_FRIENDS_TUTORIAL]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("World Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_FRIENDS_TUTORIAL]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	m_objectList.push_back(object);

	object = new GameObject("Friends Level 1", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("Friends Background",Color(0.f,0.f,0.f),m_worldList[WORLD_FRIENDS_LEVEL1]->backgroundData,32,32));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Friends Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_FRIENDS_LEVEL1]->sceneryData,32,32));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Friends Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_FRIENDS_LEVEL1]->foregroundData,32,32));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_BLUE.tga");
	m_objectList.push_back(object);

	object = new GameObject("Night 1 (School) Level 1", TYPE_MAP, Vector3(0, 0, 0));
	object->addMesh(MeshBuilder::GenerateTileMap("Night 1 (School) Level 1 Background",Color(0.f,0.f,0.f),m_worldList[WORLD_SCHOOL_LEVEL1]->backgroundData,32,48));
	object->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Night 1 (School) Level 1 Scenery",Color(0.f,0.f,0.f),m_worldList[WORLD_SCHOOL_LEVEL1]->sceneryData,32,48));
	object->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	object->addMesh(MeshBuilder::GenerateTileMap("Night 1 (School) Level 1 Foreground",Color(0.f,0.f,0.f),m_worldList[WORLD_SCHOOL_LEVEL1]->foregroundData,32,48));
	object->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_RED.tga");
	m_objectList.push_back(object);

	object = new GameObject("Game Text Onryou",TYPE_TEXT);
	object->addMesh(MeshBuilder::GenerateText("Game Text Onryou",16,16));
	object->getMesh()->textureID = LoadTGA("Images//Fonts//onryou.tga");
	m_objectList.push_back(object);

	object = new GameObject("Game Text Basis", TYPE_TEXT);
	object->addMesh(MeshBuilder::GenerateText("Game Text Basis",16,16));
	object->getMesh()->textureID = LoadTGA("Images//Fonts//basis33.tga");
	m_objectList.push_back(object);

	object = new GameObject("Enemy", TYPE_ENEMY, Vector3(Evil->GetPos_x(),Evil->GetPos_y(),0.f));
	object->addMesh(MeshBuilder::GenerateQuad("Enemy",Color(1.f,0.f,0.f),32.f));
	m_objectList.push_back(object);

	object = new GameObject("Enemy Sister", TYPE_ENEMY, Vector3(Friend->GetPos_x(),Friend->GetPos_y(),0.f));
	object->addMesh(MeshBuilder::GenerateSpriteAnimation("Enemy animation",2,6,24.f,48.f));
	object->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_sister.tga");    //Current State 
	m_objectList.push_back(object);
	SpriteAnimation *enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[13]->getMesh());
	if(enemyAnim)
	{
		enemyAnim->m_anim = new Animation();
		enemyAnim->m_anim->Set(0,2,0,0.3f);
	}

	object = new GameObject("EnemyFather", TYPE_ENEMY, Vector3(Father->GetPos_x(),Father->GetPos_y(),0.f));
	object->addMesh(MeshBuilder::GenerateSpriteAnimation("Father animation",2,6,24.f,48.f));
	object->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_madFather.tga");    //Current State 
	m_objectList.push_back(object);
	enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[14]->getMesh());
	if(enemyAnim)
	{
		enemyAnim->m_anim = new Animation();
		enemyAnim->m_anim->Set(0,2,0,0.3f);
	}

	object = new GameObject("Enemy Dasher", TYPE_ENEMY, Vector3(m_enemyList[0]->GetPos_x(),m_enemyList[0]->GetPos_y(),0.f)); //ID = 16
	object->addMesh(MeshBuilder::GenerateSpriteAnimation("Dasher Animation",2,6,32.f,48.f));
	object->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_dasher.tga");    //Current State 
	m_objectList.push_back(object);
	enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[16]->getMesh());
	if(enemyAnim)
	{
		enemyAnim->m_anim = new Animation();
		enemyAnim->m_anim->Set(0,2,0,0.3f);
	}

	object = new GameObject("Enemy Ghost", TYPE_ENEMY, Vector3(m_enemyList[1]->GetPos_x(),m_enemyList[1]->GetPos_y(),0.f)); //ID = 17
	object->addMesh(MeshBuilder::GenerateSpriteAnimation("Ghost Animation",2,6,32.f,48.f));
	object->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_boy.tga");    //Current State 
	m_objectList.push_back(object);
	enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[17]->getMesh());
	if(enemyAnim)
	{
		enemyAnim->m_anim = new Animation();
		enemyAnim->m_anim->Set(0,2,0,0.3f);
	}

	Item * item = new Item("Consumable");
	item->setDescription("Consumable");
	m_itemList.push_back(item);

	item = new Item("Equipment");
	item->setDescription("Equipment");
	m_itemList.push_back(item);

	//ITEM INVENTORY
	this->getPlayer()->getInventory().addItem(m_itemList[0]);                                         //ADD ITEM (Consumable)
	this->getPlayer()->getInventory().addItem(m_itemList[1]);                                         //ADD ITEM (Equipment)

	Gui * newGui = new Gui("Item Border","Images//UI//Item_Border.tga");
	m_guiList.push_back(newGui);

	newGui = new Gui("Fear Border","Images//UI//Fear_Border.tga");
	m_guiList.push_back(newGui);

	newGui = new Gui("Fear","Images//UI//Fear.tga");
	m_guiList.push_back(newGui);

	newGui = new Gui("Wrong End","Images//UI//Sanity.tga");
	m_guiList.push_back(newGui);

	return true;
}

void ModelHandler::Update(const double dt)
{
	camera.Update(dt);

	SpriteAnimation *playerAnimation = dynamic_cast<SpriteAnimation*>(m_objectList[0]->getMesh());
	switch(player->m_animationState)
		{
		case Player::STATE_WALKING_UP:
			playerAnimation->m_anim->Set(6,8,0,0.4f);
			break;
		case Player::STATE_WALKING_DOWN:
			playerAnimation->m_anim->Set(0,2,0,0.4f);
			break;
		case Player::STATE_WALKING_LEFT:
			playerAnimation->m_anim->Set(3,5,0,0.4f);
			break;
		case Player::STATE_WALKING_RIGHT:
			playerAnimation->m_anim->Set(9,11,0,0.4f);
			break;
		case Player::STATE_IDLE_UP:
			if (playerAnimation->m_currentFrame == 7)
			{
				playerAnimation->m_anim->Set(7,7,0,0.4f);
			}
			break;
		case Player::STATE_IDLE_DOWN:
			if (playerAnimation->m_currentFrame == 1)
			{
				playerAnimation->m_anim->Set(1,1,0,0.4f);
			}
			break;
		case Player::STATE_IDLE_LEFT:
			if (playerAnimation->m_currentFrame == 4)
			{
				playerAnimation->m_anim->Set(4,4,0,0.4f);
			}
			break;
		case Player::STATE_IDLE_RIGHT:
			if (playerAnimation->m_currentFrame == 10)
			{
				playerAnimation->m_anim->Set(10,10,0,0.4f);
			}
			break;
		}

	SpriteAnimation *enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[14]->getMesh());
	switch(dynamic_cast<EnemyFriend*>(Friend)->state)
	{
	case EnemyFriend::STATE_WALK_UP:
		enemyAnim->m_anim->Set(6,8,0,0.3f);
		break;
	case EnemyFriend::STATE_WALK_DOWN:
		enemyAnim->m_anim->Set(0,2,0,0.3f);
		break;
	case EnemyFriend::STATE_WALK_LEFT:
		enemyAnim->m_anim->Set(3,5,0,0.3f);
		break;
	case EnemyFriend::STATE_WALK_RIGHT:
		enemyAnim->m_anim->Set(9,11,0,0.3f);
		break;
	}

	if(currentWorld == WORLD_SCHOOL_LEVEL1)
	{
		SpriteAnimation *enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[16]->getMesh());
		switch(dynamic_cast<EnemyDasher*>(m_enemyList[0])->getAnimState())
		{
		case EnemyDasher::STATE_WALKING_UP:
			enemyAnim->m_anim->Set(6,8,0,0.3f);
			break;
		case EnemyDasher::STATE_WALKING_DOWN:
			enemyAnim->m_anim->Set(0,2,0,0.3f);
			break;
		case EnemyDasher::STATE_WALKING_LEFT:
			enemyAnim->m_anim->Set(3,5,0,0.3f);
			break;
		case EnemyDasher::STATE_WALKING_RIGHT:
			enemyAnim->m_anim->Set(9,11,0,0.3f);
			break;
		}

		enemyAnim = dynamic_cast<SpriteAnimation*>(m_objectList[17]->getMesh());
		switch(dynamic_cast<EnemyGhost*>(m_enemyList[1])->getAnimState())
		{
		case EnemyGhost::STATE_WALKING_UP:
			enemyAnim->m_anim->Set(6,8,0,0.3f);
			break;
		case EnemyGhost::STATE_WALKING_DOWN:
			enemyAnim->m_anim->Set(0,2,0,0.3f);
			break;
		case EnemyGhost::STATE_WALKING_LEFT:
			enemyAnim->m_anim->Set(3,5,0,0.3f);
			break;
		case EnemyGhost::STATE_WALKING_RIGHT:
			enemyAnim->m_anim->Set(9,11,0,0.3f);
			break;
		}
	}

	player->update(dt,m_worldList[currentWorld], m_worldList[currentWorld]->getRoom(player->getPosition().x, player->getPosition().y),getInstance());

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
	if (currentWorld == WORLD_FRIENDS_TUTORIAL)
	{
		m_objectList[14]->isAlive = true;
		Friend->Update(this->getInstance(), dt);
		m_objectList[14]->setPosition(Vector3(Friend->GetPos_x(),Friend->GetPos_y(),0));
		Friend->SetData(m_worldList[WORLD_FRIENDS_TUTORIAL]->collisionData);

		m_objectList[15]->isAlive = true;
		Father->Update(this->getInstance(), this->sound->getNoiseLevel(), dt);
		m_objectList[15]->setPosition(Vector3(Father->GetPos_x(),Father->GetPos_y(),0));
		Father->SetData(m_worldList[WORLD_FRIENDS_TUTORIAL]->collisionData);
	}
	else
	{
		m_objectList[14]->isAlive = false;
		m_objectList[15]->isAlive = false;
	}


	if (currentWorld == WORLD_SCHOOL_LEVEL1)
	{
		m_objectList[16]->isAlive = true;
		m_enemyList[0]->Update(this->player,m_worldList[currentWorld],dt);
		m_objectList[16]->setPosition(Vector3(m_enemyList[0]->GetPos_x(),m_enemyList[0]->GetPos_y(),0));
		m_enemyList[0]->SetData(m_worldList[WORLD_SCHOOL_LEVEL1]->collisionData);

		m_objectList[17]->isAlive = true;
		m_enemyList[1]->Update(this->player,m_worldList[currentWorld],dt);
		m_objectList[17]->setPosition(Vector3(m_enemyList[1]->GetPos_x(),m_enemyList[1]->GetPos_y(),0));
		m_enemyList[1]->SetData(m_worldList[WORLD_SCHOOL_LEVEL1]->collisionData);
	}
	else
	{
		m_objectList[16]->isAlive = false;
		m_objectList[17]->isAlive = false;
	}


	Evil->Update(player, m_worldList[currentWorld], dt); 
	m_objectList[13]->setPosition(Vector3(Evil->GetPos_x(),Evil->GetPos_y(),0));
}

Camera ModelHandler::getCamera()
{
	return this->camera;
}

Game ModelHandler::getEnvironment()
{
	return this->theEnvironment;
}

Player* ModelHandler::getPlayer()
{
	return this->player;
}

EnemyFriend* ModelHandler::getFriend()
{
	return this->Friend;
}

EnemyFather* ModelHandler::getFather()
{
	return this->Father;
}