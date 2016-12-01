#include "puzzle.h"
#include "Searches.h"
#include "WaterJug.h"
#include <iostream>
#include <vector>


int main() 
{
	// Test run using Depth-First Search on 8-Puzzle
	std::cout << "Domain in use: " << "8-puzzle" << std::endl;
	Searches<puzzle> *dfs1 = new Searches<puzzle>();
	dfs1->DFS();
	delete dfs1;

	// Test run using Depth-First Search on Water Jug
	std::cout << "Domain in use: " << "Water Jug" << std::endl;
	Searches<WaterJug> *dfs2 = new Searches<WaterJug>();
	dfs2->DFS();
	delete dfs2;

	// Test run using Iterative-Deepening Depth-Limited Search on Water Jug
	std::cout << "Domain in use: " << "Water Jug" << std::endl;
	Searches<WaterJug> *ids2 = new Searches<WaterJug>();
	ids2->IDS();
	delete ids2;
}
