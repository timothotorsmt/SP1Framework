#pragma once
#include <string>
#include <iostream>
#include <bitset>
#include "Tile.h"
class Grid
{
private:
	Tile gridMap[15][35];
	std::bitset<4> doorConfig;
	std::string name;
	std::string room_pos;
public:
	Grid();
	~Grid();

	//getters
	std::string getName();
	std::string getRoomPos();
	Tile getTile(int x, int y);
	int getDoorConfig(int i);

	//setters
	void setName(std::string s);
	void setDoorConfig(int i);
	void setDoorConfig();
	void setRoomPos(std::string s);

	//others
	void importGrid(std::string fileName);
};
