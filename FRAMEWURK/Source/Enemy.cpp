#include "Enemy.h"


Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}

void Enemy::Update(int D_x, int D_y, double dt)
{

}

// Set position of the player
void Enemy::SetPos(int x, int y)
{
	theEnemyPosition_x = x;
	theEnemyPosition_y = y;
}


// Set the destination of this enemy
void Enemy::SetDestination(const int pos_x, const int pos_y)
{
	theDestination_x = pos_x;
	theDestination_y = pos_y;
}

// Get position x of the player
int Enemy::GetPos_x(void)
{
	return theEnemyPosition_x;
}

// Get position y of the player
int Enemy::GetPos_y(void)
{
	return theEnemyPosition_y;
}

// Set the destination of this enemy
int Enemy::GetDestination_x(void)
{
	return theDestination_x;
}

// Set the destination of this enemy
int Enemy::GetDestination_y(void)
{
	return theDestination_y;
}



int Enemy::CalculateDistance()
{
	return ((theDestination_x - theEnemyPosition_x)*(theDestination_x - theEnemyPosition_x) + 
			(theDestination_y - theEnemyPosition_y)*(theDestination_y - theEnemyPosition_y));
}

int Enemy::CalculateDistance_x()
{
	int x = theDestination_x - theEnemyPosition_x;

	if(x < 0)
	{
		x *= -1;
	}

	return x;
}


int Enemy::CalculateDistance_y()
{
	int y = theDestination_y - theEnemyPosition_y;

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