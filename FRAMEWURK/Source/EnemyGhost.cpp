#include "EnemyGhost.h"
#include "ModelHandler.h"

EnemyGhost::EnemyGhost(void) : movementDelay(0.0)
	, active(false)
	, blinkDelay(0.0)
	, blink(false)
	, canUp(1)
	, canDown(2)
	, canLeft(3)
	, canRight(4)
	, nothing(0)
{
	Enemy::setState(STATE_IDLE);
}

EnemyGhost::~EnemyGhost(void)
{
}

void EnemyGhost::Update(double dt, World* currentWorld, int currentRoom, ModelHandler * theModel)
{
	Enemy::Update(theModel->getPlayer(),currentWorld,dt);
	this->movementDelay += dt;
	this->Move(dt,theModel,theModel->m_worldList[theModel->currentWorld]->collisionData);
	if(active)
	{
		blinkDelay += dt;
	}
}

void EnemyGhost::Move(double dt, ModelHandler * theModel, std::vector<std::vector<int>> collisionMap)
{
	int yCollision = Math::Max(0, (int)((abs)(Enemy::GetPos_y())/32)+25);
	int xCollision = (int)(Enemy::GetPos_x()/32);
	int playerY = Math::Max(0, (int)((abs)(theModel->getPlayer()->getPosition().y)/32)+25);
	int playerX = (int)(theModel->getPlayer()->getPosition().x/32);

	moveList.clear();
	if(collisionMap[yCollision-1][xCollision] < 100)
	{
		moveList.push_back(canUp);
	}
	if(collisionMap[yCollision+1][xCollision] < 100)
	{
		moveList.push_back(canDown);
	}
	if(collisionMap[yCollision][xCollision-1] < 100)
	{
		moveList.push_back(canLeft);
	}
	if(collisionMap[yCollision][xCollision+1] < 100)
	{
		moveList.push_back(canRight);
	}
	moveList.push_back(nothing);


	if(active) //Triggered when player enters an area
	{
		if( (Enemy::getState() == STATE_IDLE || Enemy::getState() == STATE_PATROL) && Enemy::GetDelay() > 0.6) //New State every 0.6s  //Super Fake AI 
		{
			Enemy::SetDelay(0.0);
			int moveWhere = Math::RandIntMinMax(0,moveList.size());

			switch(moveList[moveWhere])
			{
			case 0:
				{
					//do nothing
					Enemy::SetDelay(0.6);
				}
				break;
			case 1:
				{
					this->getAnimState() = STATE_WALKING_UP;
					if(collisionMap[yCollision-1][xCollision] < 100 && (this->movementDelay > 0.06))
					{
						Enemy::MoveUp();
						movementDelay = 0.0;
					}
				}
				break;
			case 2:
				{
					this->getAnimState() = STATE_WALKING_DOWN;
					if(collisionMap[yCollision+1][xCollision] < 100 && (this->movementDelay > 0.06))
					{
						Enemy::MoveDown();
						movementDelay = 0.0;
					}
				}
				break;
			case 3:
				{
					this->getAnimState() = STATE_WALKING_LEFT;
					if(collisionMap[yCollision][xCollision-1] < 100 && (this->movementDelay > 0.06))
					{
						Enemy::MoveLeft();
						movementDelay = 0.0;
					}
				}
				break;
			case 4:
				{
					this->getAnimState() = STATE_WALKING_RIGHT;
					if(collisionMap[yCollision][xCollision+1] < 100 && (this->movementDelay > 0.06))
					{
						Enemy::MoveRight();
						movementDelay = 0.0;
					}
				}
				break;
			}
		}

		if(blinkDelay > 1.0)
		{
			if(blink == false)
			{
				blink = true;
				theModel->m_objectList[OBJ_GHOST]->isVisible = false;
			}
			else if(blink)
			{
				blink = false;
				theModel->m_objectList[OBJ_GHOST]->isVisible = true;
				if(abs(yCollision - playerY) + abs(xCollision - playerX) <= 7) //If the player is within 7 tiles, increase fear
				{
					theModel->getPlayer()->getCurrFear() += 8.f;
				}
			}
			blinkDelay = 0.0;
		}
	}
}

void EnemyGhost::setState(ENEMY_STATE state)
{
	Enemy::setState(state);
}

ENEMY_STATE EnemyGhost::getState()
{
	return Enemy::getState();
}

EnemyGhost::CURRENT_STATE &EnemyGhost::getAnimState()
{
	return this->m_animState;
}