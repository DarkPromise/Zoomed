#ifndef ROOM_H
#define ROOM_H

#include "Map.h"

#include <vector>
#include <iostream>

enum ROOM_TYPE
{
	ROOM_MAINMENU,

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

class Room : public CMap
{
public:
	Room(ROOM_TYPE roomType);
	~Room(void);

	void generateRoom(); // Add objects and collision based on roomType

private:

	int worldPositionX, worldPositionY; // Position of the room in world (bottom left)
	ROOM_TYPE roomType; // Stores room type
	std::vector<EXIT_DIRECTION> numExit; // Stores direction of each exit, and number of exits [ .size() ]
};

#endif