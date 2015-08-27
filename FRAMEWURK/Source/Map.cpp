#include "Map.h"

CMap::CMap(void)
{
}

CMap::CMap(const int theScreen_Height, const int theScreen_Width, const int theNumOfTiles_Height, const int theNumOfTiles_Width, const int theMap_Height, const int theMap_Width, const int theTileSize, const TILESET_ID tileset)
: theScreen_Height(0)
, theScreen_Width(0)
, theNumOfTiles_Height(0)
, theNumOfTiles_Width(0)
, theMap_Height(0)
, theMap_Width(0)
, theNumOfTiles_MapHeight(0)
, theNumOfTiles_MapWidth(0)
, theTileSize(0)
, theTileset(TILESET_MAIN_MENU)
{
	this->theScreen_Height		= theScreen_Height;
	this->theScreen_Width		= theScreen_Width;
	this->theNumOfTiles_Height	= theNumOfTiles_Height;
	this->theNumOfTiles_Width	= theNumOfTiles_Width;
	this->theTileSize			= theTileSize;
	this->theMap_Height			= theMap_Height;
	this->theMap_Width			= theMap_Width;
	this->theTileset			= tileset;

	theNumOfTiles_MapHeight = (int) (theMap_Height / theTileSize)+1;
	theNumOfTiles_MapWidth = (int) (theMap_Width / theTileSize);

	foregroundData.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		foregroundData[i].resize(theNumOfTiles_MapWidth);

	collisionData.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		collisionData[i].resize(theNumOfTiles_MapWidth);

	sceneryData.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		sceneryData[i].resize(theNumOfTiles_MapWidth);

	backgroundData.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		backgroundData[i].resize(theNumOfTiles_MapWidth);
}

CMap::~CMap(void)
{
	foregroundData.clear();
	collisionData.clear();
	sceneryData.clear();
	backgroundData.clear();
}

void CMap::SetTileSize(int tilesize)
{
	this->theTileSize = tilesize;
}

void CMap::setNumOfTiles_MapHeight(int mapHeight)
{
	this->theNumOfTiles_MapHeight = mapHeight;
}

void CMap::setNumOfTiles_MapWidth(int mapWidth)
{
	this->theNumOfTiles_MapWidth = mapWidth;
}

bool CMap::LoadMap(const std::string mapName, const std::string sceneryName, const std::string backgroundName, const std::string collisionName)
{
	if (LoadForegroundMap(mapName))
	{
		std::cout << mapName << " has been loaded. " << std::endl;
		if (LoadCollisionMap(collisionName))
		{
			std::cout << collisionName << " has been loaded. " << std::endl;
			if (LoadSceneryMap(sceneryName))
			{
				std::cout << sceneryName << " has been loaded. " << std::endl;
				if (LoadBackgroundMap(backgroundName))
				{
					std::cout << backgroundName << " has been loaded. " << std::endl << std::endl;
					return true;
				}
				std::cout << "Failed to load background" << std::endl;
				return false;
			}
			std::cout << "Failed to load scenery" << std::endl;
			return false;
		}
		std::cout << "Failed to load collision" << std::endl;
		return false;
	}
	std::cout << "Failed to load foreground" << std::endl;
	return false;
}

bool CMap::LoadCollisionMap(const std::string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	std::ifstream file(mapName.c_str());
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			std::string aLineOfText = "";
			getline(file, aLineOfText);

			if  (theLineCounter>=theNumOfTiles_MapHeight)
				break;

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
					if ( theMaxNumOfColumns != theNumOfTiles_MapWidth)
						return false;
				}
				else
				{
					int theColumnCounter = 0;

					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						collisionData[theLineCounter][theColumnCounter++] = atoi(token.c_str());
					}
				}
			}

			theLineCounter++;
		}
	}
	return true;
}
bool CMap::LoadBackgroundMap(const std::string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	std::ifstream file(mapName.c_str());
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			std::string aLineOfText = "";
			getline(file, aLineOfText);

			if  (theLineCounter>=theNumOfTiles_MapHeight)
				break;

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
					if ( theMaxNumOfColumns != theNumOfTiles_MapWidth)
						return false;
				}
				else
				{
					int theColumnCounter = 0;

					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						backgroundData[theLineCounter][theColumnCounter++] = atoi(token.c_str());
					}
				}
			}

			theLineCounter++;
		}
	}
	return true;
}
bool CMap::LoadSceneryMap(const std::string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	std::ifstream file(mapName.c_str());
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			std::string aLineOfText = "";
			getline(file, aLineOfText);

			if  (theLineCounter>=theNumOfTiles_MapHeight)
				break;

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
					if ( theMaxNumOfColumns != theNumOfTiles_MapWidth)
						return false;
				}
				else
				{
					int theColumnCounter = 0;

					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						sceneryData[theLineCounter][theColumnCounter++] = atoi(token.c_str());
					}
				}
			}

			theLineCounter++;
		}
	}
	return true;
}
bool CMap::LoadForegroundMap(const std::string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	std::ifstream file(mapName.c_str());
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			std::string aLineOfText = "";
			getline(file, aLineOfText);

			if  (theLineCounter>=theNumOfTiles_MapHeight)
				break;

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
					if ( theMaxNumOfColumns != theNumOfTiles_MapWidth)
					{
						std::cout << theMaxNumOfColumns << std::endl;
						return false;

					}
				}
				else
				{
					int theColumnCounter = 0;

					std::string token;
					std::istringstream iss(aLineOfText);
					while(getline(iss, token, ',') && (theColumnCounter<theNumOfTiles_MapWidth))
					{
						foregroundData[theLineCounter][theColumnCounter++] = atoi(token.c_str());
					}
				}
			}

			theLineCounter++;
		}
	}
	return true;
}

int CMap::GetNumOfTiles_Height(void)
{
	return theNumOfTiles_Height;
}

int CMap::GetNumOfTiles_Width(void)
{
	return theNumOfTiles_Width;
}

int CMap::getNumOfTiles_MapHeight(void)
{
	return theNumOfTiles_MapHeight;
}

int CMap::getNumOfTiles_MapWidth(void)
{
	return theNumOfTiles_MapWidth;
}

int CMap::GetTileSize(void)
{
	return theTileSize;
}