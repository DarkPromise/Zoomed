#ifndef ENEMY_FRIEND_H
#define ENEMY_FRIEND_H

#include "Enemy.h"

class EnemyFriend : public Enemy
{
public:
	
	enum ENEMYFRIEND_STATE
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

	EnemyFriend(void);
	~EnemyFriend(void);

	void Update(ModelHandler* theModel, double dt);

	void onHit(Player* player);

	void Move();

	bool stand_activated;

	ENEMYFRIEND_STATE state;

	bool alive;
};


#endif