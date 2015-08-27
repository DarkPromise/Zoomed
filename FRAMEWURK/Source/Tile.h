#ifndef TILE_H
#define TILE_H

enum TILE_ID
{
	Tile1 = 0,
};

class Tile
{
public:
	Tile(TILE_ID tileID);
	~Tile(void);

	bool isActive();
	void setActive();

	bool isCollidable();
	void setCollidable();

	TILE_ID getTileID();
	void setTileID(TILE_ID tileID);

private:
	TILE_ID m_eTileID;
	bool m_bActive;
	bool m_bCollidable;
};

#endif