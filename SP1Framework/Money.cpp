#include "Money.h"
#include <iostream>

int Money::totalMoney = 0;

Money::Money(Grid level_map)
{
	totalMoney++;
	int x = 0;
	int y = 0;
	while (level_map.getTile(x + 7, y + 2).get_tile_char() != '?') {
		x = rand() % 21;
		y = rand() % 11;
	}
	objectPosition.setCoordinates(x + 7, y + 2, true);
	entity_char = 'M';
}

Money::~Money()
{
	totalMoney--;
}

void Money::Interact(GameObject* obj)
{
	delete this;
}

bool Money::isCollided(GameObject* obj)
{
	if (objectPosition.isEqualPos(obj->getObjectPosition()))
		return true;
	else
		return false;
}

bool Money::checkForCollision(Grid map, int direction)
{
	return false;
}

void Money::MoveObject(int x, int y)
{
}

int Money::GetMoneyCount()
{
	return totalMoney;
}
