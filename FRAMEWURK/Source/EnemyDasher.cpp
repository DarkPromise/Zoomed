#include "EnemyDasher.h"

EnemyDasher::EnemyDasher(void)
{
	Enemy::setState(STATE_IDLE);
}

EnemyDasher::~EnemyDasher(void)
{
}

void EnemyDasher::Update(double dt, World* currentWorld, int currentRoom, ModelHandler * theModel)
{
	std::cout << "Test" << std::endl;
}

void EnemyDasher::Move(double dt, ModelHandler * theModel, std::vector<std::vector<int>> collisionMap)
{
}

void EnemyDasher::setState(ENEMY_STATE state)
{
	Enemy::setState(state);
}

ENEMY_STATE EnemyDasher::getState()
{
	return Enemy::getState();
}

EnemyDasher::CURRENT_STATE &EnemyDasher::getAnimState()
{
	return this->m_animState;
}