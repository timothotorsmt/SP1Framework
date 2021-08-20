#include "Player.h"

//done by dennis wong
//edited by timothy

bool Player::isPlayerCreate = false;
int Player::PocketMoney = 0;
bool Player::JewelCapture = false;

//done by dennis wong
//edited by jeremy
Player::Player()
{
	isPlayerCreate = true;
	entity_char = 'P';
	objectPosition.setCoordinates(17, 7, true);
	roomPosX = 3;
	roomPosY = 3;

}

//done by dennis wong
Player::~Player()
{
	isPlayerCreate = false;
}

//done by dennis wong
void Player::Interact(GameObject* obj)
{
	switch (obj->getEntityChar())
	{
	case 'M':
		PocketMoney++; // Default amount by 1
		break;

	case 'J':
		JewelCapture = true; // Player got the jewel
		break;
	}
}

//done by dennis wong
//edited by jeremy
bool Player::isCollided(GameObject* obj)
{
	if (objectPosition.isEqualPos(obj->getObjectPosition()))
		return true;
	else
		return false;
}

//done by dennis wong
//edited by timothy luk
//edited by jeremy
bool Player::checkForCollision(Grid map, int direction)
{
	switch (direction)
	{
	case 1: // UP
		if (objectPosition.getRow() != 0) {
			if (map.getTile(objectPosition.getColumn(), objectPosition.getRow() - 1).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	case 2: // LEFT
		if (objectPosition.getColumn() != 0) {
			if (map.getTile(objectPosition.getColumn() - 1, objectPosition.getRow()).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	case 3: // DOWN
		if (objectPosition.getRow() != 14) {
			if (map.getTile(objectPosition.getColumn(), objectPosition.getRow() + 1).get_tile_char() == '#') {
				return true;
			}
		}
		break;
	case 4: // RIGHT
		if (objectPosition.getColumn() != 34) {
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

//done by dennis wong
//edited by jeremy
void Player::MoveObject(int x, int y)
{
	objectPosition.setCoordinates(x, y, false);
}

//done by timothy
//edited by jeremy
int Player::checkIsOOB()
{
	if (objectPosition.getColumn() == 0) {
		objectPosition.setCoordinates(33, 0, false);
		shiftRoomPos((-1), 'x');
		return 2;
	}
	else if (objectPosition.getColumn() == 34) {
		objectPosition.setCoordinates(-33, 0, false);
		shiftRoomPos((1), 'x');
		return 4;
	}
	else if (objectPosition.getRow() == 0) {
		objectPosition.setCoordinates(0, 13, false);
		shiftRoomPos((-1), 'y');
		return 1;
	}
	else if (objectPosition.getRow() == 14) {
		objectPosition.setCoordinates(0, -13, false);
		shiftRoomPos((1), 'y');
		return 3;
	}
	else return 0;
}

//done by timothy
void Player::shiftRoomPos(int i, char c)
{
	if (c == 'x') {
		roomPosX += i;
	}
	else {
		roomPosY += i;
	}
}

//done by timothy
int Player::getRoomPos(char c)
{
	return (c == 'x') ? (roomPosX) : (roomPosY);
}

//done by dennis
bool Player::CheckOnPlayer()
{
	return isPlayerCreate;
}

int Player::CheckOnMoney()
{
	return PocketMoney;
}

bool Player::CheckOnJewel()
{
	return JewelCapture;
}