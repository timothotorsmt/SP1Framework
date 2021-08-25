#pragma once
#include "GameObject.h"
#include "Grid.h"

//created by jeremy chia
class Enemy : public GameObject
{
private:
	static int numOfEnemies;
	int enemyPosX{};
	int enemyPosY{};
	int roomPosX{};
	int roomPosY{};

public:
	Enemy();
	Enemy(int enemyPosX, int enemyPosY, int roomPosX, int roomPosY);
	virtual ~Enemy();

	bool isCollided(GameObject* obj);
	void Interact(GameObject* obj);
	bool checkForCollision(Grid map, int direction);
	void MoveObject(int x, int y);

	int getEnemyPosX(void);
	int getEnemyPosY(void);
};
