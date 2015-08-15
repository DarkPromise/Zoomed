#ifndef PLAYER_H
#define PLAYER_H

#include "AxisAlignedBoundingBox.h"
#include "Game.h" //Environment
#include <string>
#include "Map.h"

#define PLAYERNAME_SIZE 20;
#define PLAYER_JUMP_HEIGHT 7.f;
#define PLAYER_WALK_SPEED 3.f;
#define PLAYER_RUN_SPEED 5.f;
#define PLAYER_CLIMB_SPEED 6.f;

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
	
	virtual void move(double dt, Game Environment);
	virtual void update(double dt);

	Vector3 &getSpeed()
	{
		return m_playerSpeed;
	}

	void setSpeed(Vector3 speed)
	{
		m_playerSpeed = speed;
	}

	void accelerateHorizontal(Vector3 target_speed, float max_speed);
	void accelerateVertical(Vector3 target_speed, float max_speed);

	Vector3 &getPosition()
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

	float &getCurrMp()
	{
		return this->m_currMp;
	}

	float &getMaxMp()
	{
		return this->m_maxMp;
	}

	bool on_ground;
	bool in_liquid;
	bool is_climbing;
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

protected:
	std::string m_name;
	Vector3 m_playerSpeed;
	Vector3 m_playerPos;
	Vector3 m_playerDirection;
	BoundingBox m_boundingbox;

	float m_currMp;
	float m_maxMp;

	//Scrolling
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
};

#endif