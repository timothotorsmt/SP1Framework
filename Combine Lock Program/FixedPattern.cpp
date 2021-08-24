#include "FixedPattern.h"
#include <iostream>

int FixedPattern::FixedPatternCreated = 0;

FixedPattern::FixedPattern(int x, int y)
{
	FixedPatternCreated++;

	NumberSlot = 1;
	indexValue = 1;

	Placement_X = x;
	Placement_Y = y;
}

FixedPattern::~FixedPattern()
{
	FixedPatternCreated--;
	std::cout << "The code have been erased!" << std::endl;
}

void FixedPattern::ChangeValue()
{
	if (indexValue != 9) indexValue++;
	else indexValue = 1;

	NumberSlot = indexValue;
}

int FixedPattern::GetNumberSlot()
{
	return NumberSlot;
}

int FixedPattern::Get_X()
{
	return Placement_X;
}

int FixedPattern::Get_Y()
{
	return Placement_Y;
}

int FixedPattern::GetTotalFixedPattern()
{
	return FixedPatternCreated;
}