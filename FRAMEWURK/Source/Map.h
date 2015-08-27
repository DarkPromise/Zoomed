#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum TILESET_ID // ID for tileset to render
{
	TILESET_MAIN_MENU = 0,
	TILESET_BASEMENT,
	TILESET_BLUE,
	TILESET_PURPLE,
	TILESET_RED,
	TILESET_CLEAN,
	TILESET_GENERAL,
	TILESET_NEUTRAL,
	TILESET_POOL,
	TILESET_ROOMS,
	TILESET_TORTUREROOM,
};

class CMap
{
public:
	CMap(void); // Default constructor
	CMap(const int theScreen_Height		// Height of the screen
		, const int theScreen_Width			// Width of the screen
		, const int theNumOfTiles_Height	// Number of rows ( height of screen / tilesize )
		, const int theNumOfTiles_Width		// Number of columns ( width of screen / tilesize )
		, const int theMap_Height			// Height of the map
		, const int theMap_Width			// Height of the with
		, const int theTileSize				// Tilesize
		, const TILESET_ID tileset			// What tileset is the map using
		);
	~CMap(void);	// Destructor

	bool LoadMap
		( const std::string foregroundName	// Foreground Layer -> Things in front of the player
		, const std::string sceneryName		// Scenery Layer -> Things with transparency on top of background, behind player
		, const std::string backgroundName	// Background Layer -> The base. Does not have transparency
		, const std::string collisionName	// Collision Layer -> Layer used when updating enemies/player. Stores ID for interactions 
		);

	int GetNumOfTiles_Height(void);	// Get number of tiles for height of the screen
	int GetNumOfTiles_Width(void);	// Get number of tiles for width of the screen

	void setNumOfTiles_MapHeight(int mapHeight);	// Set number of tiles for height of the map
	void setNumOfTiles_MapWidth(int mapWidth);	// Set number of tiles for height of the map

	int getNumOfTiles_MapHeight(void);	// Get number of tiles for height of the map
	int getNumOfTiles_MapWidth(void);	// Get number of tiles for height of the map

	void SetTileSize(int tilesize); // Set tilesize
	int GetTileSize(void);	// Get tilesize of the map

	std::vector<std::vector<int> > foregroundData;	// 2D vector to store foreground values
	std::vector<std::vector<int> > collisionData;	// 2D vector to store collision values
	std::vector<std::vector<int> > sceneryData;		// 2D vector to store scenery values
	std::vector<std::vector<int> > backgroundData;	// 2D vector to store background values
TILESET_ID theTileset;			// Stores ID of tileset
private:
	int theScreen_Height;		// Stores height of the screen [px]
	int theScreen_Width;		// Stores width of the screen [px]
	int theNumOfTiles_Height;	// Stores number of columns in the screen
	int theNumOfTiles_Width;	// Stores number of rows in the screen
	int theTileSize;			// Stores tile size
	

	int theMap_Height;				// Stores height of the map [px]
	int theMap_Width;				// Stores width of the map [px]
	int theNumOfTiles_MapHeight;	// Stores number of columns in the map
	int theNumOfTiles_MapWidth;		// Stores number of rows in the map

	bool LoadCollisionMap(const std::string fileName);	// Loads values from collision csv into vector
	bool LoadBackgroundMap(const std::string fileName);	// Loads values from background csv into vector
	bool LoadSceneryMap(const std::string fileName);	// Loads values from scenery csv into vector
	bool LoadForegroundMap(const std::string fileName);	// Loads values from foreground csv into vector
};

#endif
