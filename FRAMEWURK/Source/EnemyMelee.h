#ifndef ENEMY_MELEE_H
#define ENEMY_MELEE_H

#include "Enemy.h"

class EnemyMelee : public Enemy
{

public:
	EnemyMelee(void);
	~EnemyMelee(void);

	void Update(Player* player, World* currentWorld, double dt);

	void onHit(Player* player);

	void Move();
};


#endif