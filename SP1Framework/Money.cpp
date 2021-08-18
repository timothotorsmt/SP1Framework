#include "Money.h"
#include <iostream>

int Money::totalMoney = 0;

Money::Money()
{
	totalMoney++;
	UpdatePosition(rand() % 50 + 0, rand() % 24 + 0, true);
	SetMarker('M');

	std::cout << "Money have been placed! (With Random Position)" << std::endl;
}

Money::Money(int x, int y)
{
	totalMoney++;
	UpdatePosition(x, y, true);
	SetMarker('M');

	std::cout << "Money have been placed! (With Position)" << std::endl;
}

Money::~Money()
{
	totalMoney--;
	std::cout << "Money have been taken by someone else!" << std::endl;
}

void Money::Interact(GameObject* obj) 
{
	delete this;
}

bool Money::isCollided(GameObject* obj)
{
	if (GetPosX() == obj->GetPosX() && GetPosY() == obj->GetPosY())
		return true;
	else
		return false;
}

bool Money::checkForCollision(GameObject* obj, int direction)
{
	return false;
}

void Money::MoveObject(int x, int y)
{
	// ??? No move function ???
}

int Money::GetMoneyCount()
{
	return totalMoney;
}