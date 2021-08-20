#include "Money.h"
#include <iostream>

//done by dennis wong
//edited by timothy (lightly)
int Money::totalMoney = 0;

//made by dennis wong
//edited by timothy
//edited by jeremy
Money::Money(Grid level_map)
{
	totalMoney++;
	//TODO: make this fit into the maps
	int x = 0;
	int y = 0;
	while (level_map.getTile(x + 7, y + 2).get_tile_char() != '?') {
		x = rand() % 21;
		y = rand() % 11;
	}
	objectPosition.setCoordinates(x + 7, y + 2, true);
	entity_char = 'M';
}

//done by dennis
Money::~Money()
{
	totalMoney--;
}

//done by dennis
void Money::Interact(GameObject* obj)
{
	delete this;
}

//done by dennis
//edited by jeremy
bool Money::isCollided(GameObject* obj)
{
	if (objectPosition.isEqualPos(obj->getObjectPosition()))
		return true;
	else
		return false;
}

//done by dennis wong
bool Money::checkForCollision(Grid map, int direction)
{
	return false;
}

void Money::MoveObject(int x, int y)
{
	// ??? No move function ???
}

//done by dennis wong
int Money::GetMoneyCount()
{
	return totalMoney;
}
