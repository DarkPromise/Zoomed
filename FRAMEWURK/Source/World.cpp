#include "World.h"


World::World(WORLD_ID worldID)
{
	this->WorldID = worldID;
}


World::~World(void)
{
}

void World::setWorldID(WORLD_ID worldID)
{
	this->WorldID = worldID;
}

int World::getWorldID()
{
	return WorldID;
}

int World::getRoom(float playerX, float playerY)
{
	return 0;
}