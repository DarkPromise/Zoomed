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
	m_visiblityFactor(0.f),
	levelGoal(false),
	hiding(false),
	character(1),
	isDead(false)
{
	this->m_name = name;
}

Player::~Player() 
{
}

void Player::move(double dt, ModelHandler * theModel, std::vector<std::vector<int>> collisionMap)
{
	int yColiision = Math::Max(0, (int)((abs)(m_playerPos.y)/32)+25);
	int xColiision = (int)(m_playerPos.x/32);

	bool moved = false;
	bool canMove = true;

	if(controls.up && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision-1][xColiision]<100) && m_playerPos.y+32 < 0 )
	{
		if (theModel->currentWorld == WORLD_FRIENDS_TUTORIAL)
		{
			if (theModel->getFriend()->GetPos_x() == this->getPosition().x && theModel->getFriend()->GetPos_y() == this->getPosition().y+32
				&& collisionMap[yColiision-2][xColiision] >= 100)
			{
				canMove = false;
			}
		}

		if (canMove)
		{
			this->m_animationState = Player::STATE_WALKING_UP;
			this->m_movementTimer = 0.0;
			m_playerPos.y += 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
			moved = true;
		}
	}

	if(controls.down && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision+1][xColiision] < 100 && (unsigned)(yColiision+2) < collisionMap.size()))
	{
		if (theModel->currentWorld == WORLD_FRIENDS_TUTORIAL)
		{
			if (theModel->getFriend()->GetPos_x() == this->getPosition().x && theModel->getFriend()->GetPos_y() == this->getPosition().y-32
				&& collisionMap[yColiision+2][xColiision] >= 100)
			{
				canMove = false;
			}
		}

		if (canMove)
		{
			this->m_animationState = Player::STATE_WALKING_DOWN;
			this->m_movementTimer = 0.0;
			m_playerPos.y -= 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
			moved = true;
		}
	}

	if(controls.left && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision-1] <100) && (m_playerPos.x-32 > 0))
	{
		if (theModel->currentWorld == WORLD_FRIENDS_TUTORIAL)
		{
			if (theModel->getFriend()->GetPos_x() == this->getPosition().x-32 && theModel->getFriend()->GetPos_y() == this->getPosition().y
				&& collisionMap[yColiision][xColiision-2] >= 100 )
			{
				canMove = false;
			}
		}

		if (canMove)
		{
			this->m_animationState = Player::STATE_WALKING_LEFT;
			this->m_movementTimer = 0.0;
			m_playerPos.x -= 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
			moved = true;
		}
	}

	if(controls.right && this->m_movementTimer > m_movementDelay && (collisionMap[yColiision][xColiision+1] <100 && (unsigned)(xColiision+2) < collisionMap[0].size()))
	{
		if (theModel->currentWorld == WORLD_FRIENDS_TUTORIAL)
		{
			if (theModel->getFriend()->GetPos_x() == this->getPosition().x+32 && theModel->getFriend()->GetPos_y() == this->getPosition().y
				&& collisionMap[yColiision][xColiision+2] >= 100)
			{
				canMove = false;
			}
		}

		if (canMove)
		{
			this->m_animationState = Player::STATE_WALKING_RIGHT;
			this->m_movementTimer = 0.0;
			m_playerPos.x += 32;
			m_currFear += (float)dt * 3;
			m_fearCooldown = 1.0;
			stand_activated = false;
			moved = true;
		}
	}

	if (!moved)
	{
		if (this->m_animationState == Player::STATE_WALKING_UP)
		{
			//this->m_animationState = Player::STATE_IDLE_UP;
		}
		else if (this->m_animationState == Player::STATE_WALKING_DOWN)
		{
			//this->m_animationState = Player::STATE_IDLE_DOWN;
		}
		else if (this->m_animationState == Player::STATE_WALKING_LEFT)
		{
		//	this->m_animationState = Player::STATE_IDLE_LEFT;
		}
		else if (this->m_animationState == Player::STATE_WALKING_RIGHT)
		{
			//this->m_animationState = Player::STATE_IDLE_RIGHT;
		}
	}
}

void Player::update(double dt, World* currentWorld, int currentRoom, ModelHandler * theModel)
{
	m_movementTimer += dt;
	m_immunityTimer -= dt;

	if(m_currFear >= 100)
	{
		theModel->getPlayer()->setIsHiding(true);
		theModel->currentWorld = WORLD_MAINMENU;
		theModel->getCurrLevel() = 0;
		isDead = true;
	}
	else	if(m_currFear > 50)
	{
		m_movementDelay = 0.1;
	}
	else
	{
		m_movementDelay = 0.08; // fer weng jew
	}
	getPassiveEffect(this->m_playerInventory.getItem(2)); //Slot 2 = Equipment
	
	if (!hiding)
	{
		move(dt, theModel, currentWorld->collisionData);
	}

	Interact(dt, currentWorld, currentWorld->collisionData,theModel);

	m_fearCooldown -= dt;
	if(m_fearCooldown <= 0.0)
	{
		m_fearCooldown = 0.0;
		m_currFear -= (float)(dt) * 1.5f;
	}
	m_currFear = Math::Clamp(m_currFear,2.f,100.f);
	m_playerSanity = Math::RandFloatMinMax(1.f,1.5f);
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
	if (!hiding)
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
				}
				break;
				case COLLISION_BLUE_FINISHTILE:
				{
					stand_activated = true;
					theModel->m_worldList[WORLD_FRIENDS_LEVEL1]->worldClear[0] = true;

					if (theModel->m_worldList[WORLD_FRIENDS_LEVEL1]->worldClear[0] && theModel->m_worldList[WORLD_FRIENDS_LEVEL1]->worldClear[1])
					{
						if ( theModel->currentWorld == WORLD_FRIENDS_FINISH)
						{
							theModel->currentWorld = WORLD_MAINMENU;
							theModel->getPlayer()->setPosition(Vector3(800,-1248, 0));
						}
						else
						{
							theModel->currentWorld = (WORLD_ID)((int)(theModel->currentWorld)+1);
							if (theModel->currentWorld == WORLD_FRIENDS_LEVEL1)
							{
								theModel->getPlayer()->setPosition(Vector3(2944,-768, 0));
							}
							else if (theModel->currentWorld == WORLD_FRIENDS_FINISH)
							{
								theModel->getPlayer()->setPosition(Vector3(800,-1088, 0));
							}
						}
					}
				}
				break;
				default:
				{
					stand_activated = true;
					levelGoal = false;
				}
				break;
				
			}
		}

		switch(collisionMap[yColiision+1][xColiision])
		{
		case 100:
			if(currentWorld->getWorldID() == WORLD_MAINMENU)
			{
				switch(currentWorld->sceneryData[yColiision+1][xColiision])
				{
				case MAINMENU_PILLOWBEDTOP:
					{
						if ((controls.use) && ((m_playerPos.y == MainMenuChangeCharPositionY) && (m_playerPos.x  == MainMenuChangeCharPositionX)))
						{
							character++;
							if(character > 4)
							{
								character = 1;
							}
							switch(character)
							{
							case 1:
								theModel->m_objectList[OBJ_PLAYER]->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_boy.tga");
								break;
							case 2:
								theModel->m_objectList[OBJ_PLAYER]->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_josh.tga");
								break;
							case 3:
								theModel->m_objectList[OBJ_PLAYER]->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_level1.tga");
								break;
							case 4:
								theModel->m_objectList[OBJ_PLAYER]->getMesh()->textureArray[0] = LoadTGA("Images//Character//char_main.tga");
								break;
							}
						}
					}
					break;
				case MAINMENU_PILLOWLESSBEDTOP:
					{
						if ((controls.use) && ((m_playerPos.y == MainMenuNight1PositionY) && (m_playerPos.x  == MainMenuNight1PositionX)))
						{
							theModel->currentWorld = WORLD_SCHOOL_LEVEL1;
							theModel->getCurrLevel() = 1;
							this->setPosition(Vector3(Level1SpawnPointX, Level1SpawnPointY, 0));
							theModel->getTextBox()->inText = true;
							theModel->getTextBox()->nextEpisode();
							theModel->getTextBox()->setParagraph(0);
						}
						else if((controls.use) && ((m_playerPos.y == MainMenuNight2PositionY) && (m_playerPos.x  == MainMenuNight2PositionX)))
						{
							theModel->currentWorld = WORLD_FRIENDS_TUTORIAL;
							theModel->getCurrLevel() = 2;
							theModel->m_objectList[OBJ_ENEMYSISTER]->isAlive = true;
							this->setPosition(Vector3(768, -1120, 0));
							theModel->getFather()->SetPos(2112, -896);

							theModel->getTextBox()->inText = true;
							theModel->getTextBox()->setParagraph(0);
						}
						else if((controls.use) && ((m_playerPos.y == MainMenuNight3PositionY) && (m_playerPos.x  == MainMenuNight3PositionX)))
						{
							theModel->currentWorld = WORLD_MECH;
							theModel->getCurrLevel() = 3;
							this->setPosition(Vector3(Level3SpawnPointX, Level3SpawnPointY, 0));

							theModel->getTextBox()->inText = true;
							theModel->getTextBox()->setParagraph(1);
						}
						else if((controls.use) && ((m_playerPos.y == MainMenuNight4PositionY) && (m_playerPos.x  == MainMenuNight4PositionX)))
						{
						}
					}
					break;
				}
			}
			else if(currentWorld->getWorldID() == WORLD_SCHOOL_LEVEL1)
			{
				case SCHOOL_ITEMBOX1:
					{
						if(controls.use)
						{
							for(int i = 0; i < ITEM_DEFAULT; ++i)
							{

							}
						}
					}
					break;
				case SCHOOL_ITEMBOX2:
					{
						if(controls.use)
						{
						}
					}
					break;
			}
			break;
		case 201:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.y -= 64;
				}
			}
			break;
		case 200:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.y -= 32;
				}
			}
			break;
		case 150:
			{
				if (controls.use)
				{
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision+1][xColiision] == 74)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision+1][xColiision] = 75;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision][xColiision] = 43;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision+1][xColiision] = 74;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision][xColiision] = 42;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		case 151:
			{
				if (controls.use)
				{
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision+1][xColiision] == 282)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision+1][xColiision] = 283;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision+1][xColiision] = 282;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		default:
			break;
		}

		switch(collisionMap[yColiision-1][xColiision])
		{
		case 100:
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
		case 200:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.y += 32;
				}
			}
			break;
		case 150:
			{
				if (controls.use)
				{
					//hide code
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision-1][xColiision] == 74)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision-1][xColiision] = 75;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision-2][xColiision] = 43;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision-1][xColiision] = 74;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision-2][xColiision] = 42;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		case 151:
			{
				if (controls.use)
				{
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision-1][xColiision] == 282)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision-1][xColiision] = 283;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision-1][xColiision] = 282;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		default:
			break;
		}

		switch(collisionMap[yColiision][xColiision+1])
		{
		case 100:
			break;
		case 200:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.x += 32;
				}
			}
			break;
		case 201:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.x += 32;
					this->m_playerPos.y -= 32;
				}
			}
			break;
		case 150:
			{
				if (controls.use)
				{
					//hide code
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision+1] == 74)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision+1] = 75;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision-1][xColiision+1] = 43;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision+1] = 74;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision-1][xColiision+1] = 42;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		case 151:
			{
				if (controls.use)
				{
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision+1] == 282)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision+1] = 283;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision+1] = 282;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		default:
			break;
		}

		switch(collisionMap[yColiision][xColiision-1])
		{
		case 100:
			break;
		case 200:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.x -= 32;
				}
			}
			break;
		case 201:
			{
				if (controls.use)
				{
					//hide code
					this->setIsHiding(true);
					this->m_playerPos.x -= 32;
					this->m_playerPos.y -= 32;
				}
			}
			break;
		case 150:
			{
				if (controls.use)
				{
					//hide code
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision-1] == 74)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision-1] = 75;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision-1][xColiision-1] = 43;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision-1] = 74;
						theModel->m_worldList[theModel->currentWorld]->foregroundData[yColiision-1][xColiision-1] = 42;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		case 151:
			{
				if (controls.use)
				{
					if (theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision-1] == 282)
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision-1] = 283;
					}
					else
					{
						theModel->m_worldList[theModel->currentWorld]->sceneryData[yColiision][xColiision-1] = 282;
					}
					currentWorld->UpdateWorld = true;
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (controls.use)
		{
			this->setIsHiding(false);
			this->m_playerPos.y -= 32;
			this->stand_activated = false;
		}
	}

	//Hardcoded Position Interaction Values
	static bool Objective1 = false;
	static bool Message1 = false;
	static bool Objective2 = false;
	static bool Objective3 = false;
	static bool Message2 = false;
	static bool Objective4 = false;
	static bool Objective5 = false;
	static bool Objective6 = false;

	if(theModel->currentWorld == WORLD_SCHOOL_LEVEL1)
	{
		if(controls.use)
		{
			if(m_playerPos.x == Level1Obj1X && m_playerPos.y == Level1Obj1Y)
			{
				if(Objective1 == false)
				{
					Objective1 = true;
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(1);
				}
				else
				{
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(2);
				}
			}
			if((m_playerPos.x == Level1Obj2X1 || m_playerPos.x == Level1Obj2X2) && (m_playerPos.y == Level1Obj2Y))
			{
				if(Objective1 == true)
				{
					if(Objective2 == false)
					{
						Objective2 = true;
						theModel->getTextBox()->inText = true;
						theModel->getTextBox()->setParagraph(5);
						//Teleport Player upwards
						m_playerPos.y += 160; //5 Tiles
					}
					else
					{
						//Teleport Player upwards
						m_playerPos.y += 160; //5 Tiles
					}
				}
				else
				{
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(4);
				}
			}
		}
		if(m_playerPos.x == Level1Message1X && m_playerPos.y == Level1Message1Y)
		{
			if(Message1 == false)
			{
				Message1 = true;
				theModel->getTextBox()->inText = true;
				theModel->getTextBox()->setParagraph(3);
			}
		}
		if(m_playerPos.x == Level1Obj3X && m_playerPos.y == Level1Obj3Y)
		{
			if(controls.use)
			{
				if(Objective3 == false)
				{
					Objective3 = true;
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(6);
				}
				else
				{
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(7);
				}
			}
		}
		if(m_playerPos.x == Level1Message2X && m_playerPos.y == Level1Message2Y)
		{
			if(Message2 == false)
			{
				Message2 = true;
				theModel->getTextBox()->inText = true;
				theModel->getTextBox()->setParagraph(8);
			}
		}
		if(m_playerPos.x == Level1Obj4X && m_playerPos.y == Level1Obj4Y)
		{
			if(Objective4 == false)
			{
				Objective4 = true;
				theModel->getTextBox()->inText = true;
				theModel->getTextBox()->setParagraph(9);
			}
		}
		if(m_playerPos.x == Level1Obj5X && m_playerPos.y == Level1Obj5Y)
		{
			if(controls.use)
			{
				if(Objective4 == true)
				{
					if(Objective5 == false)
					{
						Objective5 = true;
						theModel->getTextBox()->inText = true;
						theModel->getTextBox()->setParagraph(11);
					}
					else
					{
						theModel->getTextBox()->inText = true;
						theModel->getTextBox()->setParagraph(12);
					}
				}
				else
				{
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(10);
				}
			}
		}
		if(m_playerPos.x == Level1Obj6X && m_playerPos.y == Level1Obj6Y)
		{
			if(controls.use)
			{
				if(Objective6 == false)
				{
					Objective6 = true;
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(13);
				}
				else
				{
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(12);
				}
			}
		}

		if((m_playerPos.x == Level1FinishX1 || m_playerPos.x == Level1FinishX2) && (m_playerPos.y == Level1FinishY))
		{
			if(controls.use)
			{
				if(Objective6 == true)
				{
					if(Objective5 == true)
					{
						//Go back to main menu
						theModel->getTextBox()->inText = true;
						theModel->getTextBox()->setParagraph(15);

						theModel->currentWorld = WORLD_MAINMENU;
						theModel->getCurrLevel() = 0;
						this->setPosition(Vector3(Level1FinishSpawnX, Level1FinishSpawnY, 0));
					}
					else
					{
						theModel->getTextBox()->inText = true;
						theModel->getTextBox()->setParagraph(16);
					}
				}
				else
				{
					theModel->getTextBox()->inText = true;
					theModel->getTextBox()->setParagraph(17);
				}
			}
		}

		if((m_playerPos.x == Level1Obj2X1 || m_playerPos.x == Level1Obj2X2) && (m_playerPos.y == Level1Obj2Back))
		{
			m_playerPos.y -= 128;
		}
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
