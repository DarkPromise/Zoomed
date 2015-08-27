#include "GameApplication.h"

GameApplication::GameApplication() : theModel(NULL), theView(NULL), theController(NULL) {}

GameApplication::~GameApplication()
{
	delete theModel;
	theModel = NULL;

	delete theView;
	theView = NULL;

	delete theController;
	theController = NULL;
}

void GameApplication::Start()
{
	theModel = new ModelHandler();
	theView = new ViewHandler(theModel);
	theController = new ControlHandler(theModel,theView);

	theController->RunGameLoop();
}

