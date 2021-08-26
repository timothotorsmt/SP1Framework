#include "Tile.h"
#include "Colours.h"

Tile::Tile()
{
	tileCharacter = ' ';
	tilePos.setCoordinates(0, 0, true);
	canBeSeen = true;
	tile_color = 0xff;
}

Tile::~Tile()
{
}

Position Tile::get_tile_pos()
{
	return tilePos;
}

char Tile::get_tile_char()
{
	return tileCharacter;
}

bool Tile::get_is_wall()
{
	return (tileCharacter == '#') ? (true) : (false);
}

bool Tile::get_is_occupied()
{
	return (tileCharacter == ' ') ? (false) : (true);
}

WORD Tile::get_tile_color()
{
	return tile_color;
}

void Tile::set_tile_char(char c)
{
	tileCharacter = c;
}

void Tile::set_tile_color(WORD char_attribute)
{
	tile_color = char_attribute;
}

void Tile::set_canBeSeen(bool b)
{
	canBeSeen = b;
}

void Tile::set_tile_color()
{
	switch (tileCharacter)
	{
	case ('#'):
		tile_color = COLOURS::GREY;
		break;
	case ('.'):
		tile_color = COLOURS::WHITE;
		break;
	case ('M'):
		tile_color = COLOURS::GREEN;
		break;
	case ('J'):
		tile_color = COLOURS::DARKGOLD;
		break;
	case ('-'):
		tile_color = COLOURS::BLUE;
		break;
	default:
		break;
	}
}
