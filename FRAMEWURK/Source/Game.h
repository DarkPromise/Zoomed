#ifndef GAME_H
#define GAME_H

//THE GAME ENVIRONMENT

#include "Camera.h"
#include "GameObject.h"
#include "Map.h"

#include <vector>

class Game
{
public:
	Game();
	~Game();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	void addObject(GameObject*);

	std::vector<GameObject*> m_objectList;

	float getGravity();
protected:
	float m_gravity;
};

#endif