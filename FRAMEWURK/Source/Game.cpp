#include "Game.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadHmap.h"
#include <sstream>

Game::Game()
{
	//Environment Init
	std::cout << "Environment Created" << std::endl;

	m_gravity = 14.f;
}

Game::~Game()
{
}

void Game::Init()
{

}

float Game::getGravity()
{
	return m_gravity;
}

void Game::Update(double dt)
{

}

void Game::addObject(GameObject* object)
{
	m_objectList.push_back(object); //Should be Octree / Quadtree
}

void Game::Exit()
{
	
}
