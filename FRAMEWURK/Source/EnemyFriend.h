#ifndef ENEMY_FRIEND_H
#define ENEMY_FRIEND_H

#include "Enemy.h"

class EnemyFriend : public Enemy
{

public:
	EnemyFriend(void);
	~EnemyFriend(void);

	void Update(Player* player,double dt);

	void onHit(Player* player);

	void Move();
};


#endif