#include "Grid.h"
#include "Colours.h"

//construct grid
Grid::Grid() : room_pos("--"), name("")
{
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 35; i++) {
			gridMap[j][i].get_tile_pos().setCoordinates(j, i, true);
			gridMap[j][i].set_tile_char('#');
			gridMap[j][i].set_tile_color();
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 21; j++) {
			gridMap[2 + i][7 + j].set_tile_char(' ');
			gridMap[2 + i][7 + j].set_tile_color();

		}
	}
}

Grid::~Grid()
{
}

std::string Grid::getName()
{
	return name;
}

std::string Grid::getRoomPos()
{
	return room_pos;
}

Tile Grid::getTile(int x, int y)
{
	return gridMap[y][x];
}

int Grid::getDoorConfig(int i)
{
	return doorConfig[i];
}

void Grid::setName(std::string s)
{
	name = s;
}

void Grid::setDoorConfig(int i)
{
	doorConfig.set(i);
}

void Grid::setDoorConfig()
{
	//sets bitset to 1111
	doorConfig.set();
	//changes some of the bits to 0
	if (room_pos[0] == '0') {
		doorConfig.reset(0);
	}
	if (room_pos[0] == '3') {
		doorConfig.reset(1);
	}
	if (room_pos[1] == '0') {
		doorConfig.reset(2);
	}
	if (room_pos[1] == '3') {
		doorConfig.reset(3);
	}

	//top door
	if (doorConfig[0] == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				gridMap[j][15 + i].set_tile_char('.');
				gridMap[j][15 + i].set_tile_color();
			}
		}
	}
	//bottom door
	if (doorConfig[1] == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				gridMap[13 + j][15 + i].set_tile_char('.');
				gridMap[13 + j][15 + i].set_tile_color();
			}
		}
	}
	//left door
	if (doorConfig[2] == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				gridMap[i + 6][j].set_tile_char('.');
				gridMap[i + 6][j].set_tile_color();
			}
		}
	}
	//right door
	if (doorConfig[3] == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				gridMap[i + 6][j + 28].set_tile_char('.');
				gridMap[i + 6][j + 28].set_tile_color();


			}
		}
	}
}

void Grid::setRoomPos(std::string s)
{
	room_pos = s;
}

void Grid::importGrid(std::string file_name)
{
	std::ifstream readfile(file_name);
	std::getline(readfile, name);
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 21; j++) {
			char c;
			readfile >> c;
			if (c == 'M') {
				//add money as a variable entity 
			}
			gridMap[2 + i][7 + j].set_tile_char(c);
			gridMap[2 + i][7 + j].set_tile_color();
		}
	}

	readfile.close();
}
