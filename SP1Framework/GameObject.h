#pragma once
#include "Position.h"

class GameObject : public Position
{
public:
	virtual ~GameObject();

	virtual void Interact(GameObject* obj) = 0;
	virtual bool isCollided(GameObject* obj) = 0;
	virtual bool checkForCollision(GameObject* obj, int direction) = 0;
	virtual void MoveObject(int x, int y) = 0;
};