#ifndef ENEMY_GHOST
#define ENEMY_GHOST

#include "Enemy.h"

class EnemyGhost : public Enemy
{
public:
	enum CURRENT_STATE
	{
		STATE_IDLE_UP = 1,
		STATE_IDLE_DOWN,
		STATE_IDLE_LEFT,
		STATE_IDLE_RIGHT,
		STATE_WALKING_UP,
		STATE_WALKING_DOWN,
		STATE_WALKING_LEFT,
		STATE_WALKING_RIGHT,
	};

	EnemyGhost(void);
	~EnemyGhost(void);

	virtual void Move(double dt, ModelHandler * theModel, std::vector<std::vector<int>> collisionMap);
	virtual void Update(double dt, World* currentWorld, int currentRoom, ModelHandler * theModel);

	void setState(ENEMY_STATE state);
	ENEMY_STATE getState();
	CURRENT_STATE &getAnimState();

	double movementDelay;
	double blinkDelay;
	bool blink;
	bool active;

	std::vector<int> moveList;
private:
	CURRENT_STATE m_animState;
};

#endif