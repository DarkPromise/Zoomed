#include "EnemyDasher.h"
#include "ModelHandler.h"

EnemyDasher::EnemyDasher(void) : movementDelay(0.0)
	, canUp(1)
	, canDown(2)
	, canLeft(3)
	, canRight(4)
	, nothing(0)
	, canDash(true)
{
	Enemy::setState(STATE_IDLE);
}

EnemyDasher::~EnemyDasher(void)
{
}

void EnemyDasher::Update(double dt, World * currentWorld, int currentRoom, ModelHandler * theModel)
{
	Enemy::Update(theModel->getPlayer(),currentWorld,dt);
	this->movementDelay += dt;

	this->Move(dt,theModel,theModel->m_worldList[theModel->currentWorld]->collisionData);
}

void EnemyDasher::Move(double dt, ModelHandler * theModel, std::vector<std::vector<int>> collisionMap)
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

	if(Enemy::getState() != STATE_STUNNED)
	{
		if(!theModel->getPlayer()->getIsHiding())
		{
			if((abs(xCollision - playerX) <= 6) && (abs(yCollision - playerY) == 0))
			{
				Enemy::setState(STATE_ATTACKING);
				canDash = true;
			}
			else if((abs(xCollision - playerX) == 0) && (abs(yCollision - playerY) <= 6))
			{
				Enemy::setState(STATE_ATTACKING);
				canDash = true;
			}
		}
		else
		{
			Enemy::setState(STATE_PATROL);
		}
	}

	if( (Enemy::getState() == STATE_IDLE || Enemy::getState() == STATE_PATROL) && Enemy::GetDelay() > 1.5) //New State every 1.5s  //Super Fake AI 
	{
		Enemy::SetDelay(0.0);
		int moveWhere = Math::RandIntMinMax(0,moveList.size());

		switch(moveList[moveWhere])
		{
		case 0:
			{
				//do nothing
				Enemy::SetDelay(1.5);
			}
			break;
		case 1:
			{
				this->getAnimState() = STATE_WALKING_UP;
				if(collisionMap[yCollision-1][xCollision] < 100 && (this->movementDelay > 0.09))
				{
					Enemy::MoveUp();
					movementDelay = 0.0;
				}
			}
			break;
		case 2:
			{
				this->getAnimState() = STATE_WALKING_DOWN;
				if(collisionMap[yCollision+1][xCollision] < 100 && (this->movementDelay > 0.09))
				{
					Enemy::MoveDown();
					movementDelay = 0.0;
				}
			}
			break;
		case 3:
			{
				this->getAnimState() = STATE_WALKING_LEFT;
				if(collisionMap[yCollision][xCollision-1] < 100 && (this->movementDelay > 0.09))
				{
					Enemy::MoveLeft();
					movementDelay = 0.0;
				}
			}
			break;
		case 4:
			{
				this->getAnimState() = STATE_WALKING_RIGHT;
				if(collisionMap[yCollision][xCollision+1] < 100 && (this->movementDelay > 0.09))
				{
					Enemy::MoveRight();
					movementDelay = 0.0;
				}
			}
			break;
		}
	}
	else if(Enemy::getState() == STATE_ATTACKING && Enemy::getState() != STATE_STUNNED)
	{
		if(!theModel->getPlayer()->getIsHiding())
		{
			//Dash to player
			if((abs(yCollision - playerY) == 0)) //Dash X
			{
				if((collisionMap[yCollision][xCollision-1] < 100) || (collisionMap[yCollision][xCollision+1] < 100)) //Check Walls Left Right
				{
					if(playerX > xCollision)
					{
						int difference = playerX - xCollision;
						for(int i = 0; i < difference; ++i)
						{
							if(collisionMap[yCollision][xCollision+1+i] < 100)
							{
							}
							else
							{
								canDash = false;
							}
						}
						if(canDash)
						{
							this->getAnimState() = STATE_WALKING_RIGHT;
							Enemy::SetPos(Math::Round(Math::SmoothDamp(Enemy::GetPos_x(),theModel->getPlayer()->getPosition().x - 32.f,1280.f,0.01f,1280.f,1.0)),Enemy::GetPos_y());
							if(Enemy::GetPos_x() == theModel->getPlayer()->getPosition().x - 32.f)
							{
								Enemy::setState(STATE_STUNNED);
								if((theModel->getPlayer()->getCurrFear() + 20) > 100.f)
								{
									theModel->getPlayer()->getCurrFear() = 100.f;
								}
								else
								{
									theModel->getPlayer()->getCurrFear() += 20.f;
								}
								Enemy::SetDelay(0.0);
							}
						}
					}
					else
					{
						int difference = xCollision - playerX;
						for(int i = 0; i < difference; ++i)
						{
							if(collisionMap[yCollision][xCollision-1-i] < 100)
							{
							}
							else
							{
								canDash = false;
							}
						}
						if(canDash)
						{
							this->getAnimState() = STATE_WALKING_LEFT;
							Enemy::SetPos(Math::Round(Math::SmoothDamp(Enemy::GetPos_x(),theModel->getPlayer()->getPosition().x + 32.f,1280.f,0.01f,1280.f,1.0)),Enemy::GetPos_y());
							if(Enemy::GetPos_x() == theModel->getPlayer()->getPosition().x + 32.f)
							{
								Enemy::setState(STATE_STUNNED);
								if((theModel->getPlayer()->getCurrFear() + 20) > 100.f)
								{
									theModel->getPlayer()->getCurrFear() = 100.f;
								}
								else
								{
									theModel->getPlayer()->getCurrFear() += 20.f;
								}
								Enemy::SetDelay(0.0);
							}
						}
					}
				}
				else
				{
					Enemy::setState(STATE_PATROL);
					Enemy::SetDelay(0.0);
				}
			}
			else if((abs(xCollision - playerX) == 0)) //Dash Y
			{
				if((collisionMap[yCollision+1][xCollision] < 100) || (collisionMap[yCollision-1][xCollision] < 100))
				{
					if(playerY > yCollision)
					{
						int difference = playerY - yCollision;
						for(int i = 0; i < difference; ++i)
						{
							if(collisionMap[yCollision+1+i][xCollision] < 100)
							{
							}
							else
							{
								canDash = false;
							}
						}
						if(canDash)
						{
							this->getAnimState() = STATE_WALKING_DOWN;
							Enemy::SetPos(Enemy::GetPos_x(),Math::Round(Math::SmoothDamp(Enemy::GetPos_y(),theModel->getPlayer()->getPosition().y + 32.f,1280.f,0.01f,1280.f,1.0)));
							if(Enemy::GetPos_y() == theModel->getPlayer()->getPosition().y + 32.f)
							{
								Enemy::setState(STATE_STUNNED);
								if((theModel->getPlayer()->getCurrFear() + 20) > 100.f)
								{
									theModel->getPlayer()->getCurrFear() = 100.f;
								}
								else
								{
									theModel->getPlayer()->getCurrFear() += 20.f;
								}
								Enemy::SetDelay(0.0);
							}
						}
					}
					else
					{
						int difference = yCollision - playerY;
						for(int i = 0; i < difference; ++i)
						{
							if(collisionMap[yCollision-1-i][xCollision] < 100)
							{
							}
							else
							{
								canDash = false;
							}
						}
						if(canDash)
						{
							this->getAnimState() = STATE_WALKING_UP;
							Enemy::SetPos(Enemy::GetPos_x(),Math::Round(Math::SmoothDamp(Enemy::GetPos_y(),theModel->getPlayer()->getPosition().y - 32.f,1280.f,0.01f,1280.f,1.0)));
							if(Enemy::GetPos_y() == theModel->getPlayer()->getPosition().y - 32.f)
							{
								Enemy::setState(STATE_STUNNED);
								if((theModel->getPlayer()->getCurrFear() + 20) > 100.f)
								{
									theModel->getPlayer()->getCurrFear() = 100.f;
								}
								else
								{
									theModel->getPlayer()->getCurrFear() += 20.f;
								}
								Enemy::SetDelay(0.0);
							}
						}
					}
				}
			}
			else
			{
				Enemy::setState(STATE_PATROL);
				Enemy::SetDelay(0.0);
			}
		}
	}
	else if(Enemy::getState() == STATE_STUNNED)
	{
		if(Enemy::GetDelay() > 2.0) //Stunned for 2 seconds
		{
			Enemy::setState(STATE_PATROL);
		}
	}


}

void EnemyDasher::setState(ENEMY_STATE state)
{
	Enemy::setState(state);
}

ENEMY_STATE EnemyDasher::getState()
{
	return Enemy::getState();
}

EnemyDasher::CURRENT_STATE &EnemyDasher::getAnimState()
{
	return this->m_animState;
}