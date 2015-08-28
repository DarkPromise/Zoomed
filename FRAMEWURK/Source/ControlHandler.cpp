#include "ControlHandler.h"

ControlHandler::ControlHandler(ModelHandler * theModel, ViewHandler * theView) : theModel(NULL), theView(NULL)
{
	this->theView = theView;
	this->theModel = theModel;
	this->theModel->Init();

	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;

	keyHeldUp = false;
	keyHeldDown = false;
	keyHeldLeft = false;
	keyHeldRight = false;

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
			theView->Update(m_dAccumulatedTime_ThreadOne);

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

	if(theView->IsKeyPressed('W'))
	{
		/*if(keyHeldUp == false)
		{
		keyHeldUp = true;*/
		theModel->getPlayer()->controls.up = true;
		//}
		//else if(keyHeldUp == true)
		//{
		//	theModel->getPlayer()->controls.up = false;
		//}
	}
	else// if(!theView->IsKeyPressed('W') && keyHeldUp)
	{
		//keyHeldUp = false;
		theModel->getPlayer()->controls.up = false;
	}

	if(theView->IsKeyPressed('A'))
	{
		//if(keyHeldLeft== false)
		//{
		//keyHeldLeft = true;
		theModel->getPlayer()->controls.left = true;
		//}
		//else if(keyHeldLeft == true)
		//{
		//	theModel->getPlayer()->controls.left = false;
		//}
	}
	else// if(!theView->IsKeyPressed('A') && keyHeldLeft)
	{
		//keyHeldLeft = false;
		theModel->getPlayer()->controls.left = false;
	}

	if(theView->IsKeyPressed('S'))
	{
		//if(keyHeldDown== false)
		//{
		//keyHeldDown = true;
		theModel->getPlayer()->controls.down = true;
		//}
		//else if(keyHeldDown == true)
		//{
		//	theModel->getPlayer()->controls.down = false;
		//}
	}
	else// if(!theView->IsKeyPressed('S') && keyHeldDown)
	{
		//keyHeldDown = false;
		theModel->getPlayer()->controls.down = false;
	}

	if(theView->IsKeyPressed('D'))
	{
		//if(keyHeldRight == false)
		//{
		//keyHeldRight = true;
		theModel->getPlayer()->controls.right = true;
		//}
		//else if(keyHeldRight == true)
		//{
		//	theModel->getPlayer()->controls.right = false;
		//}
	}
	else// if(!theView->IsKeyPressed('D') && keyHeldRight)
	{
		//keyHeldRight = false;
		theModel->getPlayer()->controls.right = false;
	}

	if(theView->IsKeyPressed('H'))
	{
		//theModel->getPlayer()->controls.use = true;

		std::cout << "Start" << std::endl;
		for(unsigned i = 0; i < theModel->Evil->colData.size(); ++i)
			{
				for(unsigned j = 0; j < theModel->Evil->colData[i].size(); ++j)
				{
					if (theModel->Evil->GetPos_y()/32 == i && theModel->Evil->GetPos_x()/32 == j)
						std::cout << "P ";
					else
						std::cout << Math::Max(0, theModel->Evil->colData[i][j]) << " ";
				}
				std::cout << std::endl;
			}
		std::cout << "End" << std::endl;

		system("pause");

		
	}
	else
	{
		//theModel->getPlayer()->controls.use = false;
	}

	if(theView->IsKeyPressed('E'))
	{
		theModel->getPlayer()->controls.use = true;
	}
	else
	{
		theModel->getPlayer()->controls.use = false;
	}

	if(theView->IsKeyPressed('1'))
	{
		theModel->getPlayer()->getInventory().useItem(1,theModel->getPlayer());
	}

	if(theView->IsKeyPressed('2'))
	{
		theModel->getPlayer()->getInventory().useItem(2,theModel->getPlayer());
	}

	if(theView->IsKeyPressed('R') && !generateRoom)
	{
		generateRoom = true;
		if (theModel->currentWorld+1 == WORLD_TOTAL)
		{
			theModel->currentWorld = WORLD_MAINMENU;
		}
		else
		{
			theModel->currentWorld = (WORLD_ID)((int)(theModel->currentWorld)+1);
		}
		/*theModel->m_worldList[1]->m_roomList[0]->generateRoom();
		theModel->m_worldList[1]->m_roomList[1]->generateRoom();

		theModel->m_objectList[3]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->m_roomList[0]->sceneryData,32,32), 1);
		theModel->m_objectList[3]->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
		theModel->m_objectList[3]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->m_roomList[0]->foregroundData,32,32), 2);
		theModel->m_objectList[3]->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");*/

		//theModel->m_objectList[2]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->backgroundData,32,32), 0);
		//theModel->m_objectList[2]->getMesh(0)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
		//theModel->m_objectList[2]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->sceneryData,32,32), 1);
		//theModel->m_objectList[2]->getMesh(1)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
		//theModel->m_objectList[2]->setMesh(MeshBuilder::GenerateTileMap("Test Background",Color(0.f,0.f,0.f),theModel->m_worldList[1]->foregroundData,32,32), 2);
		//theModel->m_objectList[2]->getMesh(2)->textureArray[0] = LoadTGA("Images//Tilesets//Tileset_ROOMS.tga");
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
