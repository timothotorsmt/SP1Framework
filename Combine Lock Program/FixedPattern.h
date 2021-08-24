#pragma once
class FixedPattern
{
private:
	static int FixedPatternCreated;

	int NumberSlot;
	int indexValue;

	int Placement_X;
	int Placement_Y;

public:
	FixedPattern(int x, int y);
	~FixedPattern();

	void ChangeValue();
	int GetNumberSlot();
	
	int Get_X();
	int Get_Y();

	static int GetTotalFixedPattern();
};

