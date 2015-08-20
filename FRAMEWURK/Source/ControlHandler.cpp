#include "ControlHandler.h"

ControlHandler::ControlHandler(ModelHandler * theModel, ViewHandler * theView) : theModel(NULL), theView(NULL)
{
	this->theView = theView;
	this->theModel = theModel;
	this->theModel->Init();

	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;

	std::cout << "Controller Initialized" << std::endl;
	std::cout << std::endl;
}

ControlHandler::~ControlHandler(void)
{
}

void ControlHandler::RunGameLoop()
{
	bool LoopTheGame = true;

	if(theView->CreateGLWindow("Main Game",1024,800,16))
	{
		theModel->InitObjects(); //Because OpenGL isnt created yet..
	}
	else
	{
		std::cout << "Failed To Create Framework" << std::endl;
	}

	m_timer.startTimer();

	while(LoopTheGame)
	{
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;

		if (m_dAccumulatedTime_ThreadOne > 0.01) //faster
		{
			//theView->MouseUpdate();
			theView->Update(m_dElapsedTime);

			m_dAccumulatedTime_ThreadOne = 0.0;
		}
		if (m_dAccumulatedTime_ThreadTwo > 0.03)
		{
			//UpdateAI();
			m_dAccumulatedTime_ThreadTwo = 0.0;
		}

		if(ProcessInputs())
		{
			theView->RenderScene();
		}
		else
		{
			LoopTheGame = false;
		}
	}
}

void ControlHandler::MouseUpdate()
{
	//std::cout << "Mouse Coordinates : (" << theView->MouseInfo.x << "," << theView->MouseInfo.y << ")" << std::endl;

	if(theView->IsButtonPressed(0) && !theView->MouseInfo.m_bLeftButtonPressed) //LMB
	{
		//Update View State
		theView->MouseInfo.m_bLeftButtonPressed = true;
		//Get Mouse Click Coords
		//Get Current Screen State
		if(theModel->m_status == STATE_MENU)
		{
			//Check is mouse click is within any GUI bounding box(click options for GUIBUTTON::TYPE type)
		/*	for(unsigned int i = 0; i < theModel->m_buttonList.size(); ++i)
			{
				if((theModel->m_buttonList[i]->getBoundingBox().Min.x <= theView->MouseInfo.x)  && (theView->MouseInfo.x <= theModel->m_buttonList[i]->getBoundingBox().Max.x) &&
					(theModel->m_buttonList[i]->getBoundingBox().Min.y >= theView->MouseInfo.y)  && (theView->MouseInfo.y >= theModel->m_buttonList[i]->getBoundingBox().Max.y))
				{
					
				}
			}*/
			//Do the action(Parse into theView)
		}
		//exit
	}
	else if(!theView->IsButtonPressed(0) && theView->MouseInfo.m_bLeftButtonPressed)
	{
		theView->MouseInfo.m_bLeftButtonPressed = false;
	}

	if(theView->IsButtonPressed(1)) //RMB
	{

	}
}

void ControlHandler::KeyboardUpdate()
{
	static bool toggleFullScreen = false;
	static bool generateRoom = false;

	//if(theView->IsKeyPressed('5') && !toggleFullScreen)
	//{
	//	toggleFullScreen = true;
	//	theView->toggleFullScreen();
	//}
	//else if(!theView->IsKeyPressed('5') && toggleFullScreen)
	//{
	//	toggleFullScreen = false;
	//}

	if(theView->IsKeyPressed('W') || theView->IsKeyPressed(GLFW_KEY_SPACE))
	{
		theModel->getPlayer()->controls.up = true;
	}
	else
	{
		//theModel->getPlayer()->controls.jump = false;
		theModel->getPlayer()->controls.up = false;
	}

	if(theView->IsKeyPressed('A'))
	{
		theModel->getPlayer()->controls.left = true;
	}
	else
	{
		theModel->getPlayer()->controls.left = false;
	}

	if(theView->IsKeyPressed('S'))
	{
		theModel->getPlayer()->controls.down = true;
	}
	else
	{
		theModel->getPlayer()->controls.down = false;
	}
	if(theView->IsKeyPressed('D'))
	{
		theModel->getPlayer()->controls.right = true;
	}
	else
	{
		theModel->getPlayer()->controls.right = false;
	}

	if(theView->IsKeyPressed('R') && !generateRoom)
	{
		generateRoom = true;
		/*theModel->m_worldList[1]->m_roomList[0]->generateRoom();
		theModel->m_worldList[1]->m_roomList[1]->generateRoom();

		theModel->m_objectList[3]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->m_roomList[0]->sceneryData,32,32), 1);
		theModel->m_objectList[3]->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
		theModel->m_objectList[3]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->m_roomList[0]->foregroundData,32,32), 2);
		theModel->m_objectList[3]->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");*/

		theModel->m_objectList[2]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->backgroundData,32,32), 0);
		theModel->m_objectList[2]->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
		theModel->m_objectList[2]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->sceneryData,32,32), 1);
		theModel->m_objectList[2]->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
		theModel->m_objectList[2]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->foregroundData,32,32), 2);
		theModel->m_objectList[2]->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
	}
	else if(!theView->IsKeyPressed('R') && generateRoom)
	{
		generateRoom = false;
	}
}

bool ControlHandler::ProcessInputs()
{
	if(theView->isQuitGame())
	{
		return false;
	}
	KeyboardUpdate();
	MouseUpdate();

	return true;
}
