#include "Enemy.h"
#include <iostream>

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
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

//// Set Animation Invert status of the player
//void CEnemy::SetAnimationInvert(bool enemyAnimationInvert)
//{
//	this->enemyAnimationInvert = enemyAnimationInvert;
//}
//// Get Animation Invert status of the player
//bool CEnemy::GetAnimationInvert(void)
//{
//	return enemyAnimationInvert;
//}
//
//// Set Animation Counter of the player
//void CEnemy::SetAnimationCounter(int enemyAnimationCounter)
//{
//	this->enemyAnimationCounter = enemyAnimationCounter;
//}
//// Get Animation Counter of the player
//int CEnemy::GetAnimationCounter(void)
//{
//	return enemyAnimationCounter;
//}

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


void Enemy::KILL(int D_x, int D_y)
{

	SetDestination(D_x, D_y);

	int distanceHeroToEnemy = CalculateDistance();

	std::cout << D_x << "     " << D_y << std::endl;

	std::cout << theEnemyPosition_x  << "     " << theEnemyPosition_y << std::endl;

	if ( distanceHeroToEnemy < 1000000.0f )
	{
		if(CalculateDistance_x() > CalculateDistance_y())
		{
			if(theEnemyPosition_x != theDestination_x)
				theEnemyPosition_x = theEnemyPosition_x + (theDestination_x - theEnemyPosition_x > 0 ? 32 : -32 );
		}
		else if(CalculateDistance_y() > CalculateDistance_x())
		{
			if(theEnemyPosition_y != theDestination_y)
				theEnemyPosition_y = theEnemyPosition_y + (theDestination_y - theEnemyPosition_y > 0 ? 32 : -32 );
		}
	}
}