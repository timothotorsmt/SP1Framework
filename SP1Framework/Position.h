#pragma once

//done by dennis wong
//edited by timothy
class Position
{
private:
	int row;
	int column;
public:
	Position(int r, int c);
	Position();
	~Position();

	//getters
	int getRow();
	int getColumn();

	//setters;
	void setCoordinates(int c, int r, bool set);

	//others
	bool isEqualPos(Position otherPos);
};

