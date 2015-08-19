#include "Room.h"
#include "MyMath.h"

Room_Object::Room_Object(ROOM_OBJECT_TYPE objectType)
{
	this->type = objectType;

	switch (objectType)
	{
		case ROOM_OBJECT_TESTPUZZLE_BED:
			{
				this->width = 2;
				this->height = 4;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE:
			{
				this->width = 2;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE:
			{
				this->width = 2;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_WHITE_TABLECLOTH_TABLE:
			{
				this->width = 3;
				this->height = 3;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BRONZE_CANDLESTICK:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BRONZE_BOTTLE:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_OPEN_BOOK:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_CLOSED_EXIT_BOTTOM:
			{
				this->width = 3;
				this->height = 1;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_OPEN_EXIT_BOTTOM:
			{
				this->width = 3;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_BIG_WINDOW:
			{
				this->width = 3;
				this->height = 4;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_SMALL_WINDOW:
			{
				this->width = 2;
				this->height = 2;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET:
			{
				this->width = 2;
				this->height = 3;
			}
			break;
		case ROOM_OBJECT_TESTPUZZLE_PATTERNED_FLOOR:
			{
				this->width = 1;
				this->height = 1;
			}
			break;
	}
}

Room_Object::~Room_Object(void)
{
}


Room::Room(ROOM_TYPE roomType)
{
	this->roomType = roomType;
}


Room::~Room(void)
{
}

void Room::generateRoom()
{
	// Reset data values
	for (unsigned i = 1; i < this->sceneryData.size()-1; i++)
	{
		std::fill(sceneryData[i].begin(), sceneryData[i].end(), -1);
		std::fill(collisionData[i].begin(), collisionData[i].end(), -1);
		std::fill(foregroundData[i].begin(), foregroundData[i].end(), -1);
	}

	// NOTE!! __data[1][0] IS THE TOP LEFT AFTER RENDERING

	switch (roomType)
	{
	case ROOM_TESTPUZZLE:
		{
			// Generate random exits
			this->numExit.clear();
			this->addExit(EXIT_DOWN);

			//generate objects
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_WHITE_TABLECLOTH_TABLE), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_BED), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));
			while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET), Math::RandIntMinMax(2, sceneryData[0].size()-2), Math::RandIntMinMax(3, sceneryData.size()-3)));

			// do not add bronze stuff or open book unless there is a white tablecloth table
			addObject(roomType, Room_Object(static_cast<Room_Object::ROOM_OBJECT_TYPE>(Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE+Math::RandIntMinMax(0, 3))), -1, -1);


			//add exits
			for (unsigned i = 0; i < numExit.size(); i++)
			{
				while (!addObject(roomType, Room_Object(Room_Object::ROOM_OBJECT_TESTPUZZLE_CLOSED_EXIT_BOTTOM), -1, -1));
			}
		}
		break;
	}
	
}

bool Room::addObject(ROOM_TYPE type, Room_Object object, int originX, int originY)
{
	Room_Object::ROOM_OBJECT_TYPE room_object = object.type;
	
	// If object is randomised
	if (originX != -1)
	{
		//Make sure object will be rendered in the room
		if (originY < 5 || (originY + object.height) > sceneryData.size()-2 || originX < 2 || (originX + object.width) > sceneryData[0].size()-2)
		{
			return false;
		}
	
		//Make sure object doesn't collide with other objects
		{
			for (int i = 0; i <= object.height; i++)
			{
				for (int j = 0; j <= object.width; j++)
				{
					if (sceneryData[originY+i][originX+j] != -1 || foregroundData[originY+i][originX+j] != -1 || collisionData[originY+i][originX+j] != -1)
					{
						return false;
					}
				}
			}
		}
	}

	if (type == ROOM_TESTPUZZLE)
	{
		switch (room_object)
		{
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BED:
			{
				sceneryData[originY][originX] = 360; sceneryData[originY][originX+1] = 361;
				sceneryData[originY+1][originX] = 392; sceneryData[originY+1][originX+1] = 393;
				sceneryData[originY+2][originX] = 424; sceneryData[originY+2][originX+1] = 425;
				sceneryData[originY+3][originX] = 456; sceneryData[originY+3][originX+1] = 457;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_MEDIUM_TABLE:
			{
				sceneryData[originY][originX] = 202; sceneryData[originY][originX+1] = 203;
				sceneryData[originY+1][originX] = 234; sceneryData[originY+1][originX+1] = 235;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_TABLE:
			{
				sceneryData[originY][originX] = 204; sceneryData[originY][originX+1] = 205;
				sceneryData[originY+1][originX] = 236; sceneryData[originY+1][originX+1] = 237;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_LEFT:
			{
				foregroundData[originY-1][originX] = 140;
				sceneryData[originY][originX] = 172;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_CHAIR_SLANT_RIGHT:
			{
				foregroundData[originY-1][originX] = 141;
				sceneryData[originY][originX] = 173;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_WHITE_TABLECLOTH_TABLE:
			{
				sceneryData[originY][originX] = 263; sceneryData[originY][originX+1] = 264; sceneryData[originY][originX+2] = 265;
				sceneryData[originY+1][originX] = 295; sceneryData[originY+1][originX+1] = 296; sceneryData[originY+1][originX+2] = 297;
				sceneryData[originY+2][originX] = 327; sceneryData[originY+2][originX+1] = 328; sceneryData[originY+2][originX+2] = 329;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_GLOBE:
			{
				for (int i = 0; i < sceneryData.size(); i++)
				{
					for (int j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i-1][j] = 136;
							foregroundData[i][j] = 168;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_CANDLESTICK:
			{
				for (int i = 0; i < sceneryData.size(); i++)
				{
					for (int j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i-1][j] = 137;
							foregroundData[i][j] = 169;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BRONZE_BOTTLE:
			{
				for (int i = 0; i < sceneryData.size(); i++)
				{
					for (int j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i][j] = 170;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_OPEN_BOOK:
			{
				for (int i = 0; i < sceneryData.size(); i++)
				{
					for (int j = 0; j < sceneryData[i].size(); j++)
					{
						if (sceneryData[i][j] == 264)
						{
							foregroundData[i][j] = 171;
						}
					}
				}
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_CLOSED_EXIT_BOTTOM:
			{
				originX = Math::RandFloatMinMax(3, sceneryData[0].size()-4);
				while (!((originX != -1) && (sceneryData[sceneryData.size()-3][originX] == -1)))
				{
					originX = Math::RandFloatMinMax(3, sceneryData[0].size()-4);
				}

				sceneryData[sceneryData.size()-2][originX] = 266; sceneryData[sceneryData.size()-2][originX+1] = 267; sceneryData[sceneryData.size()-2][originX+2] = 268;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_OPEN_EXIT_BOTTOM:
			{
				sceneryData[originY][originX] = 330; sceneryData[originY][originX+1] = 331; sceneryData[originY][originX+2] = 332;
				sceneryData[originY+1][originX] = 362; sceneryData[originY+1][originX+1] = 363; sceneryData[originY+1][originX+2] = 364;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_BIG_WINDOW:
			{
				sceneryData[originY][originX] = 39; sceneryData[originY][originX+1] = 40; sceneryData[originY][originX+2] = 41;
				sceneryData[originY+1][originX] = 71; sceneryData[originY+1][originX+1] = 72; sceneryData[originY+1][originX+2] = 73;
				sceneryData[originY+2][originX] = 103; sceneryData[originY+2][originX+1] = 104; sceneryData[originY+2][originX+2] = 105;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_SMALL_WINDOW:
			{
				sceneryData[originY][originX] = 42; sceneryData[originY][originX+1] = 43;
				sceneryData[originY+1][originX] = 74; sceneryData[originY+1][originX+1] = 75;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_GLASS_CABINET:
			{
				foregroundData[originY][originX] = 44; foregroundData[originY][originX+1] = 45;
				sceneryData[originY+1][originX] = 76; sceneryData[originY+1][originX+1] = 77;
				sceneryData[originY+2][originX] = 108; sceneryData[originY+2][originX+1] = 109;
			}
			break;
		case Room_Object::ROOM_OBJECT_TESTPUZZLE_PATTERNED_FLOOR:
			{
				sceneryData[originY][originX] = 288;
			}
			break;
		};
	}

	return true;
}

void Room::addExit(EXIT_DIRECTION exit)
{
	this->numExit.push_back(exit);
}