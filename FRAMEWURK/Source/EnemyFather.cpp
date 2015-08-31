#include "EnemyFather.h"
#include "Player.h"
#include "World.h"
#include "ModelHandler.h"

EnemyFather::EnemyFather(void)
{
	AccumulatedTime = 0.0;
}

EnemyFather::~EnemyFather(void)
{

}

void EnemyFather::Update(ModelHandler* theModel, int noiseLevel, double dt)
{
	AccumulatedTime += dt; 

	SetDestination(theModel->getPlayer()->getPosition().x, theModel->getPlayer()->getPosition().y);
	if (CalculateDistance() >= CalculateDistance(theModel->getFriend()->GetPos_x(), theModel->getFriend()->GetPos_x()))
	{
		SetDestination(theModel->getFriend()->GetPos_x(), theModel->getFriend()->GetPos_x());
	}

	if (noiseLevel > 100)
	{
		Move();

		onHit(theModel->getPlayer(), theModel->getFriend());
	}
	else
	{
		ReturnToSpawn();
	}
}

void EnemyFather::ReturnToSpawn()
{
	this->SetPos(this->GetSpawn_x(), this->GetSpawn_y());
	//if(AccumulatedTime > GetDelay())
	//{
	//	this->AccumulatedTime = 0.0;

	//	Right = false;

	//	Left = false;

	//	Up = false;

	//	Down = false;


	//	if(GetSpawn_x() - GetPos_x() > 0 && colData[abs(static_cast<int>(GetPos_y())/32) + 25][static_cast<int>(GetPos_x())/32 + 1] < 100)
	//		Right = true;

	//	if(GetSpawn_x() - GetPos_x() < 0 && colData[abs(static_cast<int>(GetPos_y()/32)) + 25][static_cast<int>(GetPos_x()/32) - 1] < 100)
	//		Left = true;

	//	if (GetSpawn_y() - GetPos_y() < 0 && colData[abs(static_cast<int>(GetPos_y()/32)) + 26][static_cast<int>(GetPos_x()/32)] < 100)
	//		Down = true;

	//	if(GetSpawn_y() - GetPos_y() > 0 && colData[abs(static_cast<int>(GetPos_y()/32)) + 24][static_cast<int>(GetPos_x()/32)] < 100)
	//		Up = true;


	//	if(CalculateDistance_x(GetSpawn_x()) == 32 && CalculateDistance_y(GetSpawn_y()) == 0)
	//	{
	//		Right = false;
	//		Left = false;
	//	}
	//	else if(CalculateDistance_x(GetSpawn_x()) == 0 && CalculateDistance_y(GetSpawn_y()) == 32)
	//	{
	//		Up = false;
	//		Down = false;
	//	}

	//	if(GetSpawn_x() - GetPos_x() > 0)
	//	{
	//		if(Right != true && Up != true && Down != true)
	//		{
	//			/*if(colData[abs(GetPos_y()/32) + 25][GetPos_x()/32 - 1] < 100)
	//			{
	//				MoveLeft();
	//			}*/

	//		}
	//		else if(Right == true && Up != true && Down != true)
	//		{
	//			this->state = EnemyFather::STATE_WALK_RIGHT;
	//			MoveRight();
	//		}
	//		else if(Up == true || Down == true)
	//		{
	//			if(Right == true)
	//			{
	//				if(CalculateDistance_x(GetSpawn_x()) > CalculateDistance_y(GetSpawn_y()))
	//				{
	//					this->state = EnemyFather::STATE_WALK_RIGHT;
	//					MoveRight();
	//				}
	//				else
	//				{
	//					if(Up == true)
	//					{
	//						this->state = EnemyFather::STATE_WALK_UP;
	//						MoveUp();
	//					}
	//					else if(Down == true)
	//					{
	//						this->state = EnemyFather::STATE_WALK_DOWN;
	//						MoveDown();
	//					}
	//				}
	//			}
	//			else
	//			{
	//				if(Up == true)
	//				{
	//					this->state = EnemyFather::STATE_WALK_UP;
	//					MoveUp();
	//				}
	//				else if(Down == true)
	//				{
	//					this->state = EnemyFather::STATE_WALK_DOWN;
	//					MoveDown();
	//				}
	//			}
	//		}
	//	}
	//	else if(GetSpawn_x() - GetPos_x() < 0)
	//	{
	//		if(Left != true && Up != true && Down != true)
	//		{
	//			/*if(colData[abs(GetPos_y()/32) + 25][GetPos_x()/32 + 1] < 100)
	//				MoveRight();*/

	//		}
	//		else if(Left == true && Up != true && Down != true)
	//		{
	//			this->state = EnemyFather::STATE_WALK_LEFT;
	//			MoveLeft();
	//		}
	//		else if(Up == true || Down == true)
	//		{
	//			if(Left == true)
	//			{
	//				if(CalculateDistance_x(GetSpawn_x()) > CalculateDistance_y(GetSpawn_y()))
	//				{
	//					this->state = EnemyFather::STATE_WALK_LEFT;
	//					MoveLeft();
	//				}
	//				else
	//				{
	//					if(Up == true)
	//					{
	//						this->state = EnemyFather::STATE_WALK_UP;
	//						MoveUp();
	//					}
	//					else if(Down == true)
	//					{
	//						this->state = EnemyFather::STATE_WALK_DOWN;
	//						MoveDown();
	//					}
	//				}
	//			}
	//			else
	//			{
	//				if(Up == true)
	//				{
	//					this->state = EnemyFather::STATE_WALK_UP;
	//					MoveUp();
	//				}
	//				else if(Down == true)
	//				{
	//					this->state = EnemyFather::STATE_WALK_DOWN;
	//					MoveDown();
	//				}
	//			}
	//		}
	//	}
	//	else if(GetSpawn_x() - GetPos_x() == 0)
	//	{
	//		if(Up == true)
	//		{
	//			this->state = EnemyFather::STATE_WALK_UP;
	//			MoveUp();
	//		}
	//		else if(Down == true)
	//		{
	//			this->state = EnemyFather::STATE_WALK_DOWN;
	//			MoveDown();
	//		}
	//	}
	//}
}

void EnemyFather::onHit(Player* player, EnemyFriend* player2)
{
	if(CalculateDistance_x() == 32 && CalculateDistance_y() == 0)
	{
		if(player->getImmunityTimer() < 0.0)
		{
			if(player->getCurrFear() < 100.f)
			{
				if(player->getCurrFear() + 10.f > 100.f)
				{
					player->getCurrFear() = 100.f;
				}
				else
				{
					player->getCurrFear() += 10;
				}
				player->setImmunityTimer(1.0);
			}
		}
	}
	else if(CalculateDistance_x() == 0 && CalculateDistance_y() == 32)
	{
		if(player->getImmunityTimer() < 0.0)
		{
			if(player->getCurrFear() < 100.f)
			{
				if(player->getCurrFear() + 10.f > 100.f)
				{
					player->getCurrFear() = 100.f;
				}
				else
				{
					player->getCurrFear() += 10;
				}
				player->setImmunityTimer(1.0);
			}
		}
	}

	if(CalculateDistance_x(player2->GetPos_x()) == 32 && CalculateDistance_y(player2->GetPos_y()) == 0)
	{
		
	}
	else if(CalculateDistance_x(player2->GetPos_x()) == 0 && CalculateDistance_y(player2->GetPos_y()) == 32)
	{
		
	}
}

void EnemyFather::Move()
{
	//std::cout << GetPos_x() << "	 "<< GetPos_y() << std::endl;
	//std::cout << "Father Delay: " << GetDelay() << " , A Time: " << this->AccumulatedTime << std::endl;
	if(AccumulatedTime > GetDelay())
	{
		this->AccumulatedTime = 0.0;

		Right = false;

		Left = false;

		Up = false;

		Down = false;


		if(GetDestination_x() - GetPos_x() > 0 && colData[abs(static_cast<int>(GetPos_y())/32) + 25][static_cast<int>(GetPos_x())/32 + 1] < 100)
			Right = true;

		if(GetDestination_x() - GetPos_x() < 0 && colData[abs(static_cast<int>(GetPos_y()/32)) + 25][static_cast<int>(GetPos_x()/32) - 1] < 100)
			Left = true;

		if (GetDestination_y() - GetPos_y() < 0 && colData[abs(static_cast<int>(GetPos_y()/32)) + 26][static_cast<int>(GetPos_x()/32)] < 100)
			Down = true;

		if(GetDestination_y() - GetPos_y() > 0 && colData[abs(static_cast<int>(GetPos_y()/32)) + 24][static_cast<int>(GetPos_x()/32)] < 100)
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
				this->state = EnemyFather::STATE_WALK_RIGHT;
				MoveRight();
			}
			else if(Up == true || Down == true)
			{
				if(Right == true)
				{
					if(CalculateDistance_x() > CalculateDistance_y())
					{
						this->state = EnemyFather::STATE_WALK_RIGHT;
						MoveRight();
					}
					else
					{
						if(Up == true)
						{
							this->state = EnemyFather::STATE_WALK_UP;
							MoveUp();
						}
						else if(Down == true)
						{
							this->state = EnemyFather::STATE_WALK_DOWN;
							MoveDown();
						}
					}
				}
				else
				{
					if(Up == true)
					{
						this->state = EnemyFather::STATE_WALK_UP;
						MoveUp();
					}
					else if(Down == true)
					{
						this->state = EnemyFather::STATE_WALK_DOWN;
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
				this->state = EnemyFather::STATE_WALK_LEFT;
				MoveLeft();
			}
			else if(Up == true || Down == true)
			{
				if(Left == true)
				{
					if(CalculateDistance_x() > CalculateDistance_y())
					{
						this->state = EnemyFather::STATE_WALK_LEFT;
						MoveLeft();
					}
					else
					{
						if(Up == true)
						{
							this->state = EnemyFather::STATE_WALK_UP;
							MoveUp();
						}
						else if(Down == true)
						{
							this->state = EnemyFather::STATE_WALK_DOWN;
							MoveDown();
						}
					}
				}
				else
				{
					if(Up == true)
					{
						this->state = EnemyFather::STATE_WALK_UP;
						MoveUp();
					}
					else if(Down == true)
					{
						this->state = EnemyFather::STATE_WALK_DOWN;
						MoveDown();
					}
				}
			}
		}
		else if(GetDestination_x() - GetPos_x() == 0)
		{
			if(Up == true)
			{
				this->state = EnemyFather::STATE_WALK_UP;
				MoveUp();
			}
			else if(Down == true)
			{
				this->state = EnemyFather::STATE_WALK_DOWN;
				MoveDown();
			}
		}
	}
}