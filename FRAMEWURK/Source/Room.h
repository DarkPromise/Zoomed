#ifndef ROOM_H
#define ROOM_H

#include "Map.h"

#include <vector>
#include <iostream>

enum ROOM_TYPE
{
	ROOM_DUCKS = 0,
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
	Room(void);
	~Room(void);

	void generateRoom(); // Add objects and collision based on roomType

private:

	ROOM_TYPE roomType; // Stores room type
	std::vector<EXIT_DIRECTION> numExit; // Stores direction of each exit, and number of exits [ .size() ]
};

#endif