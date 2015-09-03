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
	keyUse = false;

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
			//Do the action(Parse into theView)
		}
		//exit
	}
	else if(!theView->IsButtonPressed(0) && theView->MouseInfo.m_bLeftButtonPressed)
	{
		theView->MouseInfo.m_bLeftButtonPressed = false;
	}
}

void ControlHandler::KeyboardUpdate()
{
	static bool toggleFullScreen = false;
	static bool generateRoom = false;

	if(theView->IsKeyPressed(VK_SPACE))
	{
		if (keyHeldSpace)
		{
			keyHeldSpace = false;
			if (theModel->getTextBox()->inText)
			{
				if (theModel->getTextBox()->paragraphFinished() && theModel->getTextBox()->isFinished())
				{
					theModel->getTextBox()->inText = false;
				}
				else
				{
					if (theModel->getTextBox()->isFinished())
					{
						//myEngine2->play2D(SoundFX[SOUND_NEXT]);
						theModel->getTextBox()->nextSentence();
					}
					else
					{
						theModel->getTextBox()->SpeedUp(true);
					}
				}
			}
		}
	}
	else if (!theView->IsKeyPressed(VK_SPACE))
	{
		keyHeldSpace = true;
	}

	if(theView->IsKeyPressed('W'))
	{
		if(keyHeldUp == false)
		{
		keyHeldUp = true;
		theModel->getPlayer()->controls.up = true;
		}
		else if(keyHeldUp == true)
		{
			theModel->getPlayer()->controls.up = false;
		}
	}
	else if(!theView->IsKeyPressed('W') && keyHeldUp)
	{
		keyHeldUp = false;
		theModel->getPlayer()->controls.up = false;
	}

	if(theView->IsKeyPressed('A'))
	{
		if(keyHeldLeft== false)
		{
		keyHeldLeft = true;
		theModel->getPlayer()->controls.left = true;
		}
		else if(keyHeldLeft == true)
		{
			theModel->getPlayer()->controls.left = false;
		}
	}
	else if(!theView->IsKeyPressed('A') && keyHeldLeft)
	{
		keyHeldLeft = false;
		theModel->getPlayer()->controls.left = false;
	}

	if(theView->IsKeyPressed('S'))
	{
		if(keyHeldDown== false)
		{
		keyHeldDown = true;
		theModel->getPlayer()->controls.down = true;
		}
		else if(keyHeldDown == true)
		{
			theModel->getPlayer()->controls.down = false;
		}
	}
	else if(!theView->IsKeyPressed('S') && keyHeldDown)
	{
		keyHeldDown = false;
		theModel->getPlayer()->controls.down = false;
	}

	if(theView->IsKeyPressed('D'))
	{
		if(keyHeldRight == false)
		{
		keyHeldRight = true;
		theModel->getPlayer()->controls.right = true;
		}
		else if(keyHeldRight == true)
		{
			theModel->getPlayer()->controls.right = false;
		}
	}
	else if(!theView->IsKeyPressed('D') && keyHeldRight)
	{
		keyHeldRight = false;
		theModel->getPlayer()->controls.right = false;
	}

	if(theView->IsKeyPressed('E'))
	{
		if(keyUse == false)
		{
		keyUse = true;
		theModel->getPlayer()->controls.use = true;
		}
		else if(keyUse == true)
		{
			theModel->getPlayer()->controls.use = false;
		}
	}
	else if(!theView->IsKeyPressed('E') && keyUse)
	{
		keyUse = false;
		theModel->getPlayer()->controls.use = false;
	}

	if(theModel->currentWorld != WORLD_MAINMENU)
	{
		if(theView->IsKeyPressed(VK_BACK))
		{
			theModel->currentWorld = WORLD_MAINMENU;
			theModel->getCurrLevel() = 0;
			theModel->getPlayer()->setPosition(Vector3(800, -1248, 0));
		}
	}

	if(theView->IsKeyPressed('1'))
	{
		theModel->getPlayer()->getInventory().useItem(1,theModel->getPlayer());
	}

	if(theView->IsKeyPressed('2'))
	{
		theModel->getPlayer()->getInventory().useItem(2,theModel->getPlayer());
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
