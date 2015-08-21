#ifndef WORLD_H
#define WORLD_H

#include "Room.h"

#include <vector>

enum WORLD_ID // ID for levels
{
	WORLD_MAINMENU,
	WORLD_TEST,
};

enum CONNECTION_TYPE
{
	CONNECTION_OVER_ROOMS,
	CONNECTION_UNDER_ROOMS,
	CONNECTION_LEFT_ROOMS,
	CONNECTION_RIGHT_ROOMS,
};

enum TILE_CORRIDOR
{
	TILE_CORRIDOR_FLOOR = 0,
	TILE_CORRIDOR_TOP_WALL,
	TILE_CORRIDOR_BOTTOM_WALL,
	TILE_CORRIDOR_LEFT_WALL,
	TILE_CORRIDOR_RIGHT_WALL,
	TILE_CORRIDOR_TOP_LEFT_CORNER,
	TILE_CORRIDOR_TOP_RIGHT_CORNER,
	TILE_CORRIDOR_BOTTOM_LEFT_CORNER,
	TILE_CORRIDOR_BOTTOM_RIGHT_CORNER,
	TILE_CORRIDOR_INNER_TOP_LEFT_CORNER,
	TILE_CORRIDOR_INNER_TOP_RIGHT_CORNER,
	TILE_CORRIDOR_INNER_BOTTOM_LEFT_CORNER,
	TILE_CORRIDOR_INNER_BOTTOM_RIGHTC_ORNER
};

struct Room_Exit_Connections
{
	Room_Exit_Connections(Room_Exit* exitA, Room_Exit* exitB, CONNECTION_TYPE connectionType)
	{
		this->exitA = exitA;
		this->exitB = exitB;
		this->connectionType = connectionType;

		switch (exitA->roomType)
		{
		case ROOM_TESTPUZZLE:
			{
				corridorTileIDA[TILE_CORRIDOR_FLOOR] = 162;
				corridorTileIDA[TILE_CORRIDOR_TOP_WALL] = 162;
				corridorTileIDA[TILE_CORRIDOR_BOTTOM_WALL] = 162;
				corridorTileIDA[TILE_CORRIDOR_LEFT_WALL] = 162;
				corridorTileIDA[TILE_CORRIDOR_RIGHT_WALL] = 162;
				corridorTileIDA[TILE_CORRIDOR_TOP_LEFT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_TOP_RIGHT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_BOTTOM_LEFT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_BOTTOM_RIGHT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_INNER_TOP_LEFT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_INNER_TOP_RIGHT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_INNER_BOTTOM_LEFT_CORNER] = 162;
				corridorTileIDA[TILE_CORRIDOR_INNER_BOTTOM_RIGHTC_ORNER] = 162;
			}
			break;
		}

		switch (exitB->roomType)
		{
		case ROOM_TESTPUZZLE:
			{
				corridorTileIDB[TILE_CORRIDOR_FLOOR] = 162;
				corridorTileIDB[TILE_CORRIDOR_TOP_WALL] = 162;
				corridorTileIDB[TILE_CORRIDOR_BOTTOM_WALL] = 162;
				corridorTileIDB[TILE_CORRIDOR_LEFT_WALL] = 162;
				corridorTileIDB[TILE_CORRIDOR_RIGHT_WALL] = 162;
				corridorTileIDB[TILE_CORRIDOR_TOP_LEFT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_TOP_RIGHT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_BOTTOM_LEFT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_BOTTOM_RIGHT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_INNER_TOP_LEFT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_INNER_TOP_RIGHT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_INNER_BOTTOM_LEFT_CORNER] = 162;
				corridorTileIDB[TILE_CORRIDOR_INNER_BOTTOM_RIGHTC_ORNER] = 162;
			}
			break;
		}
	}
	~Room_Exit_Connections();

	int corridorTileIDA[13];
	int corridorTileIDB[13];
	CONNECTION_TYPE connectionType;
	Room_Exit* exitA;
	Room_Exit* exitB;
};

class World : public CMap
{
public:
	World(WORLD_ID worldID);
	~World(void);

	void setWorldID(WORLD_ID worldID);	// Set World ID
	int getWorldID();					// Get World ID

	void initWorld();

	bool initCorridors(); // initialise corridors
	bool generateCorridors(); // generate corridors

	int getRoom(float playerX, float playerY);

	std::vector<Room*> m_roomList;
private:

	WORLD_ID WorldID;	// Stores ID of current map
	std::vector<Room_Exit* > exitList;
	std::vector<Room_Exit_Connections*> exitConnectionList;
	int worldWidth;
	int worldHeight;
};

#endif