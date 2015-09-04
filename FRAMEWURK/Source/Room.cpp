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
	this->exitCounter = 0;
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
		if (roomType != ROOM_MAINMENU && roomType != ROOM_FRIENDS_TUTORIAL && (roomType < ROOM_FRIENDS_CLASSROOM_SYMMETRY || roomType > ROOM_FRIENDS_ROOM_THREE) && roomType != ROOM_TUTORIAL_SIGHT && roomType != ROOM_SCHOOL_MAIN && roomType != ROOM_MECH)
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

		/*for (unsigned i = 0; i < roomObjectList.size(); i++)
		{
			if ( attemptToAdd(roomType, roomObjectList[i]) ) 
			{
				attemptCounter = 0;
			}
			else 
			{
				generatedRoom = false;
			}
		}*/           //FOR COMPILING IN RELEASE. FIX PLEASE. CAUSE OF ERROR : ROOM TYPE 3 : AHMAD'S WORLD/ROOM

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
	else if (this->roomType >= ROOM_FRIENDS_TUTORIAL && this->roomType <= ROOM_FRIENDS_ROOM_THREE)
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
	else if (this->roomType == ROOM_TUTORIAL_SIGHT)
	{
		floorTileID = RED_FLOORTILE;
	}
	else if (this->roomType == ROOM_TWO_01_SIGHT)
	{
		for(int floorTile = SIGHT_TWO_FLOORTILE_FIRST; floorTile < SIGHT_TWO_FLOORTILE_LAST; ++floorTile)
		{
			floorTileID = floorTile;
		}
	}/*
	 else if(this->roomType == ROOM_TWO_02_SIGHT)
	 {

	 }*/

	for (unsigned i = 0; i < backgroundData.size(); i++)
	{
		for (unsigned j = 0; j < backgroundData[i].size(); j++)
		{
			if ((this->backgroundData[i][j] != floorTileID) && (this->backgroundData[i][j] != -1))
			{
				this->collisionData[i][j] = 100;
			}

			if (this->roomType == ROOM_TUTORIAL_SIGHT)
			{
				if (this->sceneryData[i][j] == RED_TABLE_TILE1 || this->sceneryData[i][j] == RED_TABLE_TILE2 || this->sceneryData[i][j] == RED_TABLE_TILE3 || this->sceneryData[i][j] == RED_TABLE_TILE4 || this->sceneryData[i][j] == RED_CHAIR_TILE)
				{
					this->collisionData[i][j] = 2;
				}
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
			BLUE_TILEGRAYBLOCK_OFF,

			BLUE_FINISHTILE,

			BLUE_LOCKERHIDE,
			BLUE_LOCKERHIDE2,

			BLUE_TILEDEBRIS2,
			BLUE_TILEDEBRIS3,
			BLUE_TILEDEBRIS4,
			BLUE_TILEDEBRIS5,
			BLUE_TILEDEBRIS6,
			BLUE_TILEDEBRIS7,

			BLUE_DOORTILE1,
			BLUE_DOORTILE2,
			BLUE_DOORTILE3,
			BLUE_DOORTILE4,
			BLUE_DOORTILE5,
			BLUE_DOORTILE6,
			BLUE_DOORTILE7,
			BLUE_DOORTILE8,

			BLUE_TILEDEBRIS8,
			BLUE_TILEDEBRIS9};

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
				COLLISION_BLUE_TILEGRAYBLOCK_OFF,

				COLLISION_BLUE_FINISHTILE,

				COLLISION_BLUE_LOCKERHIDE,
				COLLISION_BLUE_LOCKERHIDE2,

				COLLISION_BLUE_TILEDEBRIS2,
				COLLISION_BLUE_TILEDEBRIS3,
				COLLISION_BLUE_TILEDEBRIS4,
				COLLISION_BLUE_TILEDEBRIS5,
				COLLISION_BLUE_TILEDEBRIS6,
				COLLISION_BLUE_TILEDEBRIS7,

				COLLISION_BLUE_DOORTILE1,
				COLLISION_BLUE_DOORTILE2,
				COLLISION_BLUE_DOORTILE3,
				COLLISION_BLUE_DOORTILE4,
				COLLISION_BLUE_DOORTILE5,
				COLLISION_BLUE_DOORTILE6,
				COLLISION_BLUE_DOORTILE7,
				COLLISION_BLUE_DOORTILE8,

				COLLISION_BLUE_TILEDEBRIS8,
				COLLISION_BLUE_TILEDEBRIS9};

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
	else if(this->theTileset == TILESET_POOL)
	{
		int ignoreTiles[MAINMENU_IGNORETOTAL] = {
			MECH_HIDE1,
			MECH_HIDE2,};

			int collisionTiles[MECH_IGNORETOTAL] = {
				COLLISION_MECH_HIDE1,
				COLLISION_MECH_HIDE2,};

				for (unsigned i = 0; i < backgroundData.size(); i++)
				{
					for (unsigned j = 0; j < backgroundData[i].size(); j++)
					{
						for (unsigned k = 0; k < MECH_IGNORETOTAL; k++)
						{
							if (sceneryData[i][j] == ignoreTiles[k])
							{
								this->collisionData[i][j] = collisionTiles[k];
							}
						}
					}
				}
	}
	else if(this->theTileset == TILESET_RED)
	{
		int ignoreFloorTiles[SCHOOL_FLOORTOTAL] = {
			SCHOOL_FLOORTILE_1,
			SCHOOL_FLOORTILE_2,
			SCHOOL_FLOORTILE_3,
			SCHOOL_FLOORTILE_4,
			SCHOOL_FLOORTILE_5, 
			SCHOOL_FLOORTILE_6,
			SCHOOL_FLOORTILE_7,
			SCHOOL_FLOORTILE_8,
			SCHOOL_FLOORTILE_9,
			SCHOOL_FLOORTILE_10, 
			SCHOOL_FLOORTILE_11,
			SCHOOL_FLOORTILE_12,
			SCHOOL_FLOORTILE_13,
			SCHOOL_FLOORTILE_14,
			SCHOOL_FLOORTILE_15,
			SCHOOL_FLOORTILE_16,
			SCHOOL_FLOORTILE_17,
			SCHOOL_FLOORTILE_18,
		};

		int ignoreTiles[SCHOOL_DEBRISTOTAL] = {
			SCHOOL_FLOORTILE_DEBRIS_1,
			SCHOOL_FLOORTILE_DEBRIS_2,
			SCHOOL_FLOORTILE_DEBRIS_3,
			SCHOOL_FLOORTILE_DEBRIS_4,
			SCHOOL_FLOORTILE_DEBRIS_5,
			SCHOOL_FLOORTILE_DEBRIS_6,
			SCHOOL_FLOORTILE_DEBRIS_7,
			SCHOOL_FLOORTILE_DEBRIS_8,
			SCHOOL_FLOORTILE_DEBRIS_9,
			SCHOOL_FLOORTILE_DEBRIS_10,
			SCHOOL_FLOORTILE_DEBRIS_11,
			SCHOOL_FLOORTILE_DEBRIS_12,
			SCHOOL_FLOORTILE_DEBRIS_13,
			SCHOOL_FLOORTILE_DEBRIS_14,
			SCHOOL_FLOORTILE_DEBRIS_15,
			SCHOOL_FLOORTILE_DEBRIS_16,
			SCHOOL_FLOORTILE_DEBRIS_17,
			SCHOOL_FLOORTILE_DEBRIS_18,
			SCHOOL_FLOORTILE_DEBRIS_19,
			SCHOOL_FLOORTILE_DEBRIS_20,
			SCHOOL_FLOORTILE_DEBRIS_21,
			SCHOOL_FLOORTILE_DEBRIS_22,
			SCHOOL_FLOORTILE_DEBRIS_23,
			SCHOOL_FLOORTILE_DEBRIS_24,
			SCHOOL_FLOORTILE_DEBRIS_25,
			SCHOOL_FLOORTILE_DEBRIS_26,
			SCHOOL_FLOORTILE_DEBRIS_27,
			SCHOOL_FLOORTILE_DEBRIS_28,
			SCHOOL_FLOORTILE_DEBRIS_29,
			SCHOOL_FLOORTILE_DEBRIS_30,
			SCHOOL_FLOORTILE_DEBRIS_31,
			SCHOOL_FLOORTILE_DEBRIS_32,
			SCHOOL_FLOORTILE_DEBRIS_33,
			SCHOOL_FLOORTILE_DEBRIS_34,
			SCHOOL_FLOORTILE_DEBRIS_35,
			SCHOOL_FLOORTILE_DEBRIS_36,
			SCHOOL_FLOORTILE_DEBRIS_37,
			SCHOOL_FLOORTILE_DEBRIS_38,
			SCHOOL_FLOORTILE_DEBRIS_39,
			SCHOOL_FLOORTILE_DEBRIS_40,
			SCHOOL_FLOORTILE_DEBRIS_41,
			SCHOOL_FLOORTILE_DEBRIS_42,
			SCHOOL_FLOORTILE_DEBRIS_43,
			SCHOOL_FLOORTILE_DEBRIS_44,
			SCHOOL_FLOORTILE_DEBRIS_45,
			SCHOOL_FLOORTILE_DEBRIS_46,
			SCHOOL_FLOORTILE_DEBRIS_47,
			SCHOOL_FLOORTILE_DEBRIS_48,
			SCHOOL_FLOORTILE_DEBRIS_49,
			SCHOOL_FLOORTILE_DEBRIS_50,
			SCHOOL_FLOORTILE_DEBRIS_51,
			SCHOOL_FLOORTILE_DEBRIS_52,
			SCHOOL_FLOORTILE_DEBRIS_53,
			SCHOOL_FLOORTILE_DEBRIS_54,
			SCHOOL_FLOORTILE_DEBRIS_55,
			SCHOOL_FLOORTILE_DEBRIS_56,
			SCHOOL_FLOORTILE_DEBRIS_57,
			SCHOOL_FLOORTILE_DEBRIS_58,
			SCHOOL_FLOORTILE_DEBRIS_59,
			SCHOOL_FLOORTILE_DEBRIS_60,
			SCHOOL_FLOORTILE_DEBRIS_61,
			SCHOOL_FLOORTILE_DEBRIS_62,
			SCHOOL_FLOORTILE_DEBRIS_63,
			SCHOOL_FLOORTILE_DEBRIS_64,
			SCHOOL_FLOORTILE_DEBRIS_65,
			SCHOOL_FLOORTILE_DEBRIS_66,
			SCHOOL_FLOORTILE_DEBRIS_67,
			SCHOOL_FLOORTILE_DEBRIS_68,
			SCHOOL_FLOORTILE_DEBRIS_69,
			SCHOOL_FLOORTILE_DEBRIS_70,
			SCHOOL_FLOORTILE_DEBRIS_71,
			SCHOOL_FLOORTILE_DEBRIS_72,
			SCHOOL_FLOORTILE_DEBRIS_73,
			SCHOOL_FLOORTILE_DEBRIS_74,
			SCHOOL_FLOORTILE_DEBRIS_75,
			SCHOOL_FLOORTILE_DEBRIS_76,
			SCHOOL_FLOORTILE_DEBRIS_77,
			SCHOOL_FLOORTILE_DEBRIS_78,
			SCHOOL_FLOORTILE_DEBRIS_79,
			SCHOOL_FLOORTILE_DEBRIS_80,
			SCHOOL_FLOORTILE_DEBRIS_81,
			SCHOOL_FLOORTILE_DEBRIS_82,
			SCHOOL_FLOORTILE_DEBRIS_83,
			SCHOOL_FLOORTILE_DEBRIS_84,
			SCHOOL_FLOORTILE_DEBRIS_85,
			SCHOOL_FLOORTILE_DEBRIS_86,
			SCHOOL_FLOORTILE_DEBRIS_87,
			SCHOOL_FLOORTILE_DEBRIS_88,
			SCHOOL_LOCKER_HIDE1,
			SCHOOL_LOCKER_HIDE2,
			SCHOOL_DOORFRAME_RIGHT,
			SCHOOL_DOORFRAME_LEFT,
		};

		int collisionTiles[SCHOOL_DEBRISTOTAL] = {
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_1,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_2,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_3,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_4,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_5,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_6,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_7,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_8,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_9,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_10,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_11,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_12,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_13,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_14,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_15,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_16,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_17,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_18,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_19,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_20,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_21,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_22,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_23,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_24,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_25,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_26,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_27,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_28,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_29,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_30,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_31,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_32,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_33,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_34,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_35,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_36,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_37,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_38,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_39,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_40,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_41,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_42,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_43,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_44,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_45,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_46,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_47,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_48,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_49,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_50,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_51,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_52,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_53,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_54,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_55,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_56,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_57,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_58,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_59,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_60,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_61,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_62,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_63,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_64,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_65,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_66,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_67,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_68,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_69,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_70,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_71,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_72,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_73,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_74,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_75,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_76,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_77,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_78,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_79,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_80,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_81,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_82,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_83,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_84,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_85,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_86,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_87,
			COLLISION_SCHOOL_FLOORTILE_DEBRIS_88,
			COLLISION_SCHOOL_LOCKER_HIDE1,
			COLLISION_SCHOOL_LOCKER_HIDE2,
			COLLISION_SCHOOL_DOORFRAME_RIGHT,
			COLLISION_SCHOOL_DOORFRAME_LEFT,
		};

		for (unsigned i = 0; i < backgroundData.size(); i++)
		{
			for (unsigned j = 0; j < backgroundData[i].size(); j++)
			{
				for (unsigned k = 0; k < SCHOOL_FLOORTOTAL; k++)
				{
					if (backgroundData[i][j] == ignoreFloorTiles[k]) //Setting all floor tiles to be 0
					{
						if(sceneryData[i][j] > -1)
						{
						}
						else
						{
							collisionData[i][j] = 1;
						}
					}
				}
			}
		}

		for (unsigned i = 0; i < backgroundData.size(); i++)
		{
			for (unsigned j = 0; j < backgroundData[i].size(); j++)
			{
				for (unsigned k = 0; k < SCHOOL_DEBRISTOTAL; ++k)
				{
					if (sceneryData[i][j] == ignoreTiles[k])
					{
						this->collisionData[i][j] = collisionTiles[k];
					}
				}
			}
		}
	}
	else if (this->theTileset == TILESET_POOL)
	{
		int ignoreTiles[MECH_IGNORETOTAL] = {
			MECH_HIDE1,
			MECH_HIDE2,};

			int collisionTiles[MECH_IGNORETOTAL] = {
				COLLISION_MECH_HIDE1,
				COLLISION_MECH_HIDE2};

				for (unsigned i = 0; i < backgroundData.size(); i++)
				{
					for (unsigned j = 0; j < backgroundData[i].size(); j++)
					{
						for (unsigned k = 0; k < MECH_IGNORETOTAL; k++)
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
	case ROOM_TUTORIAL_SIGHT:
		{


		}
		break;
	case ROOM_TWO_01_SIGHT:
		{

		}
		break;
	case ROOM_TWO_02_SIGHT:
		{
			/*	int count = 0;
			for (int j = 0; j < numExit.size(); j++)
			{
			if(numExit[j]->exitDirection == EXIT_UP && numExit[j]->roomType == ROOM_TUTORIAL_SIGHT)
			{
			count ++;
			}
			}
			if(count == 0)
			{
			numExit[exitCounter]->exitPositionX = 8;
			numExit[exitCounter]->exitPositionY = 34;

			exitCounter++;
			}
			else if(count == 1)
			{
			numExit[exitCounter]->exitPositionX = 8;
			numExit[exitCounter]->exitPositionY = 34;

			exitCounter++;
			}*/
		}
		break;
	case ROOM_THREE_01_SIGHT:
		{
			if(exit == EXIT_RIGHT)
			{
				numExit[exitCounter]->exitPositionX = 29;
				numExit[exitCounter]->exitPositionY = 11;

				exitCounter++;
			}
		}
		break;
	case ROOM_THREE_02_SIGHT:
		{
			if(exit == EXIT_DOWN)
			{
				numExit[exitCounter]->exitPositionX = 8;
				numExit[exitCounter]->exitPositionY = 34;

				exitCounter++;
			}
			else if(exit == EXIT_UP)
			{
				numExit[exitCounter]->exitPositionX = 11;
				numExit[exitCounter]->exitPositionY = 3;

				exitCounter++;
			}
		}
		break;/*
			  case ROOM_THREE_03_SIGHT:
			  {
			  if(exit == EXIT_DOWN)
			  {
			  numExit[exitCounter]->exitPositionX = 9;
			  numExit[exitCounter]->exitPositionY = 24;

			  exitCounter++;
			  }
			  }
			  break;*/
	case ROOM_FRIENDS_CLASSROOM_SYMMETRY:
		{
			if (exit == EXIT_DOWN)
			{
				int counter = 0;
				for (unsigned j = 0; j < numExit.size(); j++)
				{
					if (numExit[j]->exitDirection == EXIT_DOWN && numExit[j]->roomType == ROOM_FRIENDS_CLASSROOM_SYMMETRY)
					{
						counter++;
					}
				}

				if (counter == 0)
				{
					numExit[exitCounter]->exitPositionX = 5;
					numExit[exitCounter]->exitPositionY = sceneryData.size()-1;

					exitCounter++;
				}
				else if (counter == 1)
				{
					numExit[exitCounter]->exitPositionX = 25;
					numExit[exitCounter]->exitPositionY = sceneryData.size()-1;

					exitCounter++;
				}
			}
		}
		break;
	case ROOM_FRIENDS_TOILET:
		{
			if (exit == EXIT_RIGHT)
			{
				numExit[exitCounter]->exitPositionX = 17;
				numExit[exitCounter]->exitPositionY = 6;

				exitCounter++;
			}
		}
		break;
	case ROOM_FRIENDS_ROOM_ONE:
		{
			if (exit == EXIT_DOWN)
			{
				numExit[exitCounter]->exitPositionX = 6;
				numExit[exitCounter]->exitPositionY = 12;

				exitCounter++;
			}
		}
		break;
	case ROOM_FRIENDS_ROOM_TWO:
		{
			if (exit == EXIT_LEFT)
			{
				numExit[exitCounter]->exitPositionX = 1;
				numExit[exitCounter]->exitPositionY = 6;

				exitCounter++;
			}
			else if (exit == EXIT_RIGHT)
			{
				numExit[exitCounter]->exitPositionX = 17;
				numExit[exitCounter]->exitPositionY = 6;

				exitCounter++;
			}
		}
		break;
	case ROOM_FRIENDS_ROOM_THREE:
		{
			if (exit == EXIT_LEFT)
			{
				numExit[exitCounter]->exitPositionX = 1;
				numExit[exitCounter]->exitPositionY = 11;

				exitCounter++;
			}
			else if (exit== EXIT_UP)
			{
				numExit[exitCounter]->exitPositionX = 6;
				numExit[exitCounter]->exitPositionY = 3;

				exitCounter++;

				newExit = new Room_Exit(exit, this->getRoomType(), this->roomID);
				this->numExit.push_back(newExit);

				numExit[exitCounter]->exitPositionX = 7;
				numExit[exitCounter]->exitPositionY = 3;

				exitCounter++;
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