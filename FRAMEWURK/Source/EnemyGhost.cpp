#include "EnemyGhost.h"
#include "ModelHandler.h"

EnemyGhost::EnemyGhost(void) : movementDelay(0.0)
	, active(false)
	, blinkDelay(0.0)
	, blink(false)
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

	if(active) //Triggered when player enters an area
	{
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
				std::cout << abs(yCollision - playerY) + abs(xCollision - playerX) << std::endl;
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