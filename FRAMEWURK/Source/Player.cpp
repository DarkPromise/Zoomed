#include "Player.h"

Player::Player(std::string name)
	: on_ground(true),
	is_running(false),
	keyPressed(0),
// Protected Info
	m_maxFear(100),
	m_currFear(m_maxFear),
	m_playerSpeed(0,0,0),
	m_playerPos(0,0,0),
	m_playerDirection(1,0,0),
	m_boundingbox(1.f,1.f,1.f,-1.f,-1.f,-1.f),
	mapOffset_x(0),
	mapOffset_y(0),
	mapFineOffset_x(0),
	mapFineOffset_y(0),
	m_playerSanity(0.f)
{
	this->m_name = name;
}

Player::~Player() 
{
}

void Player::move(double dt,std::vector<std::vector<int>> collisionMap)
{
	if(controls.up)
	{
		m_playerPos.y += 8;
	}
	if(controls.down)
	{
		m_playerPos.y -= 8;
	}
	if(controls.left)
	{
		m_playerPos.x -= 8;
	}
	if(controls.right)
	{
		m_playerPos.x += 8;
	}
}

void Player::update(double dt, World* currentWorld, int currentRoom)
{
	m_playerSanity = Math::RandFloatMinMax(59.f,62.f);
	move(dt,currentWorld->m_roomList[currentRoom]->collisionData);
}

int Player::GetMapOffset_x(void)
{
	return mapOffset_x;
}

int Player::GetMapOffset_y(void)
{
	return mapOffset_y;
}

int Player::GetMapFineOffset_x(void)
{
	return mapFineOffset_x;
}
int Player::GetMapFineOffset_y(void)
{
	return mapFineOffset_y;
}

void Player::ConstraintPlayer(const int left, const int right, const int top, const int bottom, float time)
{
	
}

Inventory &Player::getInventory()
{
	return this->m_playerInventory;
}

float Player::getSanity()
{
	return this->m_playerSanity;
}