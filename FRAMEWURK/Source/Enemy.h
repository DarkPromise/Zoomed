#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>

class Player;
class World;
class ModelHandler;

enum ENEMY_STATE
{
	STATE_IDLE,
	STATE_PATROL,
	STATE_STUNNED,
	STATE_ATTACKING,
	STATE_DEAD,
};

enum ENEMY_TYPES
{
	TYPE_ENEMYMELEE,
	TYPE_ENEMYFRIEND,
	TYPE_ENEMYFATHER,
};

class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

	virtual void Update(Player* player, World* currentWorld, double dt);

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

	float GetSpawn_x(void);

	float GetSpawn_y(void);

	float CalculateDistance();

	float CalculateDistance_x();

	float CalculateDistance_y();

	float CalculateDistance(float x, float y);

	float CalculateDistance_x(float x2);

	float CalculateDistance_y(float y2);

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

	ENEMY_TYPES type;
	
	void setState(ENEMY_STATE state)
	{
		this->m_currState = state;
	}

	ENEMY_STATE getState()
	{
		return this->m_currState;
	}
private:
	ENEMY_STATE m_currState;

	// ENEMY's information
	float theEnemyPosition_x;
	float theEnemyPosition_y;

	float spawnPoint_x;
	float spawnPoint_y;

	/*bool enemyAnimationInvert;
	int enemyAnimationCounter;*/

	// The Destination is the position of the Hero
	float theDestination_x;
	float theDestination_y;

	double EnemyDelay;
};

#endif