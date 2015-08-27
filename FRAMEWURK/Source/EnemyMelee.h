#ifndef ENEMY_MELEE_H
#define ENEMY_MELEE_H

#include "Enemy.h"

class EnemyMelee : public Enemy
{

public:
	EnemyMelee(void);
	~EnemyMelee(void);

	void Update(int D_x, int D_y,double dt);

	void Move();
};


#endif