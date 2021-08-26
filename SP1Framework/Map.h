#pragma once
#include <array>
#include <iostream>
#include <vector>
#include <random>
#include "Grid.h"
#include "Player.h"
#include "Tile.h"

class Map
{
private:
	char minmap[4][4];
	Grid level_map[4][4];
	bool is_stolen;

	std::vector<std::string> filenames{ "Haute Couture Gallery.txt", "The Garden.txt", "The Prehistoric Exhibit.txt"};
public:
	Map();
	~Map();

	//getters
	char get_minmap_char(int x, int y);
	Grid get_map_grid(int x, int y);
	bool check_is_stolen(Player& player);
	std::string getObjective();

	//setters
	void update_minmap_char(Player& player);

	//others
	void distributerandomfiles();
	void generateNewMap();
};
