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
	is_stolen = (player.CheckOnJewel() == true) ? (true) : (false);
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

void Map::update_minmap_char(Player& player)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			minmap[i][j] = ' ';
		}
	}
	if (player.CheckOnJewel() == true) {
		minmap[0][0] = 'J';
	}
	minmap[player.getRoomPos('y')][player.getRoomPos('x')] = 'X';

void Map::distributerandomfiles()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!(i == 0 && j == 0) || !(i == 3 && j == 3)) {
				int randNum = std::rand() % filenames.size();
				level_map[i][j].importGrid(filenames[randNum]);
			}
		}
	}
	level_map[0][0].importGrid("jewelroom.txt");
	level_map[3][3].importGrid("spawn.txt");
}
