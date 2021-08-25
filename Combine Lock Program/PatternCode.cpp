#include "PatternCode.h"
#include <iostream>

int PatternCode::PatternCodeCreated = 0;

PatternCode::PatternCode(int x, int y, char T)
{
	PatternCodeCreated++;

	ExpressionOutput[0] = '+';
	ExpressionOutput[1] = '-';
	ExpressionOutput[2] = '/';
	ExpressionOutput[3] = 'X';

	PatternType = T;
	Placement_X = x;
	Placement_Y = y;

	valueIndex = 1;

	if (PatternType == '0') OutputValue = '1';
	else OutputValue = '+';
}

PatternCode::~PatternCode()
{
	PatternCodeCreated--;
	std::cout << "The code have been erased!" << std::endl;
}

void PatternCode::ChangeValue()
{
	switch (PatternType)
	{
		case '0':
			if (valueIndex != 9) valueIndex++;
			else valueIndex = 1;

			OutputValue = '0' + valueIndex;
			break;

		case 'a':
			if (valueIndex != 4) valueIndex++;
			else valueIndex = 1;

			OutputValue = ExpressionOutput[valueIndex - 1];
			break;
	}
}

char PatternCode::GetPatternType()
{
	return PatternType;
}

int PatternCode::Get_X()
{
	return Placement_X;
}

int PatternCode::Get_Y()
{
	return Placement_Y;
}

char PatternCode::GetOutputValue()
{
	return OutputValue;
}

int PatternCode::GetOutputIndexValue()
{
	return valueIndex;
}

int PatternCode::GetTotalPatternCode()
{
	return PatternCodeCreated;
}