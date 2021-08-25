#pragma once
class CloseButtonField
{
private:
	static bool isCloseCalled;
	static int ButtonFieldCreated;

	int Placement_X;
	int Placement_Y;

public:
	CloseButtonField(int x, int y);
	~CloseButtonField();

	void CloseButton(bool active);
	static bool GetCloseCalled();

	int Get_X();
	int Get_Y();

	static int GetTotalButtonField();
};

