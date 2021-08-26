#pragma once
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Framework/console.h"
#define BACKMATCHTEXT (BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

class Leaderboard
{
private:
	std::vector<std::pair<int, std::string>> leaderboard;
public:
	Leaderboard();
	~Leaderboard();

	//getters
	bool find_name_exists(std::string name);
	int getSize();

	//setters
	void add_new_score(std::string name, int score);
	void resetLeaderboard();
	void importLeaderboard();
	void exportLeaderboard();

	//others 
	void printLeaderboard(Console& g_Console, unsigned int i);
};

