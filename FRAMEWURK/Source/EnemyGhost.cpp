#include "EnemyGhost.h"

EnemyGhost::EnemyGhost(void)
{
	Enemy::setState(STATE_IDLE);
}

EnemyGhost::~EnemyGhost(void)
{
}

void EnemyGhost::Update(double dt, World* currentWorld, int currentRoom, ModelHandler * theModel)
{
}

void EnemyGhost::Move(double dt, ModelHandler * theModel, std::vector<std::vector<int>> collisionMap)
{
}

void EnemyGhost::setState(ENEMY_STATE state)
{
	Enemy::setState(state);
}

ENEMY_STATE EnemyGhost::getState()
{
	return Enemy::getState();
}

EnemyGhost::CURRENT_STATE &EnemyGhost::getAnimState()
{
	return this->m_animState;
}