#include "Player.h"

Player::Player(std::string name)
	: on_ground(true),
	in_liquid(false),
	is_climbing(false),
	is_running(false),
	keyPressed(0),
// Protected Info
	m_maxMp(100),
	m_currMp(m_maxMp),
	m_playerSpeed(0,0,0),
	m_playerPos(0,0,0),
	m_playerDirection(1,0,0),
	m_boundingbox(1.f,1.f,1.f,-1.f,-1.f,-1.f),
	mapOffset_x(0),
	mapOffset_y(0),
	mapFineOffset_x(0),
	mapFineOffset_y(0)
{
	this->m_name = name;
}

Player::~Player() {}

void Player::accelerateHorizontal(Vector3 target_speed, float max_speed)
{
	if(max_speed == 0)
	{
		return;
	}

	Vector3 wanted = target_speed - m_playerSpeed;
	wanted.y = 0;
	float d1 = wanted.Length();
	if(d1 > max_speed)
	{
		d1 = max_speed;
	}

	Vector3 d2 = wanted.Normalize() * d1;

	m_playerSpeed.x += d2.x;
}

void Player::accelerateVertical(Vector3 target_speed, float max_speed)
{
	if(max_speed == 0)
	{
		return;
	}
		
	float wanted = target_speed.y - m_playerSpeed.y;

	if(wanted > max_speed)
	{
		wanted = max_speed;
	}
	else if(wanted < -max_speed)
	{
		wanted = -max_speed;
	}

	m_playerSpeed.y += wanted;
}

void Player::move(double dt,Game theEnvironment)
{
	
}


void Player::update(double dt)
{
	m_playerPos += m_playerSpeed;
}

int Player::GetMapOffset_x(void)
{
	return mapOffset_x;
}

int Player::GetMapOffset_y(void)
{
	return mapOffset_y;
}

int Player::GetMapFineOffset_x(void)
{
	return mapFineOffset_x;
}
int Player::GetMapFineOffset_y(void)
{
	return mapFineOffset_y;
}

void Player::ConstraintPlayer(const int left, const int right, const int top, const int bottom, float time)
{
	
}