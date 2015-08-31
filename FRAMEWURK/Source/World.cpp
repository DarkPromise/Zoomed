#include "World.h"
#include "MyMath.h"

#include <algorithm>
#include <Windows.h>
#include <queue> //priority_queue


World::World(WORLD_ID worldID)
	: worldWidth(0)
	, worldHeight(0)
	, UpdateWorld(false)
{
	this->WorldID = worldID;

	openNodes.clear(); 
	closedNodes.clear(); 
	directionMap.clear(); // 0 = east, 1 = north, 2 = west, 3 = south
	path.clear();


	enemyList.clear();
	exitList.clear();
	exitConnectionList.clear();
}


World::~World(void)
{
	openNodes.clear(); 
	closedNodes.clear(); 
	directionMap.clear(); // 0 = east, 1 = north, 2 = west, 3 = south
	path.clear();

	enemyList.clear();
	exitList.clear();
	exitConnectionList.clear();
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

	for (unsigned i = 0; i < this->sceneryData.size(); i++) // Reset data values
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

	this->path.clear();

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
	while (!setupCorridors());
	
}

bool World::setupCorridors()
{
	for (unsigned i = 0; i < path.size(); i++)
	{
		for (int j = -5; j <= 5; j++)
		{
			for (int k = -5; k <= 5; k++)
			{
				if (this->backgroundData[path[i].y+j][path[i].x+k] == -1)
				{
					this->backgroundData[path[i].y+j][path[i].x+k] = TILE_CORRIDOR_FLOOR;
				}
			}
			
		}
	}

	std::vector<std::vector<int>> tempCorridor = backgroundData;

	//hard coded corridor change value
	for (unsigned i = 0; i < backgroundData.size(); i++)
	{
		for (unsigned j = 0; j < backgroundData[i].size(); j++)
		{
			if (backgroundData[i][j] == TILE_CORRIDOR_FLOOR)
			{
				//whole bunches of if else
				if (backgroundData[i][j-1] == -1 && (backgroundData[i][j+1] != -1) && backgroundData[i+1][j] != -1 && backgroundData[i-1][j] != -1 && backgroundData[i-1][j+1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_LEFT_WALL;
				}
				else if (backgroundData[i][j+1] == -1 && (backgroundData[i][j-1] != -1) && backgroundData[i+1][j] != -1 && backgroundData[i-1][j] != -1 && backgroundData[i-1][j-1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_RIGHT_WALL;
				}
				else if (backgroundData[i-1][j] == -1 && backgroundData[i][j-1] != -1 && backgroundData[i][j+1] != -1 && backgroundData[i+1][j] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_TOP_WALL;
				}
				else if (backgroundData[i+1][j] == -1 && backgroundData[i][j-1] != -1 && backgroundData[i][j+1] != -1 && backgroundData[i-1][j] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_BOTTOM_WALL;
				}
				else if (backgroundData[i-1][j] != -1 && backgroundData[i+1][j] == -1 && backgroundData[i][j-1] == -1 && backgroundData[i][j+1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_BOTTOM_LEFT_CORNER;
				}
				else if (backgroundData[i-1][j] != -1 && backgroundData[i+1][j] == -1 && backgroundData[i][j+1] == -1 && backgroundData[i][j-1] != -1 && backgroundData[i+1][j-1] == -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_BOTTOM_RIGHT_CORNER;
				}
				else if (backgroundData[i+1][j] != -1 && backgroundData[i-1][j] == -1 && backgroundData[i][j-1] == -1 && backgroundData[i][j+1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_TOP_LEFT_CORNER;
				}
				else if (backgroundData[i+1][j] != -1 && backgroundData[i-1][j] == -1 && backgroundData[i][j+1] == -1 && backgroundData[i][j-1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_TOP_RIGHT_CORNER;
				}
				else if (backgroundData[i-1][j-1] != -1 && backgroundData[i-1][j] != -1 && backgroundData[i-1][j+1] == -1 && backgroundData[i][j-1] != -1 && backgroundData[i+1][j] != -1 && backgroundData[i][j+1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_INNER_TOP_RIGHT_CORNER;
				}
				else if (backgroundData[i-1][j+1] != -1 && backgroundData[i-1][j] != -1 && backgroundData[i-1][j-1] == -1 && backgroundData[i][j+1] != -1 && backgroundData[i+1][j] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_INNER_TOP_LEFT_CORNER;
				}
				else if (backgroundData[i+1][j+1] != -1 && backgroundData[i+1][j] != -1 && backgroundData[i+1][j-1] == -1 && backgroundData[i][j+1] != -1 && backgroundData[i-1][j] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_INNER_BOTTOM_LEFT_CORNER;
				}
				else if (backgroundData[i+1][j-1] != -1 && backgroundData[i+1][j] != -1 && backgroundData[i+1][j+1] == -1 && backgroundData[i][j-1] != -1 && backgroundData[i-1][j] != -1 && backgroundData[i][j+1] != -1)
				{
					tempCorridor[i][j] = TILE_CORRIDOR_INNER_BOTTOM_RIGHT_CORNER;
				}
			}
		}
	}

	backgroundData = tempCorridor;

	for (unsigned i = 0; i < backgroundData.size(); i++)
	{
		for (unsigned j = 0; j < backgroundData[i].size(); j++)
		{
			if (this->backgroundData[i][j] > TILE_CORRIDOR_FLOOR && this->backgroundData[i][j] < 1024)
			{
				this->collisionData[i][j] = 100;
			}
		}
	}

	return true;
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
	switch (this->WorldID)
	{

	default:
		{
			while (exitConnectionList.size() != exitList.size()-1)
			{
				bool correctConnections = false;

				int firstRoom = Math::RandIntMinMax(0, this->m_roomList.size()-1);
				int secondRoom = Math::RandIntMinMax(0, this->m_roomList.size()-1);


				if (exitList[firstRoom]->roomID != exitList[secondRoom]->roomID && ((!exitList[firstRoom]->connected) || (!exitList[secondRoom]->connected)))
				{
					Room_Exit_Connections* newConnection = new Room_Exit_Connections(exitList[firstRoom], exitList[secondRoom], CONNECTION_PATH_FIND);
					exitConnectionList.push_back(newConnection);
				
					exitList[firstRoom]->connected = true;
					exitList[secondRoom]->connected = true;

				/*	if (secondRoom < firstRoom)
					{
						int temp = secondRoom;
						secondRoom = firstRoom;
						firstRoom = temp;
					}*/


				}
			}
		}
		break;
	}
	
	std::cout << "exits done" << std::endl;

	return true;
}

bool World::pathFind(Two_D_Grid exitA, Two_D_Grid exitB)
{
	//open nodes
	std::priority_queue<Node> queue[2];

	//set destination background to empty
	backgroundData[exitA.y][exitA.x] = -1;
	backgroundData[exitB.y][exitB.x] = -1;

	//queue index
	int queueIndex = 0;

	//direction lists
	int iDir[4] = {1, 0, -1, 0}; // dierctionx
	int jDir[4] = {0, 1, 0, -1}; // directiony

	Node* pNode1; Node* pNode2;
	int iNext, jNext, x, y;

	//prepare the vectors
	openNodes.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
		openNodes[i].resize(this->getNumOfTiles_MapWidth());

	closedNodes.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
			closedNodes[i].resize(this->getNumOfTiles_MapWidth());

	directionMap.resize(this->getNumOfTiles_MapHeight());
	for (int i = 0; i < this->getNumOfTiles_MapHeight(); ++i)
			directionMap[i].resize(this->getNumOfTiles_MapWidth());

	for (int i = 0; i < this->getNumOfTiles_MapHeight(); i++) // Reset data values
	{
		std::fill(openNodes[i].begin(), openNodes[i].end(), 0);
		std::fill(closedNodes[i].begin(), closedNodes[i].end(), 0);
		std::fill(directionMap[i].begin(), directionMap[i].end(), 0);
	}

	// puush starting node 
	pNode1 = new Node(exitA, 0, 0);
	pNode1->calculateFValue(exitB);
	queue[queueIndex].push(*pNode1);

	//pathfinding 
	while (!queue[queueIndex].empty() )
	{
		//get open node with lowest fvalue
		pNode1 = new Node(	queue[queueIndex].top().getLocation(),
							queue[queueIndex].top().getGValue(),
							queue[queueIndex].top().getFValue());

		x = pNode1->getLocation().x;
		y = pNode1->getLocation().y;
		//std::cout << "x, y = " << x << "," << y << std::endl;

		//remove open node from list
		queue[queueIndex].pop();
		openNodes[y][x] = 0;

		//mark on closed nodes
		closedNodes[y][x] = 1;

		//std::cout << std::endl;

		/*for (int i = 30; i < closedNodes.size()-10; i++)
		{
			for (int j = 0; j < closedNodes[i].size(); j++)
			{
				if ( i == exitA.y & j == exitA.x )
					std::cout << "A" << " ";
				else if ( i == exitB.y & j == exitB.x )
					std::cout << "B" << " ";
				else if ( backgroundData[i][j] != -1 )
					std::cout << "-" << " ";
				else
					std::cout << closedNodes[i][j] << " ";
			}
			std::cout << std::endl;
		}*/
		//system("pause");

		//exit Reached
		if (x == exitB.x && y == exitB.y)
		{
			/*for (unsigned i = 30; i < closedNodes.size()-10; i++)
			{
				for (unsigned j = 0; j < closedNodes[i].size(); j++)
				{
					if ( i == exitA.y && j == exitA.x )
						std::cout << directionMap[i][j] << " ";
					else if ( i == exitB.y && j == exitB.x )
						std::cout << "B" << " ";
					else if ( backgroundData[i][j] != -1 )
						std::cout << "-" << " ";
					else
						std::cout << directionMap[i][j] << " ";
				}
				std::cout << std::endl;
			}
			system("pause");*/
			delete pNode1;
			while ( !queue[queueIndex].empty() )
				queue[queueIndex].pop();

			//std::cout << std::endl;

			/*for (unsigned i = 0; i < directionMap.size(); i++)
			{
				for (unsigned j = 0; j < directionMap[i].size(); j++)
				{
					std::cout << directionMap[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;*/
			std::vector<int> pathDirection;
			this->path.push_back(Two_D_Grid(exitA.x, exitA.y));
            while(!(x == exitA.x && y == exitA.y)) 
			{
                int temp = directionMap[y][x];
				pathDirection.push_back((temp + 4/2) % 4);
                y += iDir[temp];
                x += jDir[temp];
				this->path.push_back(Two_D_Grid(x, y));
            }
			this->path.push_back(Two_D_Grid(exitB.x, exitB.y));

			//for (unsigned i = 30; i < closedNodes.size()-10; i++)
			//{
			//	for (unsigned j = 0; j < closedNodes[i].size(); j++)
			//	{
			//		/*if ( i == exitA.y && j == exitA.x )
			//			std::cout << directionMap[i][j] << " ";
			//		else if ( i == exitB.y && j == exitB.x )
			//			std::cout << "B" << " ";
			//		else */if ( backgroundData[i][j] != -1 )
			//			std::cout << "-" << " ";
			//		else
			//		{
			//			bool hihihi = false;
			//			for (unsigned k = 0; k < path.size(); k++)
			//			{
			//				if (i == path[k].y && j == path[k].x )
			//				{
			//					hihihi = true;
			//					std::cout << "P" << " ";
			//					break;
			//				}
			//			}
			//			if (!hihihi)
			//				std::cout << " " << " ";
			//		}
			//	}
			//	std::cout << std::endl;
			//}

			//system("pause");

			return true;
		}

		//try moving in possible directions (4 directions)
		for (int i = 0; i < 4; i++)
		{
			iNext = y + iDir[i]; // index of next node to move (y)
			jNext = x + jDir[i]; // index of next node to move (x)

			// not out of vector && not filled && not in close list
			if ( !(iNext < 0 || iNext > (int)(sceneryData.size()-1) || jNext < 0 || jNext > (int)(sceneryData[0].size()-1)) )
			{
				if ( !(backgroundData[iNext][jNext] != -1 || closedNodes[iNext][jNext] == 1))
				{
					//child node
					pNode2 = new Node(Two_D_Grid(jNext, iNext), pNode1->getGValue(), pNode1->getFValue());
					pNode2->updateGValue();
					pNode2->calculateFValue(exitB);

					//add into open list if not
					if (openNodes[iNext][jNext] == 0)
					{
						openNodes[iNext][jNext] = pNode2->getFValue();
						queue[queueIndex].push(*pNode2);
						//set parent node direction
						directionMap[iNext][jNext] = ( i + 2) % 4;
					}
					else if ( openNodes[iNext][jNext] > pNode2->getFValue())
					{
						//update fvalue
						openNodes[iNext][jNext] = pNode2->getFValue();

						//update direction info
						directionMap[iNext][jNext] = (i + 2) % 4;

						//empty one queue to the other queue (ignore node to replace, push in new node)
						while (!(queue[queueIndex].top().getLocation().y == iNext && queue[queueIndex].top().getLocation().x == jNext))
						{
							queue[1-queueIndex].push(queue[queueIndex].top());
							queue[queueIndex].pop(); // transfer from queue 1 to queue 2
						}
						//remove the first node
						queue[queueIndex].pop();
						//empty larger queue to smaller queue
						if (queue[queueIndex].size() > queue[1-queueIndex].size())
						{
							queueIndex = 1 - queueIndex;
						}
						while (!queue[queueIndex].empty())
						{
							queue[1-queueIndex].push(queue[queueIndex].top());
							queue[queueIndex].pop();
						}
						queueIndex = 1 - queueIndex;

						//add next node
						queue[queueIndex].push(*pNode2);
					}
					else
					{
						delete pNode2;
					}
				}
			}
		}
		delete pNode1;
	}
	//no path found ;_;
	std::cout << "WENYGEW" << std::endl;
	system("pause");
	return false;
}

bool World::generateCorridors()
{
	if (exitList.size() != 0)
	{
		if (exitConnectionList.size() != exitList.size()-1)
		{
			//std::cout << "SOMETHING WENT WRONG. WENGYEW PLS FIX" << " " << exitConnectionList.size() << " " << exitList.size() << std::endl;
			//return false;
		}

		for (unsigned i = 0; i < exitConnectionList.size(); i++)
		{
			if (exitConnectionList[i]->connectionType == CONNECTION_PATH_FIND)
			{
				this->pathFind(Two_D_Grid(exitConnectionList[i]->exitA->exitPositionX, exitConnectionList[i]->exitA->exitPositionY), Two_D_Grid(exitConnectionList[i]->exitB->exitPositionX, exitConnectionList[i]->exitB->exitPositionY));
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