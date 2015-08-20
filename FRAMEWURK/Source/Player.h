#ifndef PLAYER_H
#define PLAYER_H

#include "AxisAlignedBoundingBox.h"
#include "Game.h" //Environment
#include <string>
#include "World.h"
#include "Vector3.h"
#include "Inventory.h"

#define PLAYERNAME_SIZE 20;
#define PLAYER_JUMP_HEIGHT 7.f;
#define PLAYER_WALK_SPEED 3.f;
#define PLAYER_RUN_SPEED 5.f;
#define PLAYER_CLIMB_SPEED 6.f;
#define PLAYER_INVENTORY_SIZE 2;          // 0 for Consumable, 1 for Equipment

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
	Player(std::string name);
	~Player();
	
	virtual void move(double dt, std::vector<std::vector<int>> collisionMap);
	virtual void update(double dt, World* currentWorld, int currentRoom);

	Vector3 getSpeed()
	{
		return m_playerSpeed;
	}

	void setSpeed(Vector3 speed)
	{
		m_playerSpeed = speed;
	}

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

	//Inventory inventory;

	PlayerControls controls;
	PlayerControls getPlayerControl()
	{
		return controls;
	}

	unsigned keyPressed;

	int GetMapOffset_x(void);
	int GetMapOffset_y(void);
	int GetMapFineOffset_x(void);
	int GetMapFineOffset_y(void);
	void ConstraintPlayer(const int left, const int right, const int top, const int bottom, float time);

	Inventory getInventory();

protected:
	std::string m_name;
	Vector3 m_playerSpeed;
	Vector3 m_playerPos;
	Vector3 m_playerDirection;
	BoundingBox m_boundingbox;

	Inventory m_playerInventory;

	float m_currFear;
	float m_maxFear;

	//Scrolling
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
};

#endif