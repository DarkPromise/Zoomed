#include "Player.h"

Player::Player(std::string name)
	: on_ground(true),
	is_running(false),
	keyPressed(0),
// Protected Info
	m_maxFear(100),
	m_currFear(5),
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
	m_animationState(STATE_IDLE),
	m_fearCooldown(0.0)
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
		m_currFear += (float)dt * 3;
		m_fearCooldown = 1.0;
	}
	if(controls.down && this->m_movementTimer > m_movementDelay && (collisionMap[Math::Min(yColiision+1, (int)(collisionMap.size()-1))][Math::Min(xColiision, (int)(collisionMap[0].size()-1))] != 1) && m_playerPos.y < (collisionMap.size()+25)*32)
	{
		this->m_movementTimer = 0.0;
		m_playerPos.y -= 32;
		m_currFear += (float)dt * 3;
		m_fearCooldown = 1.0;
	}
	if(controls.left && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision-1] != 1) && m_playerPos.x > 0)
	{
		this->m_movementTimer = 0.0;
		m_playerPos.x -= 32;
		m_currFear += (float)dt * 3;
		m_fearCooldown = 1.0;
	}
	if(controls.right && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision+1] != 1))
	{
		this->m_movementTimer = 0.0;
		m_playerPos.x += 32;
		m_currFear += (float)dt * 3;
		m_fearCooldown = 1.0;
	}
}

void Player::update(double dt, World* currentWorld, int currentRoom)
{
	getPassiveEffect(this->m_playerInventory.getItem(2)); //Slot 2 = Equipment

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

	m_fearCooldown -= dt;
	if(m_fearCooldown <= 0.0)
	{
		m_fearCooldown = 0.0;
		m_currFear -= (float)dt * 1.5;
	}
	m_currFear = Math::Clamp(m_currFear,2.f,100.f);
	m_playerSanity = Math::RandFloatMinMax(60.f,80.f);
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

void Player::getPassiveEffect(Item * item)
{
	switch(item->getItemID())
	{
	case ITEM_REDUCE_NOISE_POTION:
		break;
	case ITEM_REDUCED_NOISE_GAIN_POTION:
		break;
	case ITEM_SIGHT_POTION:
		break;
	case ITEM_REDUCED_FEAR_GAIN_POTION:
		break;
	case ITEM_REDUCE_FEAR_POTION:
		break;
	case ITEM_SUPPRESS_FEAR_POTION:
		break;
	case ITEM_COMPASS:
		break;
	case ITEM_MAP:
		break;
	case ITEM_SAFETY_CHARM:
		break;
	case ITEM_EQUIPMENT_BOOTS:
		break;
	case ITEM_EQUIPMENT_GLASSES:
		break;
	case ITEM_EQUIPMENT_ARMOR:
		break;
	case ITEM_EQUIPMENT_INVISCLOAK:
		break;
	}
}