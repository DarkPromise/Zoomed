#ifndef ENEMY_FATHER_H
#define ENEMY_FATHER_H

#include "Enemy.h"
#include "EnemyFriend.h"

class EnemyFather : public Enemy
{

public:

	enum ENEMYFATHER_STATE
	{
		STATE_WALK_UP,
		STATE_WALK_DOWN,
		STATE_WALK_LEFT,
		STATE_WALK_RIGHT,
		STATE_IDLE_UP,
		STATE_IDLE_DOWN,
		STATE_IDLE_LEFT,
		STATE_IDLE_RIGHT,
	};

	EnemyFather(void);
	~EnemyFather(void);

	void Update(ModelHandler* theModel, int noiseLevel, double dt);

	void onHit(Player* player, EnemyFriend* player2);

	void ReturnToSpawn();

	void Move();

	ENEMYFATHER_STATE state;
};


#endif