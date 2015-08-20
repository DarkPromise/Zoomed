#ifndef ROOM_H
#define ROOM_H

#include "Map.h"

#include <vector>
#include <iostream>

enum ROOM_TYPE
{
	ROOM_MAINMENU,

	ROOM_TESTPUZZLE,

	ROOM_DUCKS,
	ROOM_MIRROR,
	ROOM_OMGPLEASEADDTYPES,

	ROOM_TOTAL = ROOM_OMGPLEASEADDTYPES
};

enum EXIT_DIRECTION
{
	EXIT_LEFT,
	EXIT_RIGHT,
	EXIT_UP,
	EXIT_DOWN,
};

struct Room_Object
{
	enum ROOM_OBJECT_TYPE
	{
		ROOM_OBJECT_TESTPUZZLE_BED,
		ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE,
		ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE,
		ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT,
		ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT,
		ROOM_OBJECT_TESTPUZZLE_WHITE_TABLECLOTH_TABLE,
		ROOM_OBJECT_TESTPUZZLE_BIG_WINDOW,
		ROOM_OBJECT_TESTPUZZLE_SMALL_WINDOW,
		ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET,
		ROOM_OBJECT_TESTPUZZLE_PATTERNED_FLOOR,

		// Exits
		ROOM_OBJECT_TESTPUZZLE_CLOSED_EXIT_BOTTOM,
		ROOM_OBJECT_TESTPUZZLE_OPEN_EXIT_BOTTOM,

		//Stuff on white tablecloth table
		ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE,
		ROOM_OBJECT_TESTPUZZLE_BRONZE_CANDLESTICK,
		ROOM_OBJECT_TESTPUZZLE_BRONZE_BOTTLE,
		ROOM_OBJECT_TESTPUZZLE_OPEN_BOOK,

		
	};

	Room_Object(ROOM_OBJECT_TYPE objectType, int roomHeight, int roomWidth);
	~Room_Object();
	

	ROOM_OBJECT_TYPE type;
	int width, height;
	int lowerOriginX, upperOriginX;
	int lowerOriginY, upperOriginY;
};

class Room : public CMap
{
public:
	Room(
		ROOM_TYPE roomType, 
		const int theScreen_Height, 
		const int theScreen_Width, 
		const int theNumOfTiles_Height, 
		const int theNumOfTiles_Width, 
		const int theMap_Height, 
		const int theMap_Width, 
		const int theTileSize, 
		const TILESET_ID tileset);
	~Room(void);

	void addOBJtoGenerate(Room_Object* object);

	void generateRoom(); // Add objects and collision based on roomType
	bool addObject(ROOM_TYPE type, Room_Object* object, int originX, int originY); // Add specific object to room based on position and type (origin top left)
	void addExit(EXIT_DIRECTION exit); // Adds exit to room

private:
	void reset_mapData(); // Reset map values
	bool attemptToAdd(ROOM_TYPE roomType, Room_Object* object);

	std::vector<Room_Object*> roomObjectList; // Stores all objects to be added during generateRoom()
	int attemptCounter; // Stores number of times object in room was attempted to be generated.
	int worldPositionX, worldPositionY; // Position of the room in world (bottom left)
	ROOM_TYPE roomType; // Stores room type
	std::vector<EXIT_DIRECTION> numExit; // Stores direction of each exit, and number of exits [ .size() ]
};

#endif