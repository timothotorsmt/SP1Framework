#pragma once
#include "GameObject.h"
class Collectible : public GameObject
{
private:
	int collPosX{};
	int collPosY{};
	int roomPosX{};
	int roomPosY{};
	char entity_char{};

public:
	Collectible();
	Collectible(int collPosX, int collPosY, int roomPosX, int roomPosY, char entity_char);
	virtual ~Collectible();

	bool isCollided(GameObject* obj);
	void Interact(GameObject* obj);
	bool checkForCollision(Grid map, int direction);
	void MoveObject(int x, int y);

	void setCollPosX(int x);
	void setCollPosY(int y);
	int getCollPosX(void);
	int getCollPosY(void);

	void setRoomPosX(int x);
	void setRoomPosY(int y);
	int getRoomPosX(void);
	int getRoomPosY(void);
};

