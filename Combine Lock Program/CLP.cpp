#include "CLP.h"
#include <iostream>
#include <fstream>

CLP::CLP()
{
	SecureActive = false;

	// Create field
	for (int i = 0; i < 10; i++) closeTextField[i] = new CloseButtonField(3 + i, 7);

	// 1
	myOutput_Digit[0] = new PatternCode(5, 1, '0');
	myOutput_Digit[1] = new PatternCode(7, 1, '0');

	// 2
	myOutput_Digit[2] = new PatternCode(4, 2, '0');
	myOutput_Digit[3] = new PatternCode(6, 2, '0');
	myOutput_Digit[4] = new PatternCode(8, 2, '0');

	// 3
	myOutput_Digit[5] = new PatternCode(3, 3, '0');
	myOutput_Digit[6] = new PatternCode(5, 3, '0');
	myOutput_Digit[7] = new PatternCode(7, 3, '0');
	myOutput_Digit[8] = new PatternCode(9, 3, '0');
	
	// Expression
	myOutput_Key[0] = new PatternCode(6, 1, 'a');

	myOutput_Key[1] = new PatternCode(5, 2, 'a');
	myOutput_Key[2] = new PatternCode(7, 2, 'a');

	myOutput_Key[3] = new PatternCode(4, 3, 'a');
	myOutput_Key[4] = new PatternCode(6, 3, 'a');
	myOutput_Key[5] = new PatternCode(8, 3, 'a');

	// Fixed
	myFixOutput[0] = new FixedPattern(13, 1);
	myFixOutput[1] = new FixedPattern(13, 2);
	myFixOutput[2] = new FixedPattern(13, 3);

	for (int i = 0; i < 9; i++) NumberDupliate[i] = i + 1;
}

CLP::~CLP()
{
	delete[] myOutput_Digit;
	for (int i = 0; i < 9; i++) { myOutput_Digit[i] = nullptr; }

	delete[] myOutput_Key;
	for (int i = 0; i < 5; i++) { myOutput_Key[i] = nullptr; }

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

			if (!SecureActive) break;
		}
	}
	else { SecureActive = false; }
}

void CLP::StoreNumber(int index, int* number)
{
	NumberDupliate[index] = *number;
}

void CLP::UpdateInput(int x, int y)
{
	// Get Input of pattern code (Number)
	for (int i = 0; i < 9; i++)
	{
		if (x == myOutput_Digit[i]->Get_X() && y == myOutput_Digit[i]->Get_Y())
		{
			myOutput_Digit[i]->ChangeValue();
			if (i < 9) NumberDupliate[i] = myOutput_Digit[i]->GetOutputIndexValue();
			break;
		}
	}

	// Get Input of pattern code (Expression)
	for (int i = 0; i < 6; i++)
	{
		if (x == myOutput_Key[i]->Get_X() && y == myOutput_Key[i]->Get_Y())
		{
			myOutput_Key[i]->ChangeValue();
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
			closeTextField[i]->CloseButton(SecureActive);
		}
	}
}

int CLP::GetUnitOutput(int index)
{
	int patternCode1_num = 0;
	int patternCode2_num = 0;
	int patternCode3_num = 0;

	// PattternCode_1
	switch (myOutput_Key[0]->GetOutputValue())
	{
		case '+':
			patternCode1_num = myOutput_Digit[0]->GetOutputIndexValue() + myOutput_Digit[1]->GetOutputIndexValue();
			break;

		case '-':
			patternCode1_num = myOutput_Digit[0]->GetOutputIndexValue() - myOutput_Digit[1]->GetOutputIndexValue();
			break;

		case '/':
			patternCode1_num = myOutput_Digit[0]->GetOutputIndexValue() / myOutput_Digit[1]->GetOutputIndexValue();
			break;

		case 'X':
			patternCode1_num = myOutput_Digit[0]->GetOutputIndexValue() * myOutput_Digit[1]->GetOutputIndexValue();
			break;
	}

	// PatternCode_2
	switch (myOutput_Key[1]->GetOutputValue())
	{
	case '+':
		patternCode2_num = myOutput_Digit[2]->GetOutputIndexValue() + myOutput_Digit[3]->GetOutputIndexValue();
		break;

	case '-':
		patternCode2_num = myOutput_Digit[2]->GetOutputIndexValue() - myOutput_Digit[3]->GetOutputIndexValue();
		break;

	case '/':
		patternCode2_num = myOutput_Digit[2]->GetOutputIndexValue() / myOutput_Digit[3]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode2_num = myOutput_Digit[2]->GetOutputIndexValue() * myOutput_Digit[3]->GetOutputIndexValue();
		break;
	}

	switch (myOutput_Key[2]->GetOutputValue())
	{
	case '+':
		patternCode2_num += myOutput_Digit[4]->GetOutputIndexValue();
		break;

	case '-':
		patternCode2_num -= myOutput_Digit[4]->GetOutputIndexValue();
		break;

	case '/':
		patternCode2_num /= myOutput_Digit[4]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode2_num *= myOutput_Digit[4]->GetOutputIndexValue();
		break;
	}

	// PatternCode_3
	switch (myOutput_Key[3]->GetOutputValue())
	{
	case '+':
		patternCode3_num = myOutput_Digit[5]->GetOutputIndexValue() + myOutput_Digit[6]->GetOutputIndexValue();
		break;

	case '-':
		patternCode3_num = myOutput_Digit[5]->GetOutputIndexValue() - myOutput_Digit[6]->GetOutputIndexValue();
		break;

	case '/':
		patternCode3_num = myOutput_Digit[5]->GetOutputIndexValue() / myOutput_Digit[6]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode3_num = myOutput_Digit[5]->GetOutputIndexValue() * myOutput_Digit[6]->GetOutputIndexValue();
		break;
	}

	switch (myOutput_Key[4]->GetOutputValue())
	{
	case '+':
		patternCode3_num += myOutput_Digit[7]->GetOutputIndexValue();
		break;

	case '-':
		patternCode3_num -= myOutput_Digit[7]->GetOutputIndexValue();
		break;

	case '/':
		patternCode3_num /= myOutput_Digit[7]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode3_num *= myOutput_Digit[7]->GetOutputIndexValue();
		break;
	}

	switch (myOutput_Key[5]->GetOutputValue())
	{
	case '+':
		patternCode3_num += myOutput_Digit[8]->GetOutputIndexValue();
		break;

	case '-':
		patternCode3_num -= myOutput_Digit[8]->GetOutputIndexValue();
		break;

	case '/':
		patternCode3_num /= myOutput_Digit[8]->GetOutputIndexValue();
		break;

	case 'X':
		patternCode3_num *= myOutput_Digit[8]->GetOutputIndexValue();
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
	return myOutput_Digit[*index]->GetOutputIndexValue();
}

char CLP::GetOutput_Expression(int* index)
{
	return myOutput_Key[*index]->GetOutputValue();
}

int CLP::GetOutputFixed(int index)
{
	return myFixOutput[index]->GetNumberSlot();
}

bool CLP::CheckOnSecure()
{
	return SecureActive;
}