#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	if (!leaderboard.empty()) {
		resetLeaderboard();
	}
	importLeaderboard();
}

Leaderboard::~Leaderboard()
{
	exportLeaderboard();
	for (unsigned int i = 0; i < leaderboard.size(); i++) {
		leaderboard.pop_back();
	}
}

bool Leaderboard::find_name_exists(std::string name)
{
	for (unsigned int i = 0; i < leaderboard.size(); i++) {
		if (leaderboard[i].second == name) {
			return true;
		}
	}
	return false;
}

int Leaderboard::getSize()
{
	return leaderboard.size();
}

void Leaderboard::add_new_score(std::string name, int score)
{
	leaderboard.push_back(std::make_pair(score, name));
	std::sort(leaderboard.begin(), leaderboard.end());
	std::reverse(leaderboard.begin(), leaderboard.end());
	exportLeaderboard();
}

void Leaderboard::resetLeaderboard()
{
	for (unsigned int i = 0; i < leaderboard.size(); i++) {
		leaderboard.pop_back();
	}
}

void Leaderboard::importLeaderboard()
{
	std::ifstream ReadFile("leaderboard.txt");
	while (!ReadFile.eof()) {
		std::string playerId;
		int score;
		ReadFile >> playerId >> score;
		//add score into leaderboard
		leaderboard.push_back(std::make_pair(score, playerId));
	}
	leaderboard.pop_back();
	ReadFile.close();
	//sort leaderboard
	std::sort(leaderboard.begin(), leaderboard.end());
	std::reverse(leaderboard.begin(), leaderboard.end());
}

void Leaderboard::exportLeaderboard()
{
	std::ofstream writeFile;
	writeFile.open("leaderboard.txt");
	for (unsigned int i = 0; i < leaderboard.size(); i++) {
		writeFile << leaderboard[i].second << " " << leaderboard[i].first << " ";
	}
	writeFile.close();
}

void Leaderboard::printLeaderboard(Console& g_Console, unsigned int i)
{
	COORD c;
	c.X = ((g_Console.getConsoleSize().X / 2) - 10);
	if (leaderboard.size() < 10) {
		for (unsigned int j = 0; j < leaderboard.size(); j++) {
			c.Y = 8 + j;
			std::string outputStr = std::to_string(j + 1) + ".  " + leaderboard[j].second + "       " + std::to_string(leaderboard[j].first);
			g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
		}
	}
	else {
		if ((i + 10) > leaderboard.size()) {
			i = leaderboard.size() - 10;
		}
		for (unsigned int j = i; j < (i + 10); j++) {
			c.Y = 8 + (j - i);
			std::string outputStr = std::to_string(j + 1) + ".  " + leaderboard[j].second + "       " + std::to_string(leaderboard[j].first);
			g_Console.writeToBuffer(c, outputStr, BACKMATCHTEXT);
		}
	}
}
