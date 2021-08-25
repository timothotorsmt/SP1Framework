#include "Enemy.h"

int Enemy::numOfEnemies = 0;

Enemy::Enemy()
{
	numOfEnemies++;
}

Enemy::Enemy(int enemyPosX, int enemyPosY, int roomPosX, int roomPosY)
{
	numOfEnemies++;
	
	entity_char = 'G';

	this->enemyPosX = enemyPosX;
	this->enemyPosY = enemyPosY;
	objectPosition.setCoordinates(this->enemyPosX, this->enemyPosY, true);

	this->roomPosX = roomPosX;
	this->roomPosY = roomPosY;
}

Enemy::~Enemy()
{
	numOfEnemies--;
}

// checks if guard collides with player
bool Enemy::isCollided(GameObject* obj)
{
	if (objectPosition.isEqualPos(obj->getObjectPosition()))
		return true;
	else
		return false;
}

// interaction between guard and any overlapped object
// leave empty
void Enemy::Interact(GameObject* obj)
{
}

// checks if guard collides with the walls of the map
// WIP
bool Enemy::checkForCollision(Grid map, int direction)
{
	return false;
}

// change enemy position
void Enemy::MoveObject(int x, int y)
{
	objectPosition.setCoordinates(x, y, false);
	enemyPosX += x;
	enemyPosY += y;
}

int Enemy::getEnemyPosX(void)
{
	return enemyPosX;
}

int Enemy::getEnemyPosY(void)
{
	return enemyPosY;
}
