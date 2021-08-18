#pragma once
class Position
{
private:
	int PosX;
	int PosY;
	char markLabel;

public:
	Position();
	~Position();

	const int GetPosX();
	const int GetPosY();
	const char GetMarker();

protected:
	void UpdatePosition(int x, int y, bool set);
	void SetMarker(char m);
};

