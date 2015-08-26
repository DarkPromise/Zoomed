#include "Player.h"

Player::Player(std::string name)
	: on_ground(true),
	is_running(false),
	keyPressed(0),
// Protected Info
	m_maxFear(100),
	m_currFear(20),
	m_movementDelay(0.0),
	m_movementTimer(0.0),
	m_playerPos(0,0,0),
	m_playerDirection(1,0,0),
	m_boundingbox(1.f,1.f,1.f,-1.f,-1.f,-1.f),           //Can be used for QuadTree, just leaving here for now
	mapOffset_x(0),
	mapOffset_y(0),
	mapFineOffset_x(0),
	mapFineOffset_y(0),
	m_playerSanity(0.f),
	m_animationState(STATE_IDLE)
{
	this->m_name = name;
}

Player::~Player() 
{
}

void Player::move(double dt,std::vector<std::vector<int>> collisionMap)
{
	int yColiision = Math::Max(0, (int)((abs)(m_playerPos.y)/32)+25);
	int xColiision = (int)(m_playerPos.x/32);
	std::cout << xColiision << " " << yColiision << " " << Math::Max(0, collisionMap[yColiision][xColiision]) << std::endl;
	std::cout << collisionMap[0].size() << " " << collisionMap.size() << std::endl;

	if (controls.use)
	{
			std::cout << "Start" << std::endl;
		for(int i = 0; i < collisionMap.size(); ++i)
			{
				for(int j = 0; j < collisionMap[i].size(); ++j)
				{
					if (yColiision == i && xColiision == j)
						std::cout << "P ";
					else
						std::cout << Math::Max(0, collisionMap[i][j]) << " ";
				}
				std::cout << std::endl;
			}
		std::cout << "End" << std::endl;

		system("pause");
	}

	if(controls.up && this->m_movementTimer > m_movementDelay && (collisionMap[Math::Max(0, yColiision-1)][Math::Min(xColiision, (int)(collisionMap.size()-1))] != 1) && m_playerPos.y < 0)
	{
		this->m_movementTimer = 0.0;
		m_playerPos.y += 32;
	}
	if(controls.down && this->m_movementTimer > m_movementDelay && (collisionMap[Math::Min(yColiision+1, (int)(collisionMap.size()-1))][Math::Min(xColiision, (int)(collisionMap[0].size()-1))] != 1) && m_playerPos.y < (collisionMap.size()+25)*32)
	{
		this->m_movementTimer = 0.0;
		m_playerPos.y -= 32;
	}
	if(controls.left && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision-1] != 1) && m_playerPos.x > 0)
	{
		this->m_movementTimer = 0.0;
		m_playerPos.x -= 32;
	}
	if(controls.right && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision+1] != 1))
	{
		this->m_movementTimer = 0.0;
		m_playerPos.x += 32;
	}
}

void Player::update(double dt, World* currentWorld, int currentRoom)
{
	m_playerSanity = Math::RandFloatMinMax(60.f,80.f);
	m_movementTimer += dt;

	if(m_currFear > 50)
	{
		m_movementDelay = 0.0;
	}
	else
	{
		m_movementDelay = 0.0; // fer weng jew
	}

	move(dt,currentWorld->collisionData);

	m_currFear += dt * 10;
	if(m_currFear > 100)
	{
		m_currFear = 0;
	}
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