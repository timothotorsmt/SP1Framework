#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Grid.h"
#include "Tile.h"
#include "Player.h"

using namespace std;

// done by jeremy
class Pathfinding
{
private:
	struct sNode
	{
		bool isWall = false;			// Is the node a wall?
		bool hasVisited = false;		// Has this node been visited before?
		float globalGoal{};				// Distance to goal
		float localGoal{};				// Distance to goal if alternative route taken
		int x{};						// Nodes x position in 2D space
		int y{};						// Nodes y position in 2D space
		vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent{};				// Node connecting to this node that offers shortest parent
	};

	sNode* nodes = nullptr;
	int cols = 35;
	int rows = 15;

	sNode* startNode = nullptr;
	sNode* endNode = nullptr;
	sNode* moveNode = nullptr;

	string locationName;

	int moveDirection{};

public:
	Pathfinding();
	~Pathfinding();
	
	void drawGrid(std::string map_name);

	void chooseStartEndNodes(int playerXPos, int playerYPos, int enemyXPos, int enemyYPos);
	
	int solve_AStar(void);
};
