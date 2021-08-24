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
	// change node array to be [15][35], and import grid from 
	// [2][7] to [2][27]
	// [12][7] to [12][27]
	// border surrounding grid hard code to be walls to prevent enemy from going out of grid
	// leave enemy and player coordinates to be the same as before
		
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
			}
				/*if (c == '#')
				{
					nodes[YDIM * cols + XDIM].isWall = true;
				}
			}
			else
			{
				nodes[YDIM * cols + XDIM].isWall = true;
			}*/
			
		}
	}

	// hardcode wall collision
	for (int idx = 0; idx < 77; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[78].isWall = true;
	nodes[83].isWall = true;
	nodes[89].isWall = true;
	nodes[90].isWall = true;

	for (int idx = 98; idx < 112; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[113].isWall = true;
	nodes[114].isWall = true;
	nodes[115].isWall = true;
	nodes[116].isWall = true;
	nodes[118].isWall = true;
	nodes[120].isWall = true;
	nodes[121].isWall = true;
	nodes[123].isWall = true;
	nodes[124].isWall = true;
	nodes[125].isWall = true;
	nodes[127].isWall = true;
	nodes[128].isWall = true;
	nodes[130].isWall = true;
	nodes[131].isWall = true;
	nodes[132].isWall = true;

	for (int idx = 133; idx < 147; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[148].isWall = true;
	nodes[149].isWall = true;
	nodes[151].isWall = true;
	nodes[155].isWall = true;
	nodes[156].isWall = true;
	nodes[158].isWall = true;
	nodes[163].isWall = true;
	nodes[165].isWall = true;
	nodes[166].isWall = true;

	for (int idx = 168; idx < 182; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[188].isWall = true;
	nodes[191].isWall = true;
	nodes[195].isWall = true;
	nodes[196].isWall = true;
	nodes[198].isWall = true;
	nodes[201].isWall = true;

	for (int idx = 203; idx < 217; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[218].isWall = true;
	nodes[219].isWall = true;
	nodes[221].isWall = true;
	nodes[222].isWall = true;
	nodes[223].isWall = true;
	nodes[224].isWall = true;
	nodes[226].isWall = true;
	nodes[228].isWall = true;
	nodes[229].isWall = true;
	nodes[230].isWall = true;
	nodes[231].isWall = true;
	nodes[235].isWall = true;
	nodes[236].isWall = true;

	// middle line
	for (int idx = 238; idx < 252; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[254].isWall = true;
	nodes[256].isWall = true;
	nodes[268].isWall = true;
	nodes[270].isWall = true;

	for (int idx = 273; idx < 287; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[288].isWall = true;
	nodes[289].isWall = true;
	nodes[293].isWall = true;
	nodes[294].isWall = true;
	nodes[295].isWall = true;
	nodes[296].isWall = true;
	nodes[298].isWall = true;
	nodes[300].isWall = true;
	nodes[301].isWall = true;
	nodes[302].isWall = true;
	nodes[303].isWall = true;
	nodes[305].isWall = true;
	nodes[306].isWall = true;

	for (int idx = 308; idx < 322; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[323].isWall = true;
	nodes[326].isWall = true;
	nodes[328].isWall = true;
	nodes[329].isWall = true;
	nodes[333].isWall = true;
	nodes[336].isWall = true;

	for (int idx = 343; idx < 357; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[358].isWall = true;
	nodes[359].isWall = true;
	nodes[361].isWall = true;
	nodes[366].isWall = true;
	nodes[368].isWall = true;
	nodes[369].isWall = true;
	nodes[373].isWall = true;
	nodes[375].isWall = true;
	nodes[376].isWall = true;

	for (int idx = 378; idx < 392; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[392].isWall = true;
	nodes[393].isWall = true;
	nodes[394].isWall = true;
	nodes[396].isWall = true;
	nodes[397].isWall = true;
	nodes[399].isWall = true;
	nodes[400].isWall = true;
	nodes[401].isWall = true;
	nodes[403].isWall = true;
	nodes[404].isWall = true;
	nodes[406].isWall = true;
	nodes[408].isWall = true;
	nodes[410].isWall = true;
	nodes[411].isWall = true;
	nodes[412].isWall = true;

	for (int idx = 413; idx < 427; idx++)
	{
		nodes[idx].isWall = true;
	}
	nodes[434].isWall = true;
	nodes[435].isWall = true;
	nodes[441].isWall = true;

	for (int idx = 448; idx < 525; idx++)
	{
		nodes[idx].isWall = true;
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
	
}
