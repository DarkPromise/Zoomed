#include "EnemyMelee.h"
#include "Player.h"

EnemyMelee::EnemyMelee(void)
{
	AccumulatedTime = 0.0;
	SetDelay(0.5);
}

EnemyMelee::~EnemyMelee(void)
{

}

void EnemyMelee::Update(Player* player, double dt)
{

	AccumulatedTime += dt; 


	 	
	SetDestination(player->getPosition().x, player->getPosition().y);

	 Move();

	 onHit(player);

}

void EnemyMelee::onHit(Player* player)
{
	if(CalculateDistance_x() == 32 && CalculateDistance_y() == 0)
	{
		if(player->getCurrFear() < 100)
		{
			player->getCurrFear() += 10;
		}
	}
	else if(CalculateDistance_x() == 0 && CalculateDistance_y() == 32)
		{
		if(player->getCurrFear() < 100)
		{
			player->getCurrFear() += 10;
		}
	}
}

void EnemyMelee::Move()
{

	//std::cout << GetPos_x() << "	 "<< GetPos_y() << std::endl;

	if(AccumulatedTime > GetDelay())
	{
		AccumulatedTime = 0.0;

		Right = false;

		Left = false;

		Up = false;

		Down = false;


		if(GetDestination_x() - GetPos_x() > 0 && colData[abs(GetPos_y()/32) + 25][GetPos_x()/32 + 1] < 100)
			Right = true;

		if(GetDestination_x() - GetPos_x() < 0 && colData[abs(GetPos_y()/32) + 25][GetPos_x()/32 - 1] < 100)
			Left = true;

		if (GetDestination_y() - GetPos_y() < 0 && colData[abs(GetPos_y()/32) + 26][GetPos_x()/32] < 100)
			Down = true;

		if(GetDestination_y() - GetPos_y() > 0 && colData[abs(GetPos_y()/32) + 24][GetPos_x()/32] < 100)
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