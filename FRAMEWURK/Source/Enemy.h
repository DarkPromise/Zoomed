#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>

class Player;

class Enemy
{
public:
	Enemy(void);
	~Enemy(void);


	virtual void Update(Player* player, double dt);

	// Set position x of the player
	void SetPos(float pos_x, float pos_y);
	// Set the destination of this enemy
	void SetDestination(float pos_x, float pos_y);

	// Get position x of the player
	float GetPos_x(void);
	// Get position y of the player
	float GetPos_y(void);
	// Set the destination of this enemy
	float GetDestination_x(void);
	// Set the destination of this enemy
	float GetDestination_y(void);


	
	float CalculateDistance();

	float CalculateDistance_x();

	float CalculateDistance_y();

	void MoveRight();

	void MoveLeft();

	void MoveUp();

	void MoveDown();

	void SetDelay(double t);

	double GetDelay();

	bool Right;

	bool Left;

	bool Up;

	bool Down;

	void SetData(std::vector<std::vector<int> > Data);

	std::vector<std::vector<int> > colData;	// 2D vector to store collision values

	double AccumulatedTime;

private:
	// ENEMY's information
	float theEnemyPosition_x;
	float theEnemyPosition_y;

	/*bool enemyAnimationInvert;
	int enemyAnimationCounter;*/

	// The Destination is the position of the Hero
	float theDestination_x;
	float theDestination_y;

	double EnemyDelay;

	

};

#endif