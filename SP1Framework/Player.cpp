#include "Player.h"

bool Player::isPlayerCreate = false;
int Player::PocketMoney = 0;
bool Player::jewelCaptureStatus = false;

Player::Player()
{
	isPlayerCreate = true;
	entity_char = 'P';
	objectPosition.setCoordinates(17, 6, true);
	roomPosX = 1;
	roomPosY = 0;
}

Player::~Player()
{
	isPlayerCreate = false;
}

void Player::Interact(GameObject* obj)
{
	switch (obj->getEntityChar())
	{
	case 'M':
		PocketMoney++; // Default amount by 1
		break;

	case 'J':
		jewelCaptureStatus = true; // Player got the jewel
		break;
	}
}

bool Player::isCollided(GameObject* obj)
{
	if (objectPosition.isEqualPos(obj->getObjectPosition()))
		return true;
	else
		return false;
}

bool Player::checkForCollision(Grid map, int direction)
{
	switch (direction)
	{
	case 1: // UP
		if (objectPosition.getRow() != 0) 
		{
			if (map.getTile(objectPosition.getColumn(), objectPosition.getRow() - 1).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	case 2: // LEFT
		if (objectPosition.getColumn() != 0) 
		{
			if (map.getTile(objectPosition.getColumn() - 1, objectPosition.getRow()).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	case 3: // DOWN
		if (objectPosition.getRow() != 14) 
		{
			if (map.getTile(objectPosition.getColumn(), objectPosition.getRow() + 1).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	case 4: // RIGHT
		if (objectPosition.getColumn() != 34) 
		{
			if (map.getTile(objectPosition.getColumn() + 1, objectPosition.getRow()).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	default: // STOP
		break;
	}
	//if no collision return true
	return false;
}

void Player::MoveObject(int x, int y)
{
	objectPosition.setCoordinates(x, y, false);
}

int Player::checkIsOOB()
{
	if (objectPosition.getColumn() == 0) 
	{
		objectPosition.setCoordinates(33, 0, false);
		shiftRoomPos((-1), 'x');
		return 2;
	}
	else if (objectPosition.getColumn() == 34) 
	{
		objectPosition.setCoordinates(-33, 0, false);
		shiftRoomPos((1), 'x');
		return 4;
	}
	else if (objectPosition.getRow() == 0) 
	{
		objectPosition.setCoordinates(0, 13, false);
		shiftRoomPos((-1), 'y');
		return 1;
	}
	else if (objectPosition.getRow() == 14) 
	{
		objectPosition.setCoordinates(0, -13, false);
		shiftRoomPos((1), 'y');
		return 3;
	}
	else return 0;
}

void Player::shiftRoomPos(int i, char c)
{
	if (c == 'x') 
	{
		roomPosX += i;
	}
	else 
	{
		roomPosY += i;
	}
}

int Player::getRoomPos(char c)
{
	return (c == 'x') ? (roomPosX) : (roomPosY);
}

void Player::setPlayerAliveStatus(bool playerAliveStatus)
{
	isPlayerCreate = playerAliveStatus;
}

bool Player::isPlayerAlive()
{
	return isPlayerCreate;
}

int Player::CheckOnMoney()
{
	return PocketMoney;
}

void Player::setJewelCaptureStatus(bool jewelStatus)
{
	jewelCaptureStatus = jewelStatus;
}

bool Player::isJewelCaptured()
{
	return jewelCaptureStatus;
}
