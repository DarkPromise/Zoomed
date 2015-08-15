#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum MAP_ID
{
	MAP_LEVEL1_LAYER1 = 0,
	MAP_LEVEL1_LAYER2,
	MAP_LEVEL2_LAYER1,
	MAP_LEVEL2_LAYER2,

	MAP_INSTRUCTIONS = 31,
};

class CMap
{
public:
	CMap(void);
	~CMap(void);

	void Init(const int theScreen_Height, const int theScreen_Width, const int theNumOfTiles_Height, const int theNumOfTiles_Width, const int theMap_Height, const int theMap_Width, const int theTileSize= 32);
	bool LoadMap(const std::string mapName);
	int GetNumOfTiles_Height(void);
	int GetNumOfTiles_Width(void);
	int GetTileSize(void);

	int getNumOfTiles_MapHeight(void);
	int getNumOfTiles_MapWidth(void);

	std::vector<std::vector<int> > theScreenMap;

	void setMapID(MAP_ID mapid)
	{
		this->m_iMapID = mapid;
	}

	int getMapID()
	{
		return this->m_iMapID;
	}
private:
	int theScreen_Height;
	int theScreen_Width;
	int theNumOfTiles_Height;
	int theNumOfTiles_Width;
	int theTileSize;

	int theMap_Height;
	int theMap_Width;
	int theNumOfTiles_MapHeight;
	int theNumOfTiles_MapWidth;

	int m_iMapID;

	bool LoadFile(const std::string mapName);
};

#endif
