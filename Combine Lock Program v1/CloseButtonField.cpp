#include "CloseButtonField.h"
#include <iostream>

bool CloseButtonField::isCloseCalled = true;
int CloseButtonField::ButtonFieldCreated = 0;

CloseButtonField::CloseButtonField(int x, int y)
{
	ButtonFieldCreated++;
	isCloseCalled = false;

	Placement_X = x;
	Placement_Y = y;
}

CloseButtonField::~CloseButtonField()
{
	ButtonFieldCreated--;
	isCloseCalled = true;
	std::cout << "The button field have been erased!" << std::endl;
}

void CloseButtonField::CloseButton()
{
	isCloseCalled = true;
}

bool CloseButtonField::GetCloseCalled()
{
	return isCloseCalled;
}

int CloseButtonField::Get_X()
{
	return Placement_X;
}

int CloseButtonField::Get_Y()
{
	return Placement_Y;
}

int CloseButtonField::GetTotalButtonField()
{
	return ButtonFieldCreated;
}