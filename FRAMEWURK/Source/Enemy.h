#pragma once

#include <iostream>
#include <vector>


class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

	

	
	// Set position x of the player
	void SetPos(int pos_x, int pos_y);
	// Set the destination of this enemy
	void SetDestination(const int pos_x, const int pos_y);

	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);
	// Set the destination of this enemy
	int GetDestination_x(void);
	// Set the destination of this enemy
	int GetDestination_y(void);



	//// Set Animation Invert status of the player
	//void SetAnimationInvert(bool ENEMYAnimationInvert);
	//// Get Animation Invert status of the player
	//bool GetAnimationInvert(void);
	//// Set Animation Counter of the player
	//void SetAnimationCounter(int ENEMYAnimationCounter);
	//// Get Animation Counter of the player
	//int GetAnimationCounter(void);

	void KILL(int D_x, int D_y);

	int CalculateDistance();

	int CalculateDistance_x();

	int CalculateDistance_y();

	void MoveRight();

	void MoveLeft();

	void MoveUp();

	void MoveDown();

	void Move();

	bool Right;

	bool Left;

	bool Up;

	bool Down;

	void SetData(std::vector<std::vector<int> > Data);

	std::vector<std::vector<int> > colData;	// 2D vector to store collision values

private:
	// ENEMY's information
	int theEnemyPosition_x;
	int theEnemyPosition_y;

	/*bool enemyAnimationInvert;
	int enemyAnimationCounter;*/

	// The Destination is the position of the Hero
	int theDestination_x;
	int theDestination_y;

};
