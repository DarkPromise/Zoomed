#include "EnemyFriend.h"
#include "Player.h"
#include "World.h"
#include "ModelHandler.h"

EnemyFriend::EnemyFriend(void)
{
	AccumulatedTime = 0.0;
	this->SetDelay(0);
	this->state = STATE_IDLE_RIGHT;
	this->alive = true;
}

EnemyFriend::~EnemyFriend(void)
{

}

void EnemyFriend::Update(ModelHandler * theModel, double dt)
{
	AccumulatedTime += dt;

	int yColiision = Math::Max(0, (int)((abs)(this->GetPos_y())/32)+25);
	int xColiision = (int)(GetPos_x()/32);

	//std::cout << abs(this->GetPos_y()-player->getPosition().y) << std::endl;

	//SetDestination(player->getPosition().x, player->getPosition().y);

	if (!stand_activated)
	{
		switch(colData[yColiision][xColiision])
		{
			case COLLISION_BLUE_TILEYELLOWBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < colData.size(); i++)
				{
					for (unsigned j = 0; j < colData[i].size(); j++)
					{
						if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEYELLOWBLOCK_OFF)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEYELLOWBLOCK;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 100;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
						else if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEYELLOWBLOCK)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEYELLOWBLOCK_OFF;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 0;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
					}
				}
				std::cout << "On yellow button" << std::endl;
			}
			break;
			case COLLISION_BLUE_TILEGRAYBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < colData.size(); i++)
				{
					for (unsigned j = 0; j < colData[i].size(); j++)
					{
						if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEGRAYBLOCK_OFF)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEGRAYBLOCK;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 100;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
						else if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEGRAYBLOCK)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEGRAYBLOCK_OFF;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 0;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
					}
				}
				std::cout << "On gay button" << std::endl;
			}
			break;
			case COLLISION_BLUE_TILEPURPLEBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < colData.size(); i++)
				{
					for (unsigned j = 0; j < colData[i].size(); j++)
					{
						if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEPURPLEBLOCK_OFF)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEPURPLEBLOCK;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 100;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
						else if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEPURPLEBLOCK)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEPURPLEBLOCK_OFF;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 0;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
					}
				}
				std::cout << "On purpur button" << std::endl;
			}
			break;
			case COLLISION_BLUE_TILEREDBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < colData.size(); i++)
				{
					for (unsigned j = 0; j < colData[i].size(); j++)
					{
						if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEREDBLOCK_OFF)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEREDBLOCK;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 100;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
						else if (theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] == BLUE_TILEREDBLOCK)
						{
							theModel->m_worldList[theModel->currentWorld]->sceneryData[i][j] = BLUE_TILEREDBLOCK_OFF;
							theModel->m_worldList[theModel->currentWorld]->collisionData[i][j] = 0;
							theModel->m_worldList[theModel->currentWorld]->UpdateWorld = true;
						}
					}
				}
				std::cout << "On FIREENDINGE button" << std::endl;
			}
			break;
			case COLLISION_BLUE_FINISHTILE:
				{
					stand_activated = true;
					theModel->m_worldList[WORLD_FRIENDS_LEVEL1]->worldClear[1] = true;

					if (theModel->m_worldList[WORLD_FRIENDS_LEVEL1]->worldClear[0] && theModel->m_worldList[WORLD_FRIENDS_LEVEL1]->worldClear[1])
					{
						if ( theModel->currentWorld == WORLD_FRIENDS_FINISH)
						{
							theModel->currentWorld = WORLD_MAINMENU;
						}
						else
						{
							theModel->currentWorld = (WORLD_ID)((int)(theModel->currentWorld)+1) ;
						}

						if (theModel->currentWorld == WORLD_FRIENDS_LEVEL1)
						{
							theModel->getPlayer()->setPosition(Vector3(2784,-160, 0));
						}
						else if (theModel->currentWorld == WORLD_FRIENDS_FINISH)
						{
							theModel->getPlayer()->setPosition(Vector3(800,-1088, 0));
						}
					}
				}
			break;
		}
	}

	if ( abs(theModel->getPlayer()->getPosition().x - this->GetPos_x())/32 > 6 || abs(theModel->getPlayer()->getPosition().y - this->GetPos_y()/32 > 6) )
	{
		theModel->sound->updateNoiseLevel(1);
		//std::cout << "NOISE" << std::endl;
	}

	if (theModel->getPlayer()->getPlayerControl().up && AccumulatedTime > theModel->getPlayer()->getMovementDelay() && !(abs(this->GetPos_x() == (int)(theModel->getPlayer()->getPosition().x)) && (this->GetPos_y()+32 == theModel->getPlayer()->getPosition().y)) && colData[(int)(abs(GetPos_y()/32)) + 24][(int)(GetPos_x()/32)] < 100 && (abs(GetPos_y()/32)-1) > 0)
	{
		this->state = EnemyFriend::STATE_WALK_UP;
		AccumulatedTime = 0;
		MoveUp();
		stand_activated = false;
	}

	if (theModel->getPlayer()->getPlayerControl().down && AccumulatedTime > theModel->getPlayer()->getMovementDelay() && !(abs(this->GetPos_x() == (int)(theModel->getPlayer()->getPosition().x)) && (this->GetPos_y()-32 == theModel->getPlayer()->getPosition().y)) && colData[(int)(abs(GetPos_y()/32)) + 26][(int)(GetPos_x()/32)] < 100 && (abs(GetPos_y()/32)+26) < colData.size()-1)
	{
		this->state = EnemyFriend::STATE_WALK_DOWN;
		AccumulatedTime = 0;
		MoveDown();
		stand_activated = false;
	} 

	if (theModel->getPlayer()->getPlayerControl().left && AccumulatedTime > theModel->getPlayer()->getMovementDelay() && !(abs(this->GetPos_x()-32 == (int)(theModel->getPlayer()->getPosition().x)) && (this->GetPos_y() == theModel->getPlayer()->getPosition().y)) && colData[(int)(abs(GetPos_y()/32)) + 25][(int)((GetPos_x()/32)) - 1] < 100 && (abs(GetPos_x()-32) > 0))
	{
		this->state = EnemyFriend::STATE_WALK_LEFT;
		AccumulatedTime = 0;
		MoveLeft();
		stand_activated = false;
	}

	if (theModel->getPlayer()->getPlayerControl().right && AccumulatedTime > theModel->getPlayer()->getMovementDelay() && !(abs(this->GetPos_x()+32 == (int)(theModel->getPlayer()->getPosition().x)) && (this->GetPos_y() == theModel->getPlayer()->getPosition().y)) && colData[(int)(abs(GetPos_y()/32)) + 25][(int)((GetPos_x()/32)) + 1] < 100 && (abs(GetPos_x()/32)) < colData[0].size()-1)
	{
		this->state = EnemyFriend::STATE_WALK_RIGHT;
		AccumulatedTime = 0;
		MoveRight();
		stand_activated = false;
	}

	if (theModel->getPlayer()->getPlayerControl().use)
	{
		//for (unsigned i = 0; i < colData.size(); i++)
		//{
		//	for (unsigned j = 0; j < colData[i].size(); j++)
		//	{
		//		std::cout << colData[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
	}

	// onHit(player);

}

void EnemyFriend::onHit(Player* player)
{
	//friendly~
}

void EnemyFriend::Move()
{

	//std::cout << GetPos_x() << "	 "<< GetPos_y() << std::endl;

	if(AccumulatedTime > GetDelay())
	{
		AccumulatedTime = 0.0;

		Right = false;

		Left = false;

		Up = false;

		Down = false;

		if(GetDestination_x() - GetPos_x() > 0 && colData[(int)(abs(GetPos_y()/32.f)) + 25][(int)(GetPos_x()/32) + 1] < 100)
			Right = true;

		if(GetDestination_x() - GetPos_x() < 0 && colData[(int)(abs(GetPos_y()/32.f)) + 25][(int)(GetPos_x()/32) - 1] < 100)
			Left = true;

		if (GetDestination_y() - GetPos_y() < 0 && colData[(int)(abs(GetPos_y()/32.f)) + 26][(int)(GetPos_x()/32)] < 100)
			Down = true;

		if(GetDestination_y() - GetPos_y() > 0 && colData[(int)(abs(GetPos_y()/32.f)) + 24][(int)(GetPos_x()/32)] < 100)
			Up = true;


		if(CalculateDistance_x() == 32 && CalculateDistance_y() == 0)
		{
			Right = false;
			Left = false;
		}
		else if(CalculateDistance_x() == 0 && CalculateDistance_y() == 32)
		{
			Up = false;
			Down = false;
		}

		if(GetDestination_x() - GetPos_x() > 0)
		{
			if(Right != true && Up != true && Down != true)
			{
				/*if(colData[abs(GetPos_y()/32) + 25][GetPos_x()/32 - 1] < 100)
				{
					MoveLeft();
				}*/

			}
			else if(Right == true && Up != true && Down != true)
			{
				MoveRight();
			}
			else if(Up == true || Down == true)
			{
				if(Right == true)
				{
					if(CalculateDistance_x() > CalculateDistance_y())
					{
						MoveRight();
					}
					else
					{
						if(Up == true)
						{
							MoveUp();
						}
						else if(Down == true)
						{
							MoveDown();
						}
					}
				}
				else
				{
					if(Up == true)
					{
						MoveUp();
					}
					else if(Down == true)
					{
						MoveDown();
					}
				}
			}
		}
		else if(GetDestination_x() - GetPos_x() < 0)
		{
			if(Left != true && Up != true && Down != true)
			{
				/*if(colData[abs(GetPos_y()/32) + 25][GetPos_x()/32 + 1] < 100)
					MoveRight();*/

			}
			else if(Left == true && Up != true && Down != true)
			{
				MoveLeft();
			}
			else if(Up == true || Down == true)
			{
				if(Left == true)
				{
					if(CalculateDistance_x() > CalculateDistance_y())
					{
						MoveLeft();
					}
					else
					{
						if(Up == true)
						{
							MoveUp();
						}
						else if(Down == true)
						{
							MoveDown();
						}
					}
				}
				else
				{
					if(Up == true)
					{
						MoveUp();
					}
					else if(Down == true)
					{
						MoveDown();
					}
				}
			}
		}
		else if(GetDestination_x() - GetPos_x() == 0)
		{
			if(Up == true)
			{
				MoveUp();
			}
			else if(Down == true)
			{
				MoveDown();
			}
		}
	}
}