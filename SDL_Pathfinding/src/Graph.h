#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "SDL_SimpleApp.h"
#include "Node.h"
#include "Edge.h"
#include <algorithm>

class Graph
{
public:
	Graph(std::vector<std::vector<int>> *terrain);
	~Graph();

	int num_cell_x;
	int	num_cell_y;

	std::map<std::pair<int, int>, Node*> nodesMap;
	std::map<std::pair<Node*, Node*>,Edge*> edgesMap;

	static std::vector<Node*> GetShortestPath(std::map<Node*, Node*> visited, Node* goal);
	void CreateHeuristics(Node* goal);

private:
	void initNodesMap(std::vector<std::vector<int>> *terrain);
	void initEdgesMap(std::vector<std::vector<int>> *terrain);
	void CheckAndConnectNeighborNodeMap(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain);
	void CreateConnection(Node* node1, Node* node2, int weight);
	bool CheckNeighborExists(int i, int j);
	int Chebyshev(Node * n, Node * goal);
};

