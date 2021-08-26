#include "Map.h"

//constructor for map
Map::Map()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::string roomNo = "";
			roomNo += std::to_string(i);
			roomNo += std::to_string(j);
			level_map[i][j].setRoomPos(roomNo);
			level_map[i][j].setDoorConfig();
			minmap[i][j] = ' ';
		}
	}
	is_stolen = false;
	minmap[0][0] = 'J';
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

bool Map::check_is_stolen(Player& player)
{
	is_stolen = (player.isJewelCaptured() == true) ? (true) : (false);
	return is_stolen;
}

std::string Map::getObjective()
{
	if (is_stolen == false) {
		return "Steal the jewel";
	}
	else {
		return "Escape!";
	}
}

void Map::update_minmap_char(Player& player)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			minmap[i][j] = ' ';
		}
	}
	if (true) {
		minmap[0][0] = 'J';
	}
	minmap[player.getRoomPos('y')][player.getRoomPos('x')] = 'X';
}

void Map::distributerandomfiles()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!(i == 0 && j == 0) || !(i == 3 && j == 3)) {
				int randNum = std::rand() % (filenames.size());
				level_map[i][j].importGrid(filenames[randNum]);
			}
		}
	}
	level_map[0][0].importGrid("jewelroom.txt");
	level_map[3][3].importGrid("spawn.txt");
}

void Map::generateNewMap()
{
	distributerandomfiles();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::string roomNo = "";
			roomNo += std::to_string(i);
			roomNo += std::to_string(j);
			level_map[i][j].setRoomPos(roomNo);
			level_map[i][j].setDoorConfig();
			minmap[i][j] = ' ';
		}
	}
}
