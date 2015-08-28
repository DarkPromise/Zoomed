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


	
	int CalculateDistance();

	int CalculateDistance_x();

	int CalculateDistance_y();

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
	int theEnemyPosition_x;
	int theEnemyPosition_y;

	/*bool enemyAnimationInvert;
	int enemyAnimationCounter;*/

	// The Destination is the position of the Hero
	int theDestination_x;
	int theDestination_y;

	double EnemyDelay;

	

};

#endif