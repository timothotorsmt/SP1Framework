#pragma once
class PatternCode
{
private:
	static int PatternCodeCreated;

	char ExpressionOutput[4];
	char PatternType;

	int Placement_X;
	int Placement_Y;

	int valueIndex;
	char OutputValue;

public:
	PatternCode(int x, int y, char T);
	~PatternCode();

	void ChangeValue();

	char GetPatternType();
	int Get_X();
	int Get_Y();
	char GetOutputValue();
	int GetOutputIndexValue();

	static int GetTotalPatternCode();
};

