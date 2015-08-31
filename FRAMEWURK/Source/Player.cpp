#include "Player.h"
#include "ModelHandler.h"

Player::Player(std::string name)
	: on_ground(true),
	is_running(false),
	stand_activated(false),
	keyPressed(0),
// Protected Info
	m_maxFear(100.f),
	m_currFear(2.f),
	m_movementDelay(0.0),
	m_movementTimer(0.0),
	m_playerPos(0,0,0),
	m_playerDirection(1,0,0),
	m_boundingbox(1.f,1.f,1.f,-1.f,-1.f,-1.f),           //Can be used for QuadTree, just leaving here for now
	m_playerSanity(0.f),
	m_animationState(STATE_IDLE_DOWN),
	m_fearCooldown(0.0),
	m_visiblityFactor(0.f)
{
	this->m_name = name;
}

Player::~Player() 
{
}

void Player::move(double dt,World* currentWorld, std::vector<std::vector<int>> collisionMap)
{
	int yColiision = Math::Max(0, (int)((abs)(m_playerPos.y)/32)+25);
	int xColiision = (int)(m_playerPos.x/32);
	/*std::cout << xColiision << " " << yColiision << " " << Math::Max(0, collisionMap[yColiision][xColiision]) << std::endl;
	std::cout << collisionMap[0].size() << " " << collisionMap.size() << std::endl;*/

	/*if (controls.use)
	{
			std::cout << "Start" << std::endl;
		for(unsigned i = 0; i < collisionMap.size(); ++i)
			{
				for(unsigned j = 0; j < collisionMap[i].size(); ++j)
				{
					if (yColiision == i && xColiision == j)
						std::cout << "P ";
					else
						std::cout << Math::Max(0, collisionMap[i][j]) << " ";
				}
				std::cout << std::endl;
			}
		std::cout << "End" << std::endl;

		system("pause");
	}*/

	if(controls.up && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision-1][xColiision]<100) && m_playerPos.y < 0)
	{
		if(collisionMap[yColiision-1][xColiision] == 2)
		{
			this->m_movementTimer = 0.0;
			stand_activated = false;
			if (currentWorld->sceneryData[yColiision-1][xColiision] == RED_TABLE_TILE3)
			{
				if(currentWorld->sceneryData[yColiision-3][xColiision] == -1 && currentWorld->backgroundData[yColiision-3][xColiision] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision-3][xColiision] = currentWorld->sceneryData[yColiision-2][xColiision];
					currentWorld->sceneryData[yColiision-2][xColiision] = currentWorld->sceneryData[yColiision-1][xColiision];
					currentWorld->sceneryData[yColiision-3][xColiision+1] = currentWorld->sceneryData[yColiision-2][xColiision+1];
					currentWorld->sceneryData[yColiision-2][xColiision+1] = currentWorld->sceneryData[yColiision-1][xColiision+1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision-1][xColiision] = -1;
					currentWorld->sceneryData[yColiision-1][xColiision+1] = -1;
					currentWorld->collisionData[yColiision-3][xColiision] = 2;
					currentWorld->collisionData[yColiision-3][xColiision+1] = 2;
					currentWorld->collisionData[yColiision-1][xColiision] = 0;
					currentWorld->collisionData[yColiision-1][xColiision+1] = 0;
				}
			}
			else if (currentWorld->sceneryData[yColiision-1][xColiision] == RED_TABLE_TILE4)
			{
				if(currentWorld->sceneryData[yColiision-3][xColiision-1] == -1 && currentWorld->backgroundData[yColiision-3][xColiision-1] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision-3][xColiision] = currentWorld->sceneryData[yColiision-2][xColiision];
					currentWorld->sceneryData[yColiision-2][xColiision] = currentWorld->sceneryData[yColiision-1][xColiision];
					currentWorld->sceneryData[yColiision-3][xColiision-1] = currentWorld->sceneryData[yColiision-2][xColiision-1];
					currentWorld->sceneryData[yColiision-2][xColiision-1] = currentWorld->sceneryData[yColiision-1][xColiision-1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision-1][xColiision] = -1;
					currentWorld->sceneryData[yColiision-1][xColiision-1] = -1;
					currentWorld->collisionData[yColiision-3][xColiision] = 2;
					currentWorld->collisionData[yColiision-3][xColiision-1] = 2;
					currentWorld->collisionData[yColiision-1][xColiision] = 0;
					currentWorld->collisionData[yColiision-1][xColiision-1] = 0;
				}

			}
			else if (currentWorld->sceneryData[yColiision-1][xColiision] == RED_CHAIR_TILE)
			{
				if(currentWorld->sceneryData[yColiision-2][xColiision] == -1 && currentWorld->backgroundData[yColiision-2][xColiision] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision-2][xColiision] = currentWorld->sceneryData[yColiision-1][xColiision];
					currentWorld->foregroundData[yColiision-3][xColiision] = currentWorld->foregroundData[yColiision-2][xColiision];

					currentWorld->sceneryData[yColiision-1][xColiision] = -1;
					currentWorld->foregroundData[yColiision-1][xColiision] = -1;
					currentWorld->UpdateWorld = true;
					currentWorld->collisionData[yColiision-2][xColiision] = 2;
					currentWorld->collisionData[yColiision-1][xColiision] = 0;
				}
			}
		}
		else
		{
			this->m_movementTimer = 0.0;
			m_playerPos.y += 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
		}

	}
	if(controls.down && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision+1][xColiision] < 100 && m_playerPos.y < (collisionMap.size()+25)*32))
	{	
		if(collisionMap[yColiision+1][xColiision] == 2)
		{
			this->m_movementTimer = 0.0;
			stand_activated = false;
			if (currentWorld->sceneryData[yColiision+1][xColiision] == RED_TABLE_TILE1)
			{
				if(currentWorld->sceneryData[yColiision+3][xColiision] == -1 && currentWorld->backgroundData[yColiision+3][xColiision] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision+3][xColiision] = currentWorld->sceneryData[yColiision+2][xColiision];
					currentWorld->sceneryData[yColiision+2][xColiision] = currentWorld->sceneryData[yColiision+1][xColiision];
					currentWorld->sceneryData[yColiision+3][xColiision+1] = currentWorld->sceneryData[yColiision+2][xColiision+1];
					currentWorld->sceneryData[yColiision+2][xColiision+1] = currentWorld->sceneryData[yColiision+1][xColiision+1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision+1][xColiision] = -1;
					currentWorld->sceneryData[yColiision+1][xColiision+1] = -1;
					currentWorld->collisionData[yColiision+3][xColiision] = 2;
					currentWorld->collisionData[yColiision+3][xColiision+1] = 2;
					currentWorld->collisionData[yColiision+1][xColiision] = 0;	
					currentWorld->collisionData[yColiision+1][xColiision+1] = 0;
				}
			}
			else if (currentWorld->sceneryData[yColiision+1][xColiision] == RED_TABLE_TILE2)
			{
				if(currentWorld->sceneryData[yColiision+3][xColiision] == -1 && currentWorld->backgroundData[yColiision+3][xColiision] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision+3][xColiision] = currentWorld->sceneryData[yColiision+2][xColiision];
					currentWorld->sceneryData[yColiision+2][xColiision] = currentWorld->sceneryData[yColiision+1][xColiision];
					currentWorld->sceneryData[yColiision+3][xColiision-1] = currentWorld->sceneryData[yColiision+2][xColiision-1];
					currentWorld->sceneryData[yColiision+2][xColiision-1] = currentWorld->sceneryData[yColiision+1][xColiision-1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision+1][xColiision] = -1;
					currentWorld->sceneryData[yColiision+1][xColiision-1] = -1;
					currentWorld->collisionData[yColiision+3][xColiision] = 2;
					currentWorld->collisionData[yColiision+3][xColiision-1] = 2;
					currentWorld->collisionData[yColiision+1][xColiision] = 0;
					currentWorld->collisionData[yColiision+1][xColiision-1] = 0;
				}

			}
			else if (currentWorld->sceneryData[yColiision+1][xColiision] == RED_CHAIR_TILE)
			{
				if(currentWorld->sceneryData[yColiision+2][xColiision] == -1 && currentWorld->backgroundData[yColiision+2][xColiision] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision+2][xColiision] = currentWorld->sceneryData[yColiision+1][xColiision];
					currentWorld->foregroundData[yColiision][xColiision] = currentWorld->foregroundData[yColiision-1][xColiision];

					currentWorld->sceneryData[yColiision+1][xColiision] = -1;
					currentWorld->foregroundData[yColiision+1][xColiision] = -1;
					currentWorld->UpdateWorld = true;
					currentWorld->collisionData[yColiision+2][xColiision] = 2;
					currentWorld->collisionData[yColiision+1][xColiision] = 0;
				}
			}
		}
		else
		{
			this->m_movementTimer = 0.0;
			m_playerPos.y -= 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
		}
	}
	if(controls.left && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision-1] <100) && m_playerPos.x > 0)
	{
		if(collisionMap[yColiision][xColiision-1] == 2)
		{
			this->m_movementTimer = 0.0;
			stand_activated = false;
			if (currentWorld->sceneryData[yColiision][xColiision-1] == RED_TABLE_TILE2)
			{
				if(currentWorld->sceneryData[yColiision][xColiision-3] == -1 && currentWorld->backgroundData[yColiision][xColiision-3] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision][xColiision-3] = currentWorld->sceneryData[yColiision][xColiision-2];
					currentWorld->sceneryData[yColiision][xColiision-2] = currentWorld->sceneryData[yColiision][xColiision-1];
					currentWorld->sceneryData[yColiision+1][xColiision-3] = currentWorld->sceneryData[yColiision+1][xColiision-2];
					currentWorld->sceneryData[yColiision+1][xColiision-2] = currentWorld->sceneryData[yColiision+1][xColiision-1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision][xColiision-1] = -1;
					currentWorld->sceneryData[yColiision+1][xColiision-1] = -1;
					currentWorld->collisionData[yColiision][xColiision-3] = 2;
					currentWorld->collisionData[yColiision+1][xColiision-3] = 2;
					currentWorld->collisionData[yColiision][xColiision-1] = 0;	
					currentWorld->collisionData[yColiision+1][xColiision-1] = 0;
				}
			}
			else if (currentWorld->sceneryData[yColiision][xColiision-1] == RED_TABLE_TILE4)
			{
				if(currentWorld->sceneryData[yColiision][xColiision-3] == -1 && currentWorld->backgroundData[yColiision][xColiision-3] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision][xColiision-3] = currentWorld->sceneryData[yColiision][xColiision-2];
					currentWorld->sceneryData[yColiision][xColiision-2] = currentWorld->sceneryData[yColiision][xColiision-1];
					currentWorld->sceneryData[yColiision-1][xColiision-3] = currentWorld->sceneryData[yColiision-1][xColiision-2];
					currentWorld->sceneryData[yColiision-1][xColiision-2] = currentWorld->sceneryData[yColiision-1][xColiision-1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision][xColiision-1] = -1;
					currentWorld->sceneryData[yColiision-1][xColiision-1] = -1;
					currentWorld->collisionData[yColiision][xColiision-3] = 2;
					currentWorld->collisionData[yColiision-1][xColiision-3] = 2;
					currentWorld->collisionData[yColiision][xColiision-1] = 0;	
					currentWorld->collisionData[yColiision-1][xColiision-1] = 0;
				}

			}
			else if (currentWorld->sceneryData[yColiision][xColiision-1] == RED_CHAIR_TILE)
			{
				if(currentWorld->sceneryData[yColiision][xColiision-2] == -1 && currentWorld->backgroundData[yColiision][xColiision-2] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision][xColiision-2] = currentWorld->sceneryData[yColiision][xColiision-1];
					currentWorld->foregroundData[yColiision-1][xColiision-2] = currentWorld->foregroundData[yColiision-1][xColiision-1];

					currentWorld->sceneryData[yColiision-1][xColiision-1] = -1;
					currentWorld->foregroundData[yColiision-1][xColiision-1] = -1;
					currentWorld->UpdateWorld = true;
					currentWorld->collisionData[yColiision][xColiision-2] = 2;
					currentWorld->collisionData[yColiision][xColiision-1] = 0;
				}
			}
		}
		else
		{
			this->m_movementTimer = 0.0;
			m_playerPos.x -= 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
		}
	}
	if(controls.right && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision+1] <100))
	{
		if(collisionMap[yColiision][xColiision-1] == 2)
		{
			this->m_movementTimer = 0.0;
			stand_activated = false;
			if (currentWorld->sceneryData[yColiision][xColiision+1] == RED_TABLE_TILE2)
			{
				if(currentWorld->sceneryData[yColiision][xColiision+3] == -1 && currentWorld->backgroundData[yColiision][xColiision+3] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision][xColiision+3] = currentWorld->sceneryData[yColiision][xColiision+2];
					currentWorld->sceneryData[yColiision][xColiision+2] = currentWorld->sceneryData[yColiision][xColiision+1];
					currentWorld->sceneryData[yColiision+1][xColiision+3] = currentWorld->sceneryData[yColiision+1][xColiision+2];
					currentWorld->sceneryData[yColiision+1][xColiision+2] = currentWorld->sceneryData[yColiision+1][xColiision+1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision][xColiision+1] = -1;
					currentWorld->sceneryData[yColiision+1][xColiision+1] = -1;
					currentWorld->collisionData[yColiision][xColiision+3] = 2;
					currentWorld->collisionData[yColiision+1][xColiision+3] = 2;
					currentWorld->collisionData[yColiision][xColiision+1] = 0;	
					currentWorld->collisionData[yColiision+1][xColiision+1] = 0;
				}
			}
			else if (currentWorld->sceneryData[yColiision][xColiision+1] == RED_TABLE_TILE4)
			{
				if(currentWorld->sceneryData[yColiision][xColiision+3] == -1 && currentWorld->backgroundData[yColiision][xColiision+3] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision][xColiision+3] = currentWorld->sceneryData[yColiision][xColiision+2];
					currentWorld->sceneryData[yColiision][xColiision+2] = currentWorld->sceneryData[yColiision][xColiision+1];
					currentWorld->sceneryData[yColiision-1][xColiision+3] = currentWorld->sceneryData[yColiision-1][xColiision+2];
					currentWorld->sceneryData[yColiision-1][xColiision+2] = currentWorld->sceneryData[yColiision-1][xColiision+1];
					currentWorld->UpdateWorld = true;
					currentWorld->sceneryData[yColiision][xColiision+1] = -1;
					currentWorld->sceneryData[yColiision-1][xColiision+1] = -1;
					currentWorld->collisionData[yColiision][xColiision+3] = 2;
					currentWorld->collisionData[yColiision-1][xColiision+3] = 2;
					currentWorld->collisionData[yColiision][xColiision+1] = 0;	
					currentWorld->collisionData[yColiision-1][xColiision+1] = 0;
				}

			}
			else if (currentWorld->sceneryData[yColiision][xColiision+1] == RED_CHAIR_TILE)
			{
				if(currentWorld->sceneryData[yColiision][xColiision+2] == -1 && currentWorld->backgroundData[yColiision][xColiision+2] == RED_FLOORTILE)
				{
					currentWorld->sceneryData[yColiision][xColiision+2] = currentWorld->sceneryData[yColiision][xColiision+1];
					currentWorld->foregroundData[yColiision-1][xColiision+2] = currentWorld->foregroundData[yColiision-1][xColiision+1];

					currentWorld->sceneryData[yColiision-1][xColiision+1] = -1;
					currentWorld->foregroundData[yColiision-1][xColiision+1] = -1;
					currentWorld->UpdateWorld = true;
					currentWorld->collisionData[yColiision][xColiision+2] = 2;
					currentWorld->collisionData[yColiision][xColiision+1] = 0;
				}
			}
		}
		else
		{
			this->m_movementTimer = 0.0;
			m_playerPos.x += 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
		}
	}
}

void Player::update(double dt, World* currentWorld, int currentRoom, ModelHandler * theModel)
{
	std::cout << this->m_playerPos << std::endl;

	m_movementTimer += dt;
	m_immunityTimer -= dt;

	if(m_currFear > 50)
	{
		m_movementDelay = 0.1;
	}
	else
	{
		m_movementDelay = 0.08; // fer weng jew
	}
	getPassiveEffect(this->m_playerInventory.getItem(2)); //Slot 2 = Equipment

	move(dt, currentWorld, currentWorld->collisionData);
	Interact(dt, currentWorld, currentWorld->collisionData,theModel);

	m_fearCooldown -= dt;
	if(m_fearCooldown <= 0.0)
	{
		m_fearCooldown = 0.0;
		m_currFear -= (float)(dt) * 1.5f;
	}
	m_currFear = Math::Clamp(m_currFear,2.f,100.f);
	m_playerSanity = Math::RandFloatMinMax(60.f,80.f);
}

Inventory &Player::getInventory()
{
	return this->m_playerInventory;
}

float Player::getSanity()
{
	return this->m_playerSanity;
}

void Player::getPassiveEffect(Item * item)
{
	switch(item->getItemID())
	{
	case ITEM_COMPASS:
		break;
	case ITEM_MAP:
		break;
	case ITEM_SAFETY_CHARM:
		break;
	case ITEM_EQUIPMENT_BOOTS:
		m_movementDelay -= 0.02;
		break;
	case ITEM_EQUIPMENT_GLASSES:
		break;
	case ITEM_EQUIPMENT_ARMOR:
		break;
	case ITEM_EQUIPMENT_INVISCLOAK:
		break;
	}
}

void Player::Interact(double dt, World* currentWorld, std::vector<std::vector<int>> collisionMap, ModelHandler * theModel)
{
	int yColiision = Math::Max(0, (int)((abs)(m_playerPos.y)/32)+25);
	int xColiision = (int)(m_playerPos.x/32);

	if (!stand_activated)
	{
		switch(collisionMap[yColiision][xColiision])
		{
			case COLLISION_BLUE_TILEYELLOWBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < collisionMap.size(); i++)
				{
					for (unsigned j = 0; j < collisionMap[i].size(); j++)
					{
						if (currentWorld->sceneryData[i][j] == BLUE_TILEYELLOWBLOCK_OFF)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEYELLOWBLOCK;
							currentWorld->collisionData[i][j] = 100;
							currentWorld->UpdateWorld = true;
						}
						else if (currentWorld->sceneryData[i][j] == BLUE_TILEYELLOWBLOCK)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEYELLOWBLOCK_OFF;
							currentWorld->collisionData[i][j] = 0;
							currentWorld->UpdateWorld = true;
						}
					}
				}
				std::cout << "On yellow button" << std::endl;
			}
			break;
			case COLLISION_BLUE_TILEGRAYBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < collisionMap.size(); i++)
				{
					for (unsigned j = 0; j < collisionMap[i].size(); j++)
					{
						if (currentWorld->sceneryData[i][j] == BLUE_TILEGRAYBLOCK_OFF)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEGRAYBLOCK;
							currentWorld->collisionData[i][j] = 100;
							currentWorld->UpdateWorld = true;
						}
						else if (currentWorld->sceneryData[i][j] == BLUE_TILEGRAYBLOCK)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEGRAYBLOCK_OFF;
							currentWorld->collisionData[i][j] = 0;
							currentWorld->UpdateWorld = true;
						}
					}
				}
				std::cout << "On gay button" << std::endl;
			}
			break;
			case COLLISION_BLUE_TILEPURPLEBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < collisionMap.size(); i++)
				{
					for (unsigned j = 0; j < collisionMap[i].size(); j++)
					{
						if (currentWorld->sceneryData[i][j] == BLUE_TILEPURPLEBLOCK_OFF)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEPURPLEBLOCK;
							currentWorld->collisionData[i][j] = 100;
							currentWorld->UpdateWorld = true;
						}
						else if (currentWorld->sceneryData[i][j] == BLUE_TILEPURPLEBLOCK)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEPURPLEBLOCK_OFF;
							currentWorld->collisionData[i][j] = 0;
							currentWorld->UpdateWorld = true;
						}
					}
				}
				std::cout << "On purpur button" << std::endl;
			}
			break;
			case COLLISION_BLUE_TILEREDBUTTON:
			{
				stand_activated = true;
				for (unsigned i = 0; i < collisionMap.size(); i++)
				{
					for (unsigned j = 0; j < collisionMap[i].size(); j++)
					{
						if (currentWorld->sceneryData[i][j] == BLUE_TILEREDBLOCK_OFF)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEREDBLOCK;
							currentWorld->collisionData[i][j] = 100;
							currentWorld->UpdateWorld = true;
						}
						else if (currentWorld->sceneryData[i][j] == BLUE_TILEREDBLOCK)
						{
							currentWorld->sceneryData[i][j] = BLUE_TILEREDBLOCK_OFF;
							currentWorld->collisionData[i][j] = 0;
							currentWorld->UpdateWorld = true;
						}
					}
				}
				std::cout << "On FIREENDINGE button" << std::endl;
			}
			break;
		}
	}

	switch(collisionMap[yColiision+1][xColiision])
	{
	case 100:
		std::cout << "Wall Below" << std::endl;
		if(currentWorld->getWorldID() == WORLD_MAINMENU)
		{
			switch(currentWorld->sceneryData[yColiision+1][xColiision])
			{
			case MAINMENU_PILLOWBEDTOP:
				{
					if ((controls.use) && ((m_playerPos.y -32 == MainMenuNight1PositionY) && (m_playerPos.x  == MainMenuNight1PositionX)))
					{
						std::cout << "Test" << std::endl;
						theModel->currentWorld = WORLD_FRIENDS_TUTORIAL;
						theModel->Evil->SetData(theModel->m_worldList[theModel->currentWorld]->collisionData);
					}
				}
				break;
			case MAINMENU_PILLOWBEDBOTTOM:
				{

				}
				break;
			case MAINMENU_PILLOWLESSBEDTOP:
				{

				}
				break;
			case MAINMENU_PILLOWLESSBEDBOTTOM:
				{

				}
				break;
			}
		}
		break;
	default:
		break;
	}


	switch(collisionMap[yColiision-1][xColiision])
	{
	case 100:
		std::cout << "Wall Above" << std::endl;
		switch(currentWorld->sceneryData[yColiision+1][xColiision])
		{
		case MAINMENU_PILLOWBEDTOP:
			{
				
			}
			break;
		case MAINMENU_PILLOWBEDBOTTOM:
			{

			}
			break;
		case MAINMENU_PILLOWLESSBEDTOP:
			{

			}
			break;
		case MAINMENU_PILLOWLESSBEDBOTTOM:
			{

			}
			break;
		}
		break;
	default:
		break;
	}

	switch(collisionMap[yColiision][xColiision+1])
	{
	case 100:
		std::cout << "Wall Right" << std::endl;
		break;
	default:
		break;
	}

	switch(collisionMap[yColiision][xColiision-1])
	{
	case 100:
		std::cout << "Wall Left" << std::endl;
		break;
	default:
		break;
	}
}

double Player::getImmunityTimer()
{
	return this->m_immunityTimer;
}

void Player::setImmunityTimer(double time)
{
	this->m_immunityTimer = time;
}

float Player::getVisiblityFactor()
{
	return this->m_visiblityFactor;
}

void Player::setVisibilityFactor(float visibility)
{
	this->m_visiblityFactor = visibility;
}
