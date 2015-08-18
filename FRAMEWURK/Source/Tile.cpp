#include "Tile.h"

Tile::Tile(TILE_ID tileID) : m_bActive(true),
	m_bCollidable(false)
{
	this->m_eTileID = tileID;
}

Tile::~Tile(void)
{
}

bool Tile::isActive()
{
	return this->m_bActive;
}

void Tile::setActive()
{
	if(this->m_bActive)
	{
		m_bActive = true;
	}
	else
	{
		m_bActive = false;
	}
}

bool Tile::isCollidable()
{
	return this->m_bCollidable;
}

void Tile::setCollidable()
{
	if(this->m_bCollidable)
	{
		m_bCollidable = true;
	}
	else
	{
		m_bCollidable = false;
	}
}

TILE_ID Tile::getTileID()
{
	return this->m_eTileID;
}

void Tile::setTileID(TILE_ID tileID)
{
	this->m_eTileID = tileID;
}



