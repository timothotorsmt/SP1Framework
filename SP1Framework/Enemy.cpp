#include "Enemy.h"

bool Enemy::isEnemyCreate = false;

Enemy::Enemy()
{
}

Enemy::Enemy(int enemyPosX, int enemyPosY, int roomPosX, int roomPosY)
{
	isEnemyCreate = true;
	entity_char = 'C';

	this->enemyPosX = enemyPosX;
	this->enemyPosY = enemyPosY;
	objectPosition.setCoordinates(Enemy::enemyPosX, Enemy::enemyPosY, true);
	
	this->roomPosX = roomPosX;
	this->roomPosY = roomPosY;
}

Enemy::~Enemy()
{
	isEnemyCreate = false;
}

// leave empty
void Enemy::Interact(GameObject* obj)
{
}

// checks if guard collides with player
bool Enemy::isCollided(GameObject* obj)
{
	if (objectPosition.isEqualPos(obj->getObjectPosition()))
		return true;
	else
		return false;
}

bool Enemy::checkForCollision(Grid map, int direction)
{
	return false;
}

void Enemy::MoveObject(int x, int y)
{
	objectPosition.setCoordinates(x, y, false);
}

int Enemy::getEnemyPosX(void)
{
	return enemyPosX;
}

int Enemy::getEnemyPosY(void)
{
	return enemyPosY;
}
