#include "World.h"
#include "MyMath.h"

#include <algorithm>
#include <Windows.h>


World::World(WORLD_ID worldID)
	: worldWidth(0)
	, worldHeight(0)
{
	this->WorldID = worldID;

	exitConnectionList.clear();
	exitList.clear();
}


World::~World(void)
{
	exitConnectionList.clear();
	exitList.clear();
}


void World::initWorld()
{
	worldWidth = 0; worldHeight = 0;

	for (unsigned i = 0; i < m_roomList.size(); i++)
	{
		if ((int)(m_roomList[i]->getWorldPositionX()+m_roomList[i]->backgroundData[0].size()) > worldWidth)
		{
			worldWidth = m_roomList[i]->getWorldPositionX()+m_roomList[i]->backgroundData[0].size();
		}

		if ((int)(m_roomList[i]->getWorldPositionY()+m_roomList[i]->backgroundData.size()) > worldHeight)
		{
			worldHeight = m_roomList[i]->getWorldPositionY()+m_roomList[i]->backgroundData.size();
		}
	}

	this->SetTileSize(m_roomList[0]->GetTileSize());
	this->setNumOfTiles_MapHeight(worldHeight+11); // 10 space buffer below
	this->setNumOfTiles_MapWidth(worldWidth+10); // 10 space buffer to the right

	foregroundData.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
		foregroundData[i].resize(this->getNumOfTiles_MapWidth());

	collisionData.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
		collisionData[i].resize(this->getNumOfTiles_MapWidth());

	sceneryData.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
		sceneryData[i].resize(this->getNumOfTiles_MapWidth());

	backgroundData.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
		backgroundData[i].resize(this->getNumOfTiles_MapWidth());

	for (unsigned i = 1; i < this->sceneryData.size()-1; i++) // Reset data values
	{
		std::fill(backgroundData[i].begin(), backgroundData[i].end(), -1);
		std::fill(sceneryData[i].begin(), sceneryData[i].end(), -1);
		std::fill(collisionData[i].begin(), collisionData[i].end(), -1);
		std::fill(foregroundData[i].begin(), foregroundData[i].end(), -1);
	}

	for (unsigned i = 0; i < m_roomList.size(); i++)
	{
		for (int j = 0; j < m_roomList[i]->getNumOfTiles_MapHeight(); j++)
		{
			for (int k = 0; k < m_roomList[i]->getNumOfTiles_MapWidth(); k++)
			{
				if (m_roomList[i]->backgroundData[j][k] != 0)
				{
					this->backgroundData[j+m_roomList[i]->getWorldPositionY()][k+m_roomList[i]->getWorldPositionX()] = m_roomList[i]->backgroundData[j][k];
					this->sceneryData[j+m_roomList[i]->getWorldPositionY()][k+m_roomList[i]->getWorldPositionX()] = m_roomList[i]->sceneryData[j][k];
					this->foregroundData[j+m_roomList[i]->getWorldPositionY()][k+m_roomList[i]->getWorldPositionX()] = m_roomList[i]->foregroundData[j][k];
					this->collisionData[j+m_roomList[i]->getWorldPositionY()][k+m_roomList[i]->getWorldPositionX()] = m_roomList[i]->collisionData[j][k];
				}
			}
		}
	}

	for (unsigned i = 0; i < m_roomList.size(); i++)
	{
		for (unsigned j=0; j < m_roomList[i]->getExitSize(); j++)
		{
			exitList.push_back(m_roomList[i]->getExit(j));
			exitList.back()->exitPositionY += m_roomList[i]->getWorldPositionY();
			exitList.back()->exitPositionX += m_roomList[i]->getWorldPositionX();
		}
	}

	RoomExitYLessThan sortMe;
	std::sort(exitList.begin(), exitList.end(), sortMe);

	while (!initCorridors());
	while (!generateCorridors());
}

bool World::initCorridors()
{
	if (m_roomList.size() < 2)
	{
		if (exitList.size() > 0) // Not supposed to have exits
		{
			MessageBox(NULL,L"Error", L"Check exits", NULL);
			return false;
		}
		return true;
	}

	//2 rooms or more, generate exits
	bool foundPath = false;
	Room_Exit* highestExit = exitList[0];
	Room_Exit* secondHighestExit = exitList[1];

	while (!foundPath)
	{
		if (exitList.size() == 3)
		{
			if (highestExit->exitDirection == EXIT_UP)
			{
			}
			else if (highestExit->exitDirection == EXIT_DOWN)
			{
				if (secondHighestExit->exitDirection == EXIT_UP)
				{
				}
				else if (secondHighestExit->exitDirection == EXIT_DOWN)
				{
					int lowerX = 0, upperX = 0;
					if (highestExit->exitPositionX < secondHighestExit->exitPositionX)
					{
						lowerX = highestExit->exitPositionX;
						upperX = secondHighestExit->exitPositionX;
					}
					else
					{
						lowerX = secondHighestExit->exitPositionX;
						upperX = highestExit->exitPositionX;
					}

					for (int i = lowerX; (i <= upperX) && !foundPath; i++)
					{
						for (int j = 1; (j <= 5) && !foundPath; j++)
						{
							if (backgroundData[secondHighestExit->exitPositionY+j][lowerX+i] >999) // if there's a room in between
							{
								std::cout << "room in betweeN" << std::endl;
								int connection_type = Math::RandIntMinMax(0, 1);

								if (connection_type == 0) // one over
								{
									Room_Exit_Connections* newConnection = new Room_Exit_Connections(highestExit, secondHighestExit, CONNECTION_OVER_ROOMS);
									exitConnectionList.push_back(newConnection);
									std::cout << "Over" << std::endl;

									connection_type = Math::RandIntMinMax(0, 1);
									if (connection_type == 0) // connect left room to bottom room
									{
										if (highestExit->exitPositionX < secondHighestExit->exitPositionX)
										{
											newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_LEFT_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
										else
										{
											newConnection = new Room_Exit_Connections(secondHighestExit, exitList[2], CONNECTION_LEFT_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
									}
									else // connect right room to bottom room
									{
										if (highestExit->exitPositionX > secondHighestExit->exitPositionX)
										{
											newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_RIGHT_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
										else
										{
											newConnection = new Room_Exit_Connections(secondHighestExit, exitList[2], CONNECTION_RIGHT_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
									}
									foundPath = true;
								}
								else // connect everything through bottom
								{
									std::cout << "clean case" << std::endl;
									Room_Exit_Connections* newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_UNDER_ROOMS);
									exitConnectionList.push_back(newConnection);

									newConnection = new Room_Exit_Connections(secondHighestExit, exitList[2], CONNECTION_UNDER_ROOMS);
									exitConnectionList.push_back(newConnection);
									foundPath = true;
								}
							}
							else // space in between
							{
								int connection_type = 0; //Math::RandIntMinMax(0, 1);

								if (connection_type == 0)
								{
									connection_type = 1;//Math::RandIntMinMax(0, 1);

									if (highestExit->exitPositionX < secondHighestExit->exitPositionX)
									{
										if (connection_type == 0) // connect left room below bottom room
										{
											Room_Exit_Connections* newConnection = new Room_Exit_Connections(highestExit, secondHighestExit, CONNECTION_UNDER_ROOMS);
											exitConnectionList.push_back(newConnection);

											newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_UNDER_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
										else // connect left room to left of bottom room
										{
											Room_Exit_Connections* newConnection = new Room_Exit_Connections(highestExit, secondHighestExit, CONNECTION_UNDER_ROOMS);
											exitConnectionList.push_back(newConnection);

											newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_LEFT_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
										foundPath = true;
									}
									else
									{
										if (connection_type == 0) // connect right room to below room
										{
											Room_Exit_Connections* newConnection = new Room_Exit_Connections(highestExit, secondHighestExit, CONNECTION_UNDER_ROOMS);
											exitConnectionList.push_back(newConnection);

											newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_UNDER_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
										else // connect right room to right of bottom room
										{
											Room_Exit_Connections* newConnection = new Room_Exit_Connections(highestExit, secondHighestExit, CONNECTION_UNDER_ROOMS);
											exitConnectionList.push_back(newConnection);

											newConnection = new Room_Exit_Connections(highestExit, exitList[2], CONNECTION_RIGHT_ROOMS);
											exitConnectionList.push_back(newConnection);
										}
										foundPath = true;
									}
								}
							}
						}
					}
				}
				else if (secondHighestExit->exitDirection == EXIT_LEFT)
				{
				}
				else if (secondHighestExit->exitDirection == EXIT_RIGHT)
				{
				}
			}
			else if (highestExit->exitDirection == EXIT_LEFT)
			{
			}
			else if (highestExit->exitDirection == EXIT_RIGHT)
			{
			}
		}
	}
	return true;
}

bool World::generateCorridors()
{
	if (exitList.size() != 0)
	{
		if (exitConnectionList.size() != exitList.size()-1)
		{
			std::cout << "SOMETHING WENT WRONG. WENGYEW PLS FIX" << " " << exitConnectionList.size() << " " << exitList.size() << std::endl;
			return false;
		}

		for (unsigned i = 0; i < exitConnectionList.size(); i++)
		{
			if (exitConnectionList[i]->connectionType == CONNECTION_OVER_ROOMS)
			{
				std::cout << "Connection Over" << std::endl;
			}
			else if (exitConnectionList[i]->connectionType == CONNECTION_UNDER_ROOMS)
			{
				std::cout << "Connection Under" << std::endl;
				int lowerCorridorY = exitConnectionList[i]->exitB->exitPositionY + (3*Math::RandIntMinMax(1, 3));

				int leftCorridorX = exitConnectionList[i]->exitA->exitPositionX, rightCorridorX = exitConnectionList[i]->exitB->exitPositionX;
				if (exitConnectionList[i]->exitA->exitPositionX > exitConnectionList[i]->exitB->exitPositionX)
				{
					leftCorridorX = exitConnectionList[i]->exitB->exitPositionX;
					rightCorridorX = exitConnectionList[i]->exitA->exitPositionX;
				} // assign left and right limit for X

				bool foundPath = false;
				int upperCorridorY = lowerCorridorY;
				int leftCornerX = 0, rightCornerX = 0;
				while (!foundPath)
				{
					foundPath = true;
					if (exitConnectionList[i]->exitA->exitPositionX < exitConnectionList[i]->exitB->exitPositionX)
					{
						for (int j = leftCorridorX; (j <= rightCorridorX) && foundPath; j++)
						{
							if (backgroundData[upperCorridorY][j] != -1) // not empty
							{
								if (( backgroundData[upperCorridorY][j] != exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR])
									|| (backgroundData[upperCorridorY][j] != exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]))
								{
									leftCornerX = j-3 ; // assign left value
									for (int k = rightCorridorX; (k >= leftCorridorX) && rightCornerX == 0; k--)
									{
										if (backgroundData[upperCorridorY][k] != -1) // not empty
										{
											if (( backgroundData[upperCorridorY][k] != exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR])
												|| (backgroundData[upperCorridorY][k] != exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]))
											{
												rightCornerX = k+3; // assign right value

											}
										}
									}
									foundPath = false;
									upperCorridorY -= 1;
								}
							}
						}
					}
					else
					{
						for (int j = rightCorridorX; (j >= leftCorridorX) && foundPath; j--)
						{
							if (backgroundData[upperCorridorY][j] != -1) // not empty
							{
								if (( backgroundData[upperCorridorY][j] != exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR])
									|| (backgroundData[upperCorridorY][j] != exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]))
								{
									rightCornerX = j+3 ; // assign right value
									for (int k = leftCorridorX; (k <= rightCorridorX) && leftCornerX == 0; k++)
									{
										if (backgroundData[upperCorridorY][k] != -1) // not empty
										{
											if (( backgroundData[upperCorridorY][k] != exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR])
												|| (backgroundData[upperCorridorY][k] != exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]))
											{
												leftCornerX = k-3; // assign left value

											}
										}
									}
									foundPath = false;
									upperCorridorY -= 1;
								}
							}
						}
					}
				}

				if (upperCorridorY != lowerCorridorY)
				{
					upperCorridorY += Math::RandIntMinMax(0, 0);
					if (upperCorridorY % 3 != 0)
					{
						upperCorridorY -= (upperCorridorY%3);
					}

					for (int j = exitConnectionList[i]->exitA->exitPositionY; j < upperCorridorY; j++)
					{
						this->backgroundData[j][exitConnectionList[i]->exitA->exitPositionX] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
					} // extend downwards, higher room

					for (int j = exitConnectionList[i]->exitB->exitPositionY; j < lowerCorridorY; j++)
					{
						this->backgroundData[j][exitConnectionList[i]->exitB->exitPositionX] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
					} // extend downwards, lower room


					if (exitConnectionList[i]->exitA->exitPositionX < exitConnectionList[i]->exitB->exitPositionX) // left exit is higher
					{
						//connect
						for (int j = exitConnectionList[i]->exitA->exitPositionX; j < rightCornerX; j++) // horizonal to corner
						{
							this->backgroundData[upperCorridorY][j] = exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR];
						}
						for (int j = exitConnectionList[i]->exitB->exitPositionX; j > rightCornerX; j--)
						{
							this->backgroundData[lowerCorridorY][j] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
						}
						for (int j = lowerCorridorY; j >= upperCorridorY; j--) // vertical
						{
							this->backgroundData[j][rightCornerX] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
						}
					}
					else // right exit is higher
					{
						//connect
						std::cout << "right exit higher" << leftCorridorX<< " " << leftCornerX << " " << std::endl;
						for (int j = leftCorridorX; j <= leftCornerX; j++) // horizonal to corner
						{
							this->backgroundData[lowerCorridorY][j] = exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR];
						}
						for (int j = rightCorridorX; j >= rightCornerX; j--)
						{
							this->backgroundData[upperCorridorY][j] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
						}
						for (int j = lowerCorridorY; j >= upperCorridorY; j-- ) // vertical
						{
							this->backgroundData[j][leftCornerX] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
						}
					}					
				}
				else
				{	
					std::cout << "straight" << std::endl;
					//for (int j = exitConnectionList[i]->exitA->exitPositionY; j < lowerCorridorY; j++)
					//{
					//	this->backgroundData[j][exitConnectionList[i]->exitA->exitPositionX] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
					//} // extend downwards, higher room

					//for (int j = exitConnectionList[i]->exitB->exitPositionY; j < lowerCorridorY; j++)
					//{
					//	this->backgroundData[j][exitConnectionList[i]->exitB->exitPositionX] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
					//} // extend downwards, lower room

					//for (int j = leftCorridorX; j <= rightCorridorX; j++)
					//{
					//	this->backgroundData[lowerCorridorY][j] = exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR];
					//}// horizontal
				}
			}
			else if (exitConnectionList[i]->connectionType == CONNECTION_LEFT_ROOMS)
			{
				std::cout << "Connection Left" << std::endl;
				//stub below room
				int LowerCorridorA = exitConnectionList[i]->exitA->exitPositionY+3, lowerCorridorB = exitConnectionList[i]->exitB->exitPositionY+3;

				for (int j = exitConnectionList[i]->exitA->exitPositionY; j <= LowerCorridorA; j++)
				{
					this->backgroundData[j][exitConnectionList[i]->exitA->exitPositionX] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
				} // extend downwards, higher room

				for (int j = exitConnectionList[i]->exitB->exitPositionY; j <= lowerCorridorB; j++)
				{
					this->backgroundData[j][exitConnectionList[i]->exitB->exitPositionX] = (exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]);
				} // extend downwards, lower room

				int LeftCorridorA = exitConnectionList[i]->exitA->exitPositionX-8, LeftCorridorB = exitConnectionList[i]->exitB->exitPositionX-8;

				//extend left
				for (int j = exitConnectionList[i]->exitA->exitPositionX; j > LeftCorridorA; j--)
				{
					this->backgroundData[exitConnectionList[i]->exitA->exitPositionY+3][j] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
				} // extend left, higher room

				for (int j = exitConnectionList[i]->exitB->exitPositionX; j > LeftCorridorB; j--)
				{
					this->backgroundData[exitConnectionList[i]->exitB->exitPositionY+3][j] = (exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]);
				} // extend left, lower room

				for (int j = LowerCorridorA; j <= lowerCorridorB; j++)
				{
					this->backgroundData[j][LeftCorridorA] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
				} // extend downwards, higher room

				for (int j = lowerCorridorB; j <= lowerCorridorB; j++)
				{
					this->backgroundData[j][LeftCorridorB] = exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR];
				} // extend downwards, lower room

				if (LeftCorridorB < LeftCorridorA) // swap values if not in order
				{
					LeftCorridorB = LeftCorridorB ^ LeftCorridorA;
					LeftCorridorA = LeftCorridorB ^ LeftCorridorA;
					LeftCorridorB = LeftCorridorB ^ LeftCorridorA;
				}

				for (int j = LeftCorridorA; j <= LeftCorridorB; j++)
				{
 					this->backgroundData[lowerCorridorB][j] = exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR];
				}
			}
			else if (exitConnectionList[i]->connectionType == CONNECTION_RIGHT_ROOMS)
			{
				std::cout << "Connection right" << std::endl;
				//stub below room
				int LowerCorridorA = exitConnectionList[i]->exitA->exitPositionY+3, LowerCorridorB = exitConnectionList[i]->exitB->exitPositionY+3;
				int RightCorridorX = exitConnectionList[i]->exitB->exitPositionX;
				while(backgroundData[exitConnectionList[i]->exitB->exitPositionY][RightCorridorX] != -1) // find right limit of right corridor
				{
					++RightCorridorX;
				}
				RightCorridorX += Math::RandIntMinMax(2, 4);

				for (int j = exitConnectionList[i]->exitA->exitPositionY; j <= LowerCorridorA; j++)
				{
					this->backgroundData[j][exitConnectionList[i]->exitA->exitPositionX] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
				} // extend downwards, higher room

				for (int j = exitConnectionList[i]->exitB->exitPositionY; j <= LowerCorridorB; j++)
				{
					this->backgroundData[j][exitConnectionList[i]->exitB->exitPositionX] = (exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]);
				} // extend downwards, lower room

				//extend right/left
				if (exitConnectionList[i]->exitA->exitPositionX < RightCorridorX)
				{
					for (int j = exitConnectionList[i]->exitA->exitPositionX; j < RightCorridorX; j++)
					{
						this->backgroundData[exitConnectionList[i]->exitA->exitPositionY+3][j] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
					} // extend right, higher room
				}
				else
				{
					for (int j = exitConnectionList[i]->exitA->exitPositionX; j > RightCorridorX; j--)
					{
						this->backgroundData[exitConnectionList[i]->exitA->exitPositionY+3][j] = (exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR]);
					} // extend left, higher room
				}

				for (int j = exitConnectionList[i]->exitB->exitPositionX; j < RightCorridorX; j++)
				{
					this->backgroundData[exitConnectionList[i]->exitB->exitPositionY+3][j] = (exitConnectionList[i]->corridorTileIDB[TILE_CORRIDOR_FLOOR]);
				}// extend right, lower room

				for (int j = LowerCorridorA; j <= LowerCorridorB; j++)
				{
 					this->backgroundData[j][RightCorridorX] = exitConnectionList[i]->corridorTileIDA[TILE_CORRIDOR_FLOOR];
				} // connect right
			}
		}
	}

	return true;
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