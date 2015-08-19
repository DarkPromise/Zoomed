#ifndef WORLD_H
#define WORLD_H

#include "Room.h"

#include <vector>

enum WORLD_ID // ID for levels
{
	WORLD_MAINMENU,
};

class World
{
public:
	World(WORLD_ID worldID);
	~World(void);

	void setWorldID(WORLD_ID worldID);	// Set World ID
	int getWorldID();					// Get World ID

	int getRoom(float playerX, float playerY);

	std::vector<Room*> m_roomList;
private:

	WORLD_ID WorldID;	// Stores ID of current map
};

#endif