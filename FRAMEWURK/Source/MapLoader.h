#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "Map.h"
#include "GameObject.h"

#include <vector>

class MapLoader
{
public:
	MapLoader(void);
	~MapLoader(void);

	std::vector<CMap*> m_MapList;
	std::vector<GameObject*> m_tileList;

	//**************************************\\    Tilemap(s)
	CMap * m_TileMap;
	void RenderTileMap(CMap * mapToRender);
	int tileOffset_x, tileOffset_y;

	//CMap* m_cRearMap;
	//void RenderRearTileMap();
	//int rearWallOffset_x, rearWallOffset_y;
	//int rearWallTileOffset_x, rearWallTileOffset_y;
	//int rearWallFineOffset_x, rearWallFineOffset_y;

	//***************************************\\

	//	int m = 0;
	//for(int i = 0; i < mapToRender->GetNumOfTiles_Height(); i++)
	//{
	//	for(int k = 0; k < mapToRender->GetNumOfTiles_Width()+1; k++)
	//	{
	//		m = tileOffset_x + k;
	//		if((tileOffset_x+k) >= mapToRender->getNumOfTiles_MapWidth())
	//		{
	//			break;
	//		}
	//		if(mapToRender->theScreenMap[i][m] != -1)
	//		{
	//			RenderTileOnScreen(m_meshList[GEO_BG_SPRITESHEET],false, mapToRender->theScreenMap[i][m], 32.f, (float)k*mapToRender->GetTileSize()-this->theModel->getPlayer()->GetMapFineOffset_x() , (float)575-i*mapToRender->GetTileSize());
	//		}
	//	}
	//}
};


#endif