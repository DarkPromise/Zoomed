#include "Room.h"
#include "MyMath.h"

#define NUM_ATTEMPTS	100

Room_Object::Room_Object(ROOM_OBJECT_TYPE objectType, int roomHeight, int roomWidth)
{
	this->type = objectType;

	this->lowerOriginX = 2; this->upperOriginX = roomWidth-2;
	this->lowerOriginY = 7; this->upperOriginY = roomHeight-3;

	switch (objectType)
	{
		case ROOM_OBJECT_TESTPUZZLE_BED:
			{
				this->width = 2;
				this->height = 4;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE:
			{
				this->width = 2;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE:
			{
				this->width = 2;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_WHITE_TABLECLOTH_TABLE:
			{
				this->width = 3;
				this->height = 3;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE:
			{
				this->width = 1;
				this->height = 1;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BRONZE_CANDLESTICK:
			{
				this->width = 1;
				this->height = 1;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BRONZE_BOTTLE:
			{
				this->width = 1;
				this->height = 1;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_OPEN_BOOK:
			{
				this->width = 1;
				this->height = 1;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_CLOSED_EXIT_BOTTOM:
			{
				this->width = 3;
				this->height = 1;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_OPEN_EXIT_BOTTOM:
			{
				this->width = 3;
				this->height = 2;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BIG_WINDOW:
			{
				this->width = 3;
				this->height = 4;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_SMALL_WINDOW:
			{
				this->width = 2;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET:
			{
				this->width = 2;
				this->height = 3;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_PATTERNED_FLOOR:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_MECH_FACTORY_PIPES:
			{
				this->width = 5;
				this->height = 4;
			}
			break;
		case ROOM_OBJECT_MECH_CURVE_PIPES:
			{
				this->width = 3;
				this->height = 2;

				/*this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;*/
			}
			break;
		case ROOM_OBJECT_MECH_WALL_PIPES:
			{
				this->width = 4;
				this->height = 3;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_MECH_HOSE_PIPE:
			{
				this->width = 3;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_MECH_ROCK_WALL:
			{
				this->width = 4;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_MECH_ROCK_RIGHT:
			{
				this->width = 1;
				this->height = 3;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_MECH_ROCK_LEFT:
			{
				this->width = 1;
				this->height = 3;

				this->lowerOriginX = -1; this->upperOriginX = -1;
				this->lowerOriginY = -1; this->upperOriginY = -1;
			}
			break;
		case ROOM_OBJECT_MECH_ENGINE:
			{
				this->width = 2;
				this->height = 2;

			}
			break;
	}
}

Room_Object::~Room_Object(void)
{
}


Room::Room(ROOM_TYPE roomType,
	const int theScreen_Height, 
		const int theScreen_Width, 
		const int theNumOfTiles_Height, 
		const int theNumOfTiles_Width, 
		const int theMap_Height, 
		const int theMap_Width, 
		const int theTileSize, 
		const TILESET_ID tileset,
		const int worldPositionX,
		const int worldPositionY,
		const int roomID) : CMap(theScreen_Height, theScreen_Width, theNumOfTiles_Height, theNumOfTiles_Width, theMap_Height, theMap_Width, theTileSize, tileset)
		, attemptCounter(0)
{
	numExit.clear();
	roomObjectList.clear();

	this->roomType = roomType;
	this->roomID = roomID;

	this->worldPositionX = worldPositionX;
	this->worldPositionY = worldPositionY;

	switch (roomType)
	{
	case ROOM_TESTPUZZLE:
		{
			Room_Object* tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_BED, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE, sceneryData.size(), sceneryData[0].size());
			addOBJtoGenerate(tempObject);
		}
		break;
	case ROOM_MECH:
		{
			

			Room_Object* tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_WALL_PIPES, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_ROCK_RIGHT, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_ROCK_LEFT, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);


			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_HOSE_PIPE, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_ROCK_WALL, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_FACTORY_PIPES, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_CURVE_PIPES, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);

			tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_ENGINE, GetNumOfTiles_Height(), GetNumOfTiles_Width());
			addOBJtoGenerate(tempObject);
		}
		break;
	}
}


Room::~Room(void)
{
	numExit.clear();
	roomObjectList.clear();
}

void Room::reset_mapData()
{
	for (unsigned i = 1; i < this->sceneryData.size()-1; i++) // Reset data values
	{
		std::fill(sceneryData[i].begin(), sceneryData[i].end(), -1);
		std::fill(collisionData[i].begin(), collisionData[i].end(), -1);
		std::fill(foregroundData[i].begin(), foregroundData[i].end(), -1);
	}
}

bool Room::attemptToAdd(ROOM_TYPE roomType, Room_Object* object)
{
	while (attemptCounter < NUM_ATTEMPTS)
	{
		if ( addObject(roomType, object, Math::RandIntMinMax(object->lowerOriginX, object->upperOriginX), Math::RandIntMinMax(object->lowerOriginY, object->upperOriginY)) )
			return true;

		attemptCounter++;
	}

	return false;
}

void Room::addOBJtoGenerate(Room_Object* object)
{
	this->roomObjectList.push_back(object);
}

void Room::generateRoom()
{
	// NOTE!! __data[1][0] IS THE TOP LEFT AFTER RENDERING	
	bool generatedRoom = false;

	while (!generatedRoom)
	{
		this->exitCounter = 0; // counters number of exits placed
		attemptCounter = 0; // counts number of times object was tried to be placed
		generatedRoom = true; // reset room flag
		if (roomType != ROOM_TUTORIAL_FRIENDS && roomType != ROOM_MAINMENU && roomType != ROOM_MAINMENU)
		{
			reset_mapData(); // reset map data
		}
		else
		{
			for (unsigned i = 1; i < this->sceneryData.size()-1; i++) // Reset data values
			{
				std::fill(collisionData[i].begin(), collisionData[i].end(), -1);
			}
		}

		//generate objects
		for (unsigned i = 0; i < roomObjectList.size(); i++)
		{
			if ( attemptToAdd(roomType, roomObjectList[i]) ) 
			{
				attemptCounter = 0;
			}
			else 
			{
				generatedRoom = false;
			}
		}
	}

	// test collision code
	for (unsigned i = 0; i < sceneryData.size(); i++)
	{
		for (unsigned j = 0; j < sceneryData[i].size(); j++)
		{
			if (this->sceneryData[i][j] != -1)
			{
				this->collisionData[i][j] = 100;
			}
		}
	}

	int floorTileID = -1;
	if (this->roomType == ROOM_TESTPUZZLE)
	{
		floorTileID = ROOMS_FLOORTILE;

	}
	else if (this->roomType == ROOM_TUTORIAL_FRIENDS)
	{
		floorTileID = BLUE_FLOORTILE;
	}
	else if (this->roomType == ROOM_MAINMENU)
	{
		floorTileID = MAINMENU_FLOORTILE;
	}
	else if (this->roomType == ROOM_MECH)
	{
		floorTileID = MECH_FLOORTILE;
	}

	for (unsigned i = 0; i < backgroundData.size(); i++)
	{
		for (unsigned j = 0; j < backgroundData[i].size(); j++)
		{
			if ((this->backgroundData[i][j] != floorTileID) && (this->backgroundData[i][j] != -1))
			{
				this->collisionData[i][j] = 100;
			}

			if (this->backgroundData[i][j] > TILE_CORRIDOR_FLOOR && this->backgroundData[i][j] < 1024)
			{
				this->collisionData[i][j] = 100;
			}
		}
	}

	if (this->theTileset == TILESET_BLUE)
	{
		int ignoreTiles[BLUE_IGNORETOTAL] = {
		BLUE_TILEBLOOD,
		BLUE_TILEBODY1,
		BLUE_TILEDEBRIS1,

		BLUE_TILEYELLOWBUTTON,
		BLUE_TILEREDBUTTON,
		BLUE_TILEPURPLEBUTTON,
		BLUE_TILEGRAYBUTTON,
		
		BLUE_TILEYELLOWBLOCK_OFF,
		BLUE_TILEREDBLOCK_OFF,
		BLUE_TILEPURPLEBLOCK_OFF,
		BLUE_TILEGRAYBLOCK_OFF};

		int collisionTiles[BLUE_IGNORETOTAL] = {
		COLLISION_BLUE_TILEBLOOD,
		COLLISION_BLUE_TILEBODY1,
		COLLISION_BLUE_TILEDEBRIS1,

		COLLISION_BLUE_TILEYELLOWBUTTON,
		COLLISION_BLUE_TILEREDBUTTON,
		COLLISION_BLUE_TILEPURPLEBUTTON,
		COLLISION_BLUE_TILEGRAYBUTTON,
		
		COLLISION_BLUE_TILEYELLOWBLOCK_OFF,
		COLLISION_BLUE_TILEREDBLOCK_OFF,
		COLLISION_BLUE_TILEPURPLEBLOCK_OFF,
		COLLISION_BLUE_TILEGRAYBLOCK_OFF};

		for (unsigned i = 0; i < backgroundData.size(); i++)
		{
			for (unsigned j = 0; j < backgroundData[i].size(); j++)
			{
				for (unsigned k = 0; k < BLUE_IGNORETOTAL; k++)
				{
					if (sceneryData[i][j] == ignoreTiles[k])
					{
						this->collisionData[i][j] = collisionTiles[k];
					}
				}
			}
		}
	}
	else if (this->theTileset == TILESET_MAIN_MENU)
	{
		int ignoreTiles[MAINMENU_IGNORETOTAL] = {
		MAINMENU_TILEBLOOD,
		MAINMENU_TILEDEBRIS1,
		MAINMENU_TILEDEBRIS2,
		MAINMENU_TILEDEBRIS3,
		MAINMENU_TILEDEBRIS4,
		MAINMENU_TILEDEBRIS5,
		MAINMENU_TILEDEBRIS6,
		MAINMENU_TILEDEBRIS7,};

		int collisionTiles[MAINMENU_IGNORETOTAL] = {
		COLLISION_MAINMENU_TILEBLOOD,
		COLLISION_MAINMENU_TILEDEBRIS1,
		COLLISION_MAINMENU_TILEDEBRIS2,
		COLLISION_MAINMENU_TILEDEBRIS3,
		COLLISION_MAINMENU_TILEDEBRIS4,
		COLLISION_MAINMENU_TILEDEBRIS5,
		COLLISION_MAINMENU_TILEDEBRIS6,
		COLLISION_MAINMENU_TILEDEBRIS7,};

		for (unsigned i = 0; i < backgroundData.size(); i++)
		{
			for (unsigned j = 0; j < backgroundData[i].size(); j++)
			{
				for (unsigned k = 0; k < MAINMENU_IGNORETOTAL; k++)
				{
					if (sceneryData[i][j] == ignoreTiles[k])
					{
						this->collisionData[i][j] = collisionTiles[k];
					}
				}
			}
		}
	}
}

bool Room::addObject(ROOM_TYPE type, Room_Object* object, int originX, int originY)
{
	Room_Object::ROOM_OBJECT_TYPE room_object = object->type;
	
	// If object is randomised
	if (originX != -1)
	{
		//Make sure object will be rendered in the room
		if (originY < 5 || (originY + object->height) > (int)(sceneryData.size()-2) || originX < 2 || (originX + object->width) > (int)(sceneryData[0].size()-2))
		{
			return false;
		}
	
		//Make sure object doesn't collide with other objects and doesn't lie directly beside
		{
			for (int i = -1; i <= object->height+1; i++)
			{
				for (int j = -1; j <= object->width+1; j++)
				{
					if (sceneryData[originY+i][originX+j] != -1 || foregroundData[originY+i][originX+j] != -1 || collisionData[originY+i][originX+j] != -1)
					{
						return false;
					}
				}
			}
		}
	}

	if (type == ROOM_TESTPUZZLE)
	{
		switch (room_object)
		{
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BED:
			{
				sceneryData[originY][originX] = 360; sceneryData[originY][originX+1] = 361;
				sceneryData[originY+1][originX] = 392; sceneryData[originY+1][originX+1] = 393;
				sceneryData[originY+2][originX] = 424; sceneryData[originY+2][originX+1] = 425;
				sceneryData[originY+3][originX] = 456; sceneryData[originY+3][originX+1] = 457;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE:
			{
				sceneryData[originY][originX] = 202; sceneryData[originY][originX+1] = 203;
				sceneryData[originY+1][originX] = 234; sceneryData[originY+1][originX+1] = 235;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE:
			{
				sceneryData[originY][originX] = 204; sceneryData[originY][originX+1] = 205;
				sceneryData[originY+1][originX] = 236; sceneryData[originY+1][originX+1] = 237;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT:
			{
				foregroundData[originY-1][originX] = 140;
				sceneryData[originY][originX] = 172;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT:
			{
				foregroundData[originY-1][originX] = 141;
				sceneryData[originY][originX] = 173;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_WHITE_TABLECLOTH_TABLE:
			{
				sceneryData[originY][originX] = 263; sceneryData[originY][originX+1] = 264; sceneryData[originY][originX+2] = 265;
				sceneryData[originY+1][originX] = 295; sceneryData[originY+1][originX+1] = 296; sceneryData[originY+1][originX+2] = 297;
				sceneryData[originY+2][originX] = 327; sceneryData[originY+2][originX+1] = 328; sceneryData[originY+2][originX+2] = 329;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE:
			{
				for (unsigned i = 0; i < sceneryData.size(); i++)
				{
					for (unsigned j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i-1][j] = 136;
							foregroundData[i][j] = 168;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_CANDLESTICK:
			{
				for (unsigned i = 0; i < sceneryData.size(); i++)
				{
					for (unsigned j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i-1][j] = 137;
							foregroundData[i][j] = 169;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_BOTTLE:
			{
				for (unsigned i = 0; i < sceneryData.size(); i++)
				{
					for (unsigned j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i][j] = 170;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_OPEN_BOOK:
			{
				for (unsigned i = 0; i < sceneryData.size(); i++)
				{
					for (unsigned j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i][j] = 171;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_CLOSED_EXIT_BOTTOM:
			{
				originX = Math::RandIntMinMax(3, sceneryData[0].size()-5);
				while (!((originX != -1) && (sceneryData[sceneryData.size()-3][originX] == -1)))
				{
					originX = Math::RandIntMinMax(3, sceneryData[0].size()-5);
				}

				sceneryData[sceneryData.size()-2][originX] = 266; sceneryData[sceneryData.size()-2][originX+1] = 267; sceneryData[sceneryData.size()-2][originX+2] = 268;

				numExit[exitCounter]->exitPositionX = originX+1;
				numExit[exitCounter]->exitPositionY = sceneryData.size()-2;

				exitCounter++;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_OPEN_EXIT_BOTTOM:
			{
				originX = Math::RandIntMinMax(3, sceneryData[0].size()-5);
				while (!((originX != -1) && (sceneryData[sceneryData.size()-3][originX] == -1)))
				{
					originX = Math::RandIntMinMax(3, sceneryData[0].size()-5);
				}

				sceneryData[sceneryData.size()-2][originX] = 266; sceneryData[sceneryData.size()-2][originX+2] = 268;
				backgroundData[sceneryData.size()-2][originX+1] = 162; sceneryData[sceneryData.size()-2][originX+1] = -1;

				numExit[exitCounter]->exitPositionX = originX+1;
				numExit[exitCounter]->exitPositionY = sceneryData.size()-2;

				exitCounter++;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BIG_WINDOW:
			{
				sceneryData[originY][originX] = 39; sceneryData[originY][originX+1] = 40; sceneryData[originY][originX+2] = 41;
				sceneryData[originY+1][originX] = 71; sceneryData[originY+1][originX+1] = 72; sceneryData[originY+1][originX+2] = 73;
				sceneryData[originY+2][originX] = 103; sceneryData[originY+2][originX+1] = 104; sceneryData[originY+2][originX+2] = 105;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_WINDOW:
			{
				sceneryData[originY][originX] = 42; sceneryData[originY][originX+1] = 43;
				sceneryData[originY+1][originX] = 74; sceneryData[originY+1][originX+1] = 75;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET:
			{
				originX = Math::RandIntMinMax(3, sceneryData[0].size()-4);
				while (!((originX != -1) && (sceneryData[sceneryData.size()-3][originX] == -1)))
				{
					for (int i = originX-1; i < originX+object->width; i++)
					{
						for (int j = 3; j <= 6; j++)
						{
							if (sceneryData[j][i] != -1)
							{
								originX = Math::RandIntMinMax(3, sceneryData[0].size()-4);
								break;
							}
						}
					}
				}

				foregroundData[3][originX] = 44; foregroundData[3][originX+1] = 45;
				sceneryData[4][originX] = 76; sceneryData[4][originX+1] = 77;
				sceneryData[5][originX] = 108; sceneryData[5][originX+1] = 109;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_PATTERNED_FLOOR:
			{
				sceneryData[originY][originX] = 288;
			}
			break;
		};
	}
	else if (type == ROOM_MECH)
	{
		switch (room_object)
		{
		case Room_Object::ROOM_OBJECT_MECH_WALL_PIPES:
			{
				originX = Math::RandIntMinMax(3, sceneryData[0].size()-7);
				while (!((originX != -1) && (sceneryData[sceneryData.size()-3][originX] == -1)))
				{
					for (int i = originX-1; i < originX+object->width; i++)
					{
						for (int j = 2; j <= 5; j++)
						{
							if (sceneryData[j][i] != -1)
							{
								originX = Math::RandIntMinMax(3, sceneryData[0].size()-7);
								break;
							}
						}
					}
				}

				sceneryData[2][originX] = 556; sceneryData[2][originX+1] = 557; sceneryData[2][originX+2] = 558; sceneryData[2][originX+3] = 559;
				sceneryData[3][originX] = 588; sceneryData[3][originX+1] = 589; sceneryData[3][originX+2] = 590; sceneryData[3][originX+3] = 591;
				sceneryData[4][originX] = 620; sceneryData[4][originX+1] = 621; sceneryData[4][originX+2] = 622; sceneryData[4][originX+3] = 623;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_ENGINE:
			{
				sceneryData[originY][originX] = 582; sceneryData[originY][originX+1] = 583;
				sceneryData[originY+1][originX] = 614; sceneryData[originY+1][originX+1] = 615;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_HOSE_PIPE:
			{
				sceneryData[originY][originX] = 477; sceneryData[originY][originX+1] = 478; sceneryData[originY][originX+2] = 479;
				sceneryData[originY+1][originX] = 509; sceneryData[originY+1][originX+1] = 510; sceneryData[originY+1][originX+2] = 511;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_FACTORY_PIPES:
			{
				sceneryData[originY][originX] = 516; sceneryData[originY][originX+1] = 517; 
				sceneryData[originY+1][originX] = 548; sceneryData[originY+1][originX+1] = 549; sceneryData[originY+1][originX+2] = 550;
				sceneryData[originY+2][originX] = 580; sceneryData[originY+2][originX+1] = 581; sceneryData[originY+2][originX+2] = 582; sceneryData[originY+2][originX+3] = 583; sceneryData[originY+2][originX+4] = 584;
				sceneryData[originY+3][originX] = 612; sceneryData[originY+3][originX+1] = 613; sceneryData[originY+3][originX+2] = 614; sceneryData[originY+3][originX+3] = 615; sceneryData[originY+3][originX+4] = 616;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_ROCK_WALL:
			{
				sceneryData[originY][originX] = 34; sceneryData[originY][originX+1] = 35; sceneryData[originY][originX+2] = 36; sceneryData[originY][originX+3] = 37; 
				sceneryData[originY+1][originX] = 66; sceneryData[originY+1][originX+1] = 67; sceneryData[originY+1][originX+2] = 68; sceneryData[originY+1][originX+3] = 69;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_ROCK_RIGHT:
			{
				originX = Math::RandIntMinMax(5, sceneryData[0].size()-5);
				originY = Math::RandIntMinMax(5, sceneryData.size()-5);


				for (int i = originX; i < originX+object->width; i++)
				{
					for (int j = originY; j <= originY+object->height; j++)
					{
						if (sceneryData[j][i] != -1)
						{
							originX = Math::RandIntMinMax(5, sceneryData[0].size()-5);
							originY = Math::RandIntMinMax(5, sceneryData.size()-5);
							break;
						}
					}
				}


				sceneryData[originY][originX] = 102;
				sceneryData[originY+1][originX] = 134;
				sceneryData[originY+2][originX] = 166;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_ROCK_LEFT:
			{

				originX = Math::RandIntMinMax(5, sceneryData[0].size()-5);
				originY = Math::RandIntMinMax(5, sceneryData.size()-5);

				for (int i = originX; i < originX+object->width; i++)
				{
					for (int j = originY; j <= originY+object->height; j++)
					{
						while (!((originY != -1) && (sceneryData[originY][originX] == -1)))
						{
							originX = Math::RandIntMinMax(5, sceneryData[0].size()-5);
							originY = Math::RandIntMinMax(5, sceneryData.size()-5);
						}
					}
				}


				
				sceneryData[originY][originX] = 97;
				sceneryData[originY+1][originX] = 129;
				sceneryData[originY+2][originX] = 161;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_CURVE_PIPES:
			{
				/*originY = 2;
				originX = Math::RandIntMinMax(4, sceneryData[0].size()-6);
				while (!((originX != -1) && (sceneryData[sceneryData.size()-4][originX] == -1)))
				{
					for (int i = originX-1; i < originX+object->width; i++)
					{
						for (int j = 2; j <= 7; j++)
						{
							if (sceneryData[j][i] != -1)
							{
								originX = Math::RandIntMinMax(4, sceneryData[0].size()-6);
								break;
							}
						}
					}
				}*/

				foregroundData[originY][originX+1] = 522; foregroundData[originY][originX+2] = 523; 
				foregroundData[originY+1][originX+1] = 554; foregroundData[originY+1][originX+2] = 555;
				foregroundData[originY+2][originX+1] = 586; foregroundData[originY+2][originX+2] = 587;
				sceneryData[originY+3][originX] = 617; sceneryData[originY+3][originX+1] = 618; sceneryData[originY+3][originX+2] = 619;
				sceneryData[originY+4][originX] = 649; sceneryData[originY+4][originX+1] = 650; sceneryData[originY+4][originX+2] = 651;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_LEFT_DOOR:
			{
				originX = 0;
				originY = Math::RandIntMinMax(4, sceneryData.size()-1);

				while (!((originY != -1) && (sceneryData[originY][originX] == -1)))
				{
					originY = Math::RandIntMinMax(4, sceneryData.size()-1);
				}



				foregroundData[originY][originX] = 938; sceneryData[originY][originX+1] = 939;
				foregroundData[originY+1][originX] = 970; foregroundData[originY+1][originX+1] = 971;
				sceneryData[originY+2][originX] = 1002; sceneryData[originY+2][originX+1] = 1003;

				sceneryData[originY][originX] = 938;

				backgroundData[originY][originX] = MECH_FLOORTILE; backgroundData[originY][originX+1] = MECH_FLOORTILE;
				backgroundData[originY+1][originX] = MECH_FLOORTILE; backgroundData[originY+1][originX+1] = MECH_FLOORTILE;
				backgroundData[originY+2][originX] = MECH_FLOORTILE; backgroundData[originY+2][originX+1] = MECH_FLOORTILE;


				numExit[exitCounter]->exitPositionX = originX;
				numExit[exitCounter]->exitPositionY = originY+1;

				exitCounter++;
			}
			break;
		case Room_Object::ROOM_OBJECT_MECH_RIGHT_DOOR:
			{
				originX = sceneryData[0].size() - 2;
				originY = Math::RandIntMinMax(4, sceneryData.size()-1);

				while (!((originY != -1) && (sceneryData[originY][originX] == -1)))
				{
					originY = Math::RandIntMinMax(4, sceneryData.size()-1);
				}

				sceneryData[originY][originX] = 842; foregroundData[originY][originX+1] = 843;
				backgroundData[originY+1][originX] = 874; foregroundData[originY+1][originX+1] = 875;
				sceneryData[originY+2][originX] = 906; sceneryData[originY+2][originX+1] = 907;

				sceneryData[originY][originX+1] = 843;

				backgroundData[originY][originX] = MECH_FLOORTILE; backgroundData[originY][originX+1] = MECH_FLOORTILE;
				backgroundData[originY+1][originX] = MECH_FLOORTILE; backgroundData[originY+1][originX+1] = MECH_FLOORTILE;
				backgroundData[originY+2][originX] = MECH_FLOORTILE; backgroundData[originY+2][originX+1] = MECH_FLOORTILE;

				numExit[exitCounter]->exitPositionX = originX+2;
				numExit[exitCounter]->exitPositionY = originY+1;

				exitCounter++;
			}
			break;
		};
	}


	return true;
}

void Room::addExit(EXIT_DIRECTION exit)
{
	Room_Exit* newExit = new Room_Exit(exit, this->getRoomType(), this->roomID);
	this->numExit.push_back(newExit);
	
	switch (roomType)
	{
	case ROOM_TESTPUZZLE:
		{
			if (exit == EXIT_DOWN)
			{
				Room_Object* tempObject = new Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_OPEN_EXIT_BOTTOM, sceneryData.size(), sceneryData[0].size());
				addOBJtoGenerate(tempObject);
			}
			/*else if (exit == EXIT_UP)
			{
			}
			else if (exit == EXIT_LEFT)
			{
			}
			else if (exit == EXIT_RIGHT)
			{
			}*/
		}
		break;
	case ROOM_MECH:
		{
			if(exit == EXIT_RIGHT)
			{
				Room_Object* tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_RIGHT_DOOR, sceneryData.size(), sceneryData[0].size());
				addOBJtoGenerate(tempObject);
			}
			else if(exit == EXIT_LEFT)
			{
				Room_Object* tempObject = new Room_Object(Room_Object::ROOM_OBJECT_MECH_LEFT_DOOR, sceneryData.size(), sceneryData[0].size());
				addOBJtoGenerate(tempObject);
			}
		}
		break;
	}
}

ROOM_TYPE Room::getRoomType()
{
	return this->roomType;
}

unsigned Room::getExitSize()
{
	return numExit.size();
}

Room_Exit* Room::getExit(int index)
{
	return numExit[index];
}

int Room::getWorldPositionX()
{
	return this->worldPositionX;
}

int Room::getWorldPositionY()
{
	return this->worldPositionY;
}