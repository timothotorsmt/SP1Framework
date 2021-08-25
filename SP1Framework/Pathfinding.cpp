#include <list>
#include "Pathfinding.h"
#include "Grid.h"
#include "Tile.h"
#include "Player.h"

using namespace std;

Pathfinding::Pathfinding()
{
}

Pathfinding::~Pathfinding()
{
}

void Pathfinding::drawGrid(std::string map_name)
{
	// 2D array of nodes
	nodes = new sNode[cols * rows];

	
	ifstream readfile(map_name);
	getline(readfile, locationName);

	for (int YDIM = 0; YDIM < rows; YDIM++)
	{
		for (int XDIM = 0; XDIM < cols; XDIM++)
		{
			nodes[YDIM * cols + XDIM].x = XDIM;
			nodes[YDIM * cols + XDIM].y = YDIM;
			nodes[YDIM * cols + XDIM].parent = nullptr;
			nodes[YDIM * cols + XDIM].hasVisited = false;

			if ((YDIM >= 2 && YDIM <= 12) && (XDIM >= 7 && XDIM <= 27))
			{
				char c;
				readfile >> c;
			
				if (c == '#')
				{
					nodes[YDIM * cols + XDIM].isWall = true;
				}
			}
			else
			{
				nodes[YDIM * cols + XDIM].isWall = true;
			}
			
		}
	}

	// connect nodes together
	for (int YDIM = 0; YDIM < rows; YDIM++)
	{
		for (int XDIM = 0; XDIM < cols; XDIM++)
		{
			if (YDIM > 0) // ensures no nodes are connected to anything past the top border
			{
				nodes[YDIM * cols + XDIM].vecNeighbours.push_back(&nodes[(YDIM - 1) * cols + (XDIM + 0)]);
			}
			if (YDIM < rows - 1) // ensures no nodes are connected to anything past the bottom border
			{
				nodes[YDIM * cols + XDIM].vecNeighbours.push_back(&nodes[(YDIM + 1) * cols + (XDIM + 0)]);
			}
			if (XDIM > 0) // ensures no nodes are connected to anything past the left border
			{
				nodes[YDIM * cols + XDIM].vecNeighbours.push_back(&nodes[(YDIM + 0) * cols + (XDIM - 1)]);
			}
			if (XDIM < cols - 1) // ensures no nodes are connected to anything past the right border
			{
				nodes[YDIM * cols + XDIM].vecNeighbours.push_back(&nodes[(YDIM + 0) * cols + (XDIM + 1)]);
			}
		}
	}
}

void Pathfinding::chooseStartEndNodes(int playerXPos, int playerYPos, int enemyXPos, int enemyYPos)
{
	startNode = &nodes[(enemyYPos) * cols + (enemyXPos)];
	endNode = &nodes[(playerYPos) * cols + (playerXPos)];
}

int Pathfinding::solve_AStar(void)
{
	// default state
	for (int YDIM = 0; YDIM < rows; YDIM++)
	{
		for (int XDIM = 0; XDIM < cols; XDIM++)
		{
			nodes[YDIM * cols + XDIM].hasVisited = false;
			nodes[YDIM * cols + XDIM].globalGoal = INFINITY;
			nodes[YDIM * cols + XDIM].localGoal = INFINITY;
			nodes[YDIM * cols + XDIM].parent = nullptr;
		}
	}

	auto distance = [](sNode* a, sNode* b)
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b)
	{
		return distance(a, b);
	};

	// Setup starting conditions
	sNode* currentNode = startNode;
	startNode->localGoal = 0.0f;
	startNode->globalGoal = heuristic(startNode, endNode);

	// Start node added to not tested list
	// Newly discovered nodes are added to this list as the algorithm goes on
	list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(startNode);

	while (!listNotTestedNodes.empty() && currentNode != endNode)// Find absolutely shortest path // && currentNode != endNode)
	{
		// Untested nodes sorted by lowest global goal first
		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->globalGoal < rhs->globalGoal; });

		// Remove already visited nodes
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->hasVisited)
		{
			listNotTestedNodes.pop_front();
		}

		// Stop testing if all nodes tested
		if (listNotTestedNodes.empty())
		{
			break;
		}

		currentNode = listNotTestedNodes.front();
		currentNode->hasVisited = true;

		// Check each of the neighbours of node
		for (auto neighbourNode : currentNode->vecNeighbours)
		{
			// add node to not tested list if node had not been visited and is not a wall
			if (!neighbourNode->hasVisited && neighbourNode->isWall == 0)
			{
				listNotTestedNodes.push_back(neighbourNode);
			}

			// Calculate the neighbours potential lowest parent distance
			float possibleLowerGoal = currentNode->localGoal + distance(currentNode, neighbourNode);

			// Update neighbour to use current node as path source and set distance scores
			// if pathing through node is a lower distance than current set distance
			if (possibleLowerGoal < neighbourNode->localGoal)
			{
				neighbourNode->parent = currentNode;
				neighbourNode->localGoal = possibleLowerGoal;

				// Update neighbour's score after new best path length found
				neighbourNode->globalGoal = neighbourNode->localGoal + heuristic(neighbourNode, endNode);
			}
		}
	}

	// List of nodes that make up the shortest path
	list<sNode*> listShortestPathNodes;
	sNode* moveNode = nullptr;

	// path from end node to start node
	sNode* p = endNode;
	while (p->parent != nullptr)
	{
		listShortestPathNodes.push_front(p);
		p = p->parent;
		moveNode = listShortestPathNodes.front();
	}

	if (moveNode != nullptr)
	{
		// enemy moves up
		if (moveNode->y == startNode->y - 1)
		{
			moveDirection = 1;
		}
		// enemy moves down
		else if (moveNode->y == startNode->y + 1)
		{
			moveDirection = 3;
		}
		// enemy moves left
		else if (moveNode->x == startNode->x - 1)
		{
			moveDirection = 2;
		}
		// enemy moves right
		else if (moveNode->x == startNode->x + 1)
		{
			moveDirection = 4;
		}
		else
		{
			moveDirection = 0;
		}
		return moveDirection;
	}
	return 0;
}
