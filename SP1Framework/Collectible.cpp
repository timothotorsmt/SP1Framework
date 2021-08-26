#include "Collectible.h"

Collectible::Collectible()
{
}

Collectible::Collectible(int collPosX, int collPosY, int roomPosX, int roomPosY, char entity_char)
{
	this->collPosX = collPosX;
	this->collPosY = collPosY;
	objectPosition.setCoordinates(this->collPosX, this->collPosY, true);

	this->roomPosX = roomPosX;
	this->roomPosY = roomPosY;
	this->entity_char = entity_char;
}

Collectible::~Collectible()
{
}

bool Collectible::isCollided(GameObject* obj)
{
	return false;
}

void Collectible::Interact(GameObject* obj)
{
}

bool Collectible::checkForCollision(Grid map, int direction)
{
	return false;
}

void Collectible::MoveObject(int x, int y)
{
}

void Collectible::setCollPosX(int x)
{
	collPosX = x;
}

void Collectible::setCollPosY(int y)
{
	collPosY = y;
}

int Collectible::getCollPosX(void)
{
	return collPosX;
}

int Collectible::getCollPosY(void)
{
	return collPosY;
}

void Collectible::setRoomPosX(int x)
{
	roomPosX = x;
}

void Collectible::setRoomPosY(int y)
{
	roomPosY = y;
}

int Collectible::getRoomPosX(void)
{
	return roomPosX;
}

int Collectible::getRoomPosY(void)
{
	return roomPosY;
}
