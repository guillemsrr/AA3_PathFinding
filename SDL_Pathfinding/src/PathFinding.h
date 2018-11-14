#pragma once
#include "Graph.h"
#include<queue>
#include <set>

class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	static std::map<Node*, Node*> BreadthFirstSearch( Node* start, Node* goal);
	static std::map<Node*, std::pair<Node*, int>> Dijkstra(Graph *graph, Node* start, Node* goal);
	static void GreedyBestFirstSearch(Graph* graph, Node* start, Node* goal);
	static void A(Graph* graph, Node* start, Node* goal);
};

