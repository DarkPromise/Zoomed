#include "EnemyFriend.h"
#include "Player.h"

EnemyFriend::EnemyFriend(void)
{
	AccumulatedTime = 0.0;
	this->SetDelay(0);
}

EnemyFriend::~EnemyFriend(void)
{

}

void EnemyFriend::Update(Player* player, double dt)
{
	AccumulatedTime += dt;

	//std::cout << abs(this->GetPos_y()-player->getPosition().y) << std::endl;

	//SetDestination(player->getPosition().x, player->getPosition().y);

	if (player->getPlayerControl().up && AccumulatedTime > this->GetDelay() && !(abs(this->GetPos_x() == player->getPosition().x) && (this->GetPos_y()+32 == player->getPosition().y)) && colData[abs(GetPos_y()/32) + 24][GetPos_x()/32] < 100 && (abs(GetPos_y()/32)-2) > 0)
	{
		AccumulatedTime = 0;
		MoveUp();
	}
	else if (player->getPlayerControl().down && AccumulatedTime > player->getMovementDelay() && !(abs(this->GetPos_x() == player->getPosition().x) && (this->GetPos_y()-32 == player->getPosition().y)) && colData[Math::Min(abs(GetPos_y()/32) + 26, (int)(colData.size()-1))][GetPos_x()/32] < 100 && (abs(GetPos_y()/32)+26) < colData.size())
	{
		AccumulatedTime = 0;
		MoveDown();
	}
	else if (player->getPlayerControl().left && AccumulatedTime > this->GetDelay() && !(abs(this->GetPos_x()+32 == player->getPosition().x) && (this->GetPos_y() == player->getPosition().y)) && colData[abs(GetPos_y()/32) + 25][(GetPos_x()/32) - 1] < 100)
	{
		AccumulatedTime = 0;
		MoveLeft();
	}
	else if (player->getPlayerControl().right && AccumulatedTime > this->GetDelay() && !(abs(this->GetPos_x()-32 == player->getPosition().x) && (this->GetPos_y() == player->getPosition().y)) && colData[abs(GetPos_y()/32) + 25][(GetPos_x()/32) + 1] < 100)
	{
		AccumulatedTime = 0;
		MoveRight();
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