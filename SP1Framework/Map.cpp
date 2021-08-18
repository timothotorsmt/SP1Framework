#include "Map.h"

Map::Map()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::string roomNo = "";
			roomNo += i;
			roomNo += j;
			level_map[i][j].setRoomPos(roomNo);
			level_map[i][j].setDoorConfig();
			minmap[i][j] = ' ';
		}
	}
	is_stolen = false;
	minmap[0][0] = 'J';
	isCurrentlyIn[0] = 3;
	isCurrentlyIn[1] = 3;
}

Map::~Map()
{
}

char Map::get_minmap_char(int x, int y)
{
	return minmap[y][x];
}

Grid Map::get_map_grid(int x, int y)
{
	return level_map[y][x];
}

bool Map::check_is_stolen()
{
	return is_stolen;
}

int Map::getCurrentBox(int i)
{
	return isCurrentlyIn[1];
}

std::string Map::getObjective()
{
	if (is_stolen == false) {
		return "Steal the jewel";
	}
	else {
		return "Escape the museum";
	}
}

void Map::update_minmap_char()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			minmap[i][j] = ' ';
		}
	}
	if (is_stolen == false) {
		minmap[0][0] = 'J';
	}
	minmap[isCurrentlyIn[0]][isCurrentlyIn[1]] = 'X';
}

void Map::moveBox(int direction)
{
	switch (direction) {
	case 1:
		isCurrentlyIn[0] -= 1;
		break;
	case 2:
		isCurrentlyIn[0] += 1;
		break;
	case 3:
		isCurrentlyIn[1] -= 1;
		break;
	case 4:
		isCurrentlyIn[1] += 1;
		break;
	default:
		break;
	}
}
