#include "Position.h"

Position::Position(int r, int c) : row(r), column(c)
{
}

Position::Position() : row(0), column(0)
{
}

Position::~Position()
{
}

int Position::getRow()
{
	return row;
}

int Position::getColumn()
{
	return column;
}

void Position::setCoordinates(int c, int r, bool set)
{
	if (set) {
		row = r;
		column = c;
	}
	else {
		row += r;
		column += c;
	}
}

bool Position::isEqualPos(Position otherPos)
{
	if (row != otherPos.getRow()) return false;
	if (column != otherPos.getColumn()) return false;
	return true;
}
