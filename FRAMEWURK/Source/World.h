#ifndef WORLD_H
#define WORLD_H

#include "Room.h"
#include "Enemy.h"
#include "Vector3.h"

#include <vector>

enum WORLD_ID // ID for levels
{
	WORLD_MAINMENU,
	WORLD_TEST,
	WORLD_MECH,
};

enum CONNECTION_TYPE
{
	CONNECTION_PATH_FIND,
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

struct Two_D_Grid
{
	int x, y;

    Two_D_Grid()
    {
        x = y = 0;
    }

    Two_D_Grid(int x, int y)
    {
        this->x = x;
        this->y = y;
	}
};

class Node
{
	// Current position;
	int x, y;
	// Total distance travelled
	int GValue;
	// gvalue + hvalue
	int FValue;

public:
	Node(Two_D_Grid location, int gValue, int FValue)
	{
		this->x = location.x;
		this->y = location.y;
		this->GValue = gValue;
		this->FValue = FValue;
	}

	Two_D_Grid getLocation()
	{
		return Two_D_Grid(x, y);
	}

	int getGValue() const
	{
		return GValue;
	}

	int getFValue() const
	{
		return FValue;
	}

	void calculateFValue(const Two_D_Grid endLocation)
	{
		FValue = GValue + getHValue(endLocation) * 10;
	}

	void updateGValue()
	{
		GValue += 10;
	}

	int getHValue(const Two_D_Grid endLocation)
	{
		int xDiff = endLocation.x - x;
		int yDiff = endLocation.y - y;

		int distance = (int)(sqrt( (double)(xDiff*xDiff+yDiff*yDiff) ));

		return distance;
	}

	friend bool operator< (const Node & a, const Node & b)
	{
		return a.getFValue() > b.getFValue();
	}
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
	bool setupCorridors(); // setup corridors (expand)

	int getRoom(float playerX, float playerY);

	bool pathFind(Two_D_Grid exitA, Two_D_Grid exitB);

	std::vector<Room*> m_roomList;
private:
	// for pathfinding
	std::vector<std::vector<int>> openNodes; 
	std::vector<std::vector<int>> closedNodes; 
	std::vector<std::vector<int>> directionMap; // 0 = east, 1 = north, 2 = west, 3 = south
	std::vector<Two_D_Grid> path;


	std::vector<Enemy*> enemyList;
	WORLD_ID WorldID;	// Stores ID of current map
	std::vector<Room_Exit* > exitList;
	std::vector<Room_Exit_Connections*> exitConnectionList;
	int worldWidth;
	int worldHeight;
};

#endif