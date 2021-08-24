#include "CLP.h"
#include <iostream>
#include <fstream>

CLP::CLP()
{
	SecureActive = false;

	// Create field
	for (int i = 0; i < 10; i++) closeTextField[i] = new CloseButtonField(3 + i, 9);

	// Fixed
	myFixOutput[0] = new FixedPattern(13, 1);
	myFixOutput[1] = new FixedPattern(13, 2);
	myFixOutput[2] = new FixedPattern(13, 3);

	// 1
	myOutput[0] = new PatternCode(5, 1, '0');
	myOutput[1] = new PatternCode(6, 1, 'a');
	myOutput[2] = new PatternCode(7, 1, '0');

	// 2
	myOutput[3] = new PatternCode(4, 2, '0');
	myOutput[4] = new PatternCode(5, 2, 'a');
	myOutput[5] = new PatternCode(6, 2, '0');
	myOutput[6] = new PatternCode(7, 2, 'a');
	myOutput[7] = new PatternCode(8, 2, '0');

	// 3
	myOutput[8] = new PatternCode(3, 3, '0');
	myOutput[9] = new PatternCode(4, 3, 'a');
	myOutput[10] = new PatternCode(5, 3, '0');
	myOutput[11] = new PatternCode(6, 3, 'a');
	myOutput[12] = new PatternCode(7, 3, '0');
	myOutput[13] = new PatternCode(8, 3, 'a');
	myOutput[14] = new PatternCode(9, 3, '0');

	for (int i = 0; i < 9; i++) NumberDupliate[i] = i + 1;
}

CLP::~CLP()
{
	delete[] myOutput;
	for (int i = 0; i < 15; i++) { myOutput[i] = nullptr; }

	delete[] myFixOutput;
	for (int i = 0; i < 3; i++) { myFixOutput[i] = nullptr; }

	delete[] closeTextField;
	for (int i = 0; i < 10; i++) { closeTextField[i] = nullptr; }

	std::cout << "The Combine Lock Program have been terminated!" << std::endl;
}

void CLP::CheckStatus()
{
	if (myFixOutput[0]->GetNumberSlot() == GetUnitOutput(1) 
		&& myFixOutput[1]->GetNumberSlot() == GetUnitOutput(2)
		&& myFixOutput[2]->GetNumberSlot() == GetUnitOutput(3))
	{

		// Duplicate Checker
		for (int check = 0; check < 9; check++) 
		{
			for (int find = check + 1; find < 9; find++)
			{
				if (NumberDupliate[check] == NumberDupliate[find])
				{
					SecureActive = false;
					break;
				}
				else { SecureActive = true; }
			}
		}
	}
	else { SecureActive = false; }
}

void CLP::StoreNumber(int index, int number)
{
	NumberDupliate[index] = number;
}

void CLP::UpdateInput(int x, int y)
{
	// Get Input of pattern code
	for (int i = 0; i < PatternCode::GetTotalPatternCode(); i++)
	{
		if (x == myOutput[i]->Get_X() && y == myOutput[i]->Get_Y())
		{
			myOutput[i]->ChangeValue();
			break;
		}
	}

	// Get Input of fixed code
	for (int i = 0; i < FixedPattern::GetTotalFixedPattern(); i++)
	{
		if (x == myFixOutput[i]->Get_X() && y == myFixOutput[i]->Get_Y())
		{
			myFixOutput[i]->ChangeValue();
			break;
		}
	}

	// Get Input of button field
	for (int i = 0; i < CloseButtonField::GetTotalButtonField(); i++)
	{
		if (x == closeTextField[i]->Get_X() && y == closeTextField[i]->Get_Y())
		{
			closeTextField[i]->CloseButton();
		}
	}
}

int CLP::GetUnitOutput(int index)
{
	int patternCode1_num = 0;
	int patternCode2_num = 0;
	int patternCode3_num = 0;

	// PattternCode_1
	switch (myOutput[1]->GetOutputValue())
	{
		case '+':
			patternCode1_num = myOutput[0]->GetOutputIndexValue() + myOutput[2]->GetOutputIndexValue();
			break;

		case '-':
			patternCode1_num = myOutput[0]->GetOutputIndexValue() - myOutput[2]->GetOutputIndexValue();
			break;

		case '/':
			patternCode1_num = myOutput[0]->GetOutputIndexValue() / myOutput[2]->GetOutputIndexValue();
			break;

		case 'X':
			patternCode1_num = myOutput[0]->GetOutputIndexValue() * myOutput[2]->GetOutputIndexValue();
			break;
	}

	// PatternCode_2
	switch (myOutput[4]->GetOutputValue())
	{
	case '+':
		patternCode2_num = myOutput[3]->GetOutputIndexValue() + myOutput[5]->GetOutputIndexValue();
		break;

	case '-':
		patternCode2_num = myOutput[3]->GetOutputIndexValue() - myOutput[5]->GetOutputIndexValue();
		break;

	case '/':
		patternCode2_num = myOutput[3]->GetOutputIndexValue() / myOutput[5]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode2_num = myOutput[3]->GetOutputIndexValue() * myOutput[5]->GetOutputIndexValue();
		break;
	}

	switch (myOutput[6]->GetOutputValue())
	{
	case '+':
		patternCode2_num += myOutput[7]->GetOutputIndexValue();
		break;

	case '-':
		patternCode2_num -= myOutput[7]->GetOutputIndexValue();
		break;

	case '/':
		patternCode2_num /= myOutput[7]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode2_num *= myOutput[7]->GetOutputIndexValue();
		break;
	}

	// PatternCode_3
	switch (myOutput[9]->GetOutputValue())
	{
	case '+':
		patternCode3_num = myOutput[8]->GetOutputIndexValue() + myOutput[10]->GetOutputIndexValue();
		break;

	case '-':
		patternCode3_num = myOutput[8]->GetOutputIndexValue() - myOutput[10]->GetOutputIndexValue();
		break;

	case '/':
		patternCode3_num = myOutput[8]->GetOutputIndexValue() / myOutput[10]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode3_num = myOutput[8]->GetOutputIndexValue() * myOutput[10]->GetOutputIndexValue();
		break;
	}

	switch (myOutput[11]->GetOutputValue())
	{
	case '+':
		patternCode3_num += myOutput[12]->GetOutputIndexValue();
		break;

	case '-':
		patternCode3_num -= myOutput[12]->GetOutputIndexValue();
		break;

	case '/':
		patternCode3_num /= myOutput[12]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode3_num *= myOutput[12]->GetOutputIndexValue();
		break;
	}

	switch (myOutput[13]->GetOutputValue())
	{
	case '+':
		patternCode3_num += myOutput[14]->GetOutputIndexValue();
		break;

	case '-':
		patternCode3_num -= myOutput[14]->GetOutputIndexValue();
		break;

	case '/':
		patternCode3_num /= myOutput[14]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode3_num *= myOutput[14]->GetOutputIndexValue();
		break;
	}

	// Get Info
	switch (index)
	{
	case 1:
		return patternCode1_num;

	case 2:
		return patternCode2_num;

	default:
		return patternCode3_num;
	}
}

int CLP::GetOutput_Number(int* index)
{
	return myOutput[*index]->GetOutputIndexValue();
}

char CLP::GetOutput_Expression(int* index)
{
	return myOutput[*index]->GetOutputValue();
}

int CLP::GetOutputFixed(int* index)
{
	return myFixOutput[*index]->GetNumberSlot();
}

bool CLP::CheckOnSecure()
{
	return SecureActive;
}