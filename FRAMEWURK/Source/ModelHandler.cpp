#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	std::cout << "Model Handler Initialized" << std::endl;
}

ModelHandler::~ModelHandler(void)
{
}

void ModelHandler::Init() //Anything that moves in the game
{
	player = new Player("Josh");
	player->setPosition(Vector3(0,0,0));

	camera.Init(Vector3(0,0,10),Vector3(0,0,0),Vector3(0,1,0));

	m_status = STATE_MENU;
}

void ModelHandler::Update(const double dt)
{
	camera.Update(dt);
	player->update(dt);
}

Camera ModelHandler::getCamera()
{
	return this->camera;
}

Game ModelHandler::getEnvironment()
{
	return this->theEnvironment;
}

Player * ModelHandler::getPlayer()
{
	return this->player;
}
