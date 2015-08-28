#ifndef PLAYER_H
#define PLAYER_H

#include "AxisAlignedBoundingBox.h"
#include "Game.h" //Environment
#include <string>
#include "World.h"
#include "Vector3.h"
#include "Inventory.h"

#define PLAYERNAME_SIZE 20
#define PLAYER_INVENTORY_SIZE 2          // 0 for Consumable, 1 for Equipment

struct PlayerControls
{
	PlayerControls()
	{
		up = false;
		down = false;
		left = false;
		right = false;
		run = false;
		jump = false;
		use = false;
	}

	PlayerControls(
		bool key_up,
		bool key_down,
		bool key_left,
		bool key_right,
		bool key_jump,
		bool key_run,
		bool key_use
		)
	{
		up = key_up;
		down = key_down;
		left = key_left;
		right = key_right;
		jump = key_jump;
		use = key_use;
	}

	bool up;
	bool down;
	bool left;
	bool right;
	bool jump;
	bool run;
	bool use;
};

class Game;

class Player
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

	Player(std::string name);
	~Player();
	
	virtual void move(double dt, std::vector<std::vector<int>> collisionMap);
	virtual void update(double dt, World* currentWorld, int currentRoom);
	virtual void Interact(double dt, World* currentWorld, std::vector<std::vector<int>> collisionMap);

	Vector3 getPosition()
	{
		return m_playerPos;
	}

	virtual void setPosition(const Vector3 &position)
	{
		m_playerPos = position;
	}

	std::string getName()
	{
		return m_name;
	}

	BoundingBox &getBoundingBox()
	{
		return m_boundingbox;
	}

	void setDirection(Vector3 direction)
	{
		this->m_playerDirection = direction;
	}

	Vector3 getDirection()
	{
		return this->m_playerDirection;
	}

	float &getCurrFear()
	{
		return this->m_currFear;
	}

	float &getMaxFear()
	{
		return this->m_maxFear;
	}

	bool on_ground;
	bool is_running;
	bool stand_activated;

	PlayerControls controls;
	PlayerControls getPlayerControl()
	{
		return controls;
	}

	unsigned keyPressed;

	Inventory &getInventory();
	float getSanity();

	CURRENT_STATE m_animationState;

	void getPassiveEffect(Item * item);
	
	double getImmunityTimer();
	void setImmunityTimer(double time);

	float getVisiblityFactor();
	void setVisibilityFactor(float visibility);
protected:
	std::string m_name;
	double m_movementDelay;
	double m_movementTimer;
	double m_fearCooldown;
	double m_immunityTimer;
	Vector3 m_playerPos;
	Vector3 m_playerDirection;
	BoundingBox m_boundingbox;

	float m_playerSanity;
	float m_visiblityFactor;

	Inventory m_playerInventory;

	float m_currFear;
	float m_maxFear;
};

#endif