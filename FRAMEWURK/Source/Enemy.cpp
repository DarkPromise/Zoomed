#include "Enemy.h"
#include "Player.h"
#include "World.h"

Enemy::Enemy(void) :
EnemyDelay(0.0)
{
	
}


Enemy::~Enemy(void)
{
}

void Enemy::Update(Player* player, World* currentWorld, double dt)
{
	this->EnemyDelay += dt;
}

// Set position of the player
void Enemy::SetPos(float x, float y)
{
	theEnemyPosition_x = x;
	theEnemyPosition_y = y;

	spawnPoint_x = x;
	spawnPoint_y = y;
}


// Set the destination of this enemy
void Enemy::SetDestination(float pos_x, float pos_y)
{
	theDestination_x = pos_x;
	theDestination_y = pos_y;
}

// Get position x of the player
float Enemy::GetPos_x(void)
{
	return theEnemyPosition_x;
}

// Get position y of the player
float Enemy::GetPos_y(void)
{
	return theEnemyPosition_y;
}

float Enemy::GetSpawn_x(void)
{
	return spawnPoint_x;
}

float Enemy::GetSpawn_y(void)
{
	return spawnPoint_y;
}

// Set the destination of this enemy
float Enemy::GetDestination_x(void)
{
	return theDestination_x;
}

// Set the destination of this enemy
float Enemy::GetDestination_y(void)
{
	return theDestination_y;
}



float Enemy::CalculateDistance()
{
	return ((theDestination_x - theEnemyPosition_x)*(theDestination_x - theEnemyPosition_x) + 
			(theDestination_y - theEnemyPosition_y)*(theDestination_y - theEnemyPosition_y));
}

float Enemy::CalculateDistance_x()
{
	float x = theDestination_x - theEnemyPosition_x;

	if(x < 0)
	{
		x *= -1;
	}

	return x;
}


float Enemy::CalculateDistance_y()
{
	float y = theDestination_y - theEnemyPosition_y;

	if(y < 0)
	{
		y *= -1;
	}

	return y;

}

float Enemy::CalculateDistance(float x, float y)
{
	return ((x - this->GetPos_x())*(x - this->GetPos_x()) + 
		(y - this->GetPos_y())*(y - this->GetPos_y()));
}

float Enemy::CalculateDistance_x(float x2)
{
	float x = x2 - theEnemyPosition_x;

	if(x < 0)
	{
		x *= -1;
	}

	return x;
}


float Enemy::CalculateDistance_y(float y2)
{
	float y = y2 - theEnemyPosition_y;

	if(y < 0)
	{
		y *= -1;
	}

	return y;

}

void Enemy::MoveRight()
{
	theEnemyPosition_x += 32;
}

void Enemy::MoveLeft()
{
	theEnemyPosition_x -= 32;
}

void Enemy::MoveUp()
{
	theEnemyPosition_y += 32;
}

void Enemy::MoveDown()
{
	theEnemyPosition_y -= 32;
}

void Enemy::SetData(std::vector<std::vector<int> > Data)
{
	colData = Data;
}

void Enemy::SetDelay(double t)
{
	EnemyDelay = t;
}

double Enemy::GetDelay()
{
	return EnemyDelay;
}