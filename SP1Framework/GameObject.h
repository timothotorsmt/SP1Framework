#pragma once
#include "Position.h"
#include "Grid.h"

//made by dennis wong
//edited by timothy
//edited by jeremy
class GameObject
{
protected:
	Position objectPosition;
	char entity_char;

public:
	//constructors and destructors
	GameObject();
	virtual ~GameObject();

	//others
	virtual void Interact(GameObject* obj) = 0;
	virtual bool isCollided(GameObject* obj) = 0;
	virtual bool checkForCollision(Grid map, int direction) = 0;
	virtual void MoveObject(int x, int y) = 0;

	//getters and setters
	//composition
	Position getObjectPosition();
	char getEntityChar();
	void setEntityChar(char c);
};
