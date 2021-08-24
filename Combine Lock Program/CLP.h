#pragma once
#include "PatternCode.h"
#include "FixedPattern.h"
#include "CloseButtonField.h"

class CLP
{
private:
	bool SecureActive;
	int NumberDupliate[9];

	PatternCode* myOutput[15];
	FixedPattern* myFixOutput[3];
	CloseButtonField* closeTextField[10];

public:
	CLP();
	~CLP();

	bool CheckOnSecure();

	int GetOutput_Number(int* index);
	char GetOutput_Expression(int* index);
	int GetOutputFixed(int* index);

	void UpdateInput(int x, int y);
	void CheckStatus();
	void StoreNumber(int index, int number);

	int GetUnitOutput(int index);
};

