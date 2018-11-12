#pragma once
#include "Graph.h"
#include<queue>
#include <set>

class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void BreadthFirstSearch(Graph* graph, Node* start, Node* goal);
	void Dijkstra(Graph* graph, Node* start, Node* goal);
	void GreedyBestFirstSearch(Graph* graph, Node* start, Node* goal);
	void A(Graph* graph, Node* start, Node* goal);
};

