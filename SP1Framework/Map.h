#pragma once
#include <bits/stdc++.h>
#include "Grid.h"
#include "Tile.h"
class Map
{
private:
	char minmap[4][4];
	Grid level_map[4][4];
	bool is_stolen;
	int isCurrentlyIn[2];
public:
	Map();
	~Map();

	//getters
	char get_minmap_char(int x, int y);
	Grid get_map_grid(int x, int y);
	bool check_is_stolen();
	int Map::getCurrentBox(int i);
	std::string getObjective();

	//setters
	void update_minmap_char();
	void moveBox(int direction);
};
