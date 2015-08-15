#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "ModelHandler.h" //Model
#include "ViewHandler.h"  //View
#include "ControlHandler.h" //Controller

class GameApplication
{
public:
	ModelHandler * theModel;
	ViewHandler * theView;
	ControlHandler * theController;

	GameApplication();
	virtual ~GameApplication();

	virtual void Start();
};

#endif