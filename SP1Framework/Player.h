#pragma once
#include "GameObject.h"
#include "Grid.h"

class Player : public GameObject
{
private:
	static bool isPlayerCreate;
	static int PocketMoney;
	static bool jewelCaptureStatus;
	int roomPosX;
	int roomPosY;

public:
	Player();
	virtual ~Player();

	void Interact(GameObject* obj);				// Interact with object that is overlapped and ready to be execute
	bool isCollided(GameObject* obj);			// Check if object is overlap with anything
	bool checkForCollision(Grid map, int direction);	// Check if object possible to move
	void MoveObject(int x, int y);				// Move player and update position
	int checkIsOOB();
	void shiftRoomPos(int i, char c);
	int getRoomPos(char c);

	static void setPlayerAliveStatus(bool playerAliveStatus);
	static bool isPlayerAlive();

	static int CheckOnMoney();

	static void setJewelCaptureStatus(bool jewelStatus);
	static bool isJewelCaptured();
};
