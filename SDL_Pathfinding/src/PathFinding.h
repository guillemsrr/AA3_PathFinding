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
	static std::map<Node*, std::pair<Node*, int>> Dijkstra(Graph *graph, Node* start, Node* goal);	//cameFrom and costSoFar in one map
	static std::map<Node*, Node*> DijkstraV2(Graph *graph, Node* start, Node* goal);	//cameFrom and costSoFar in different maps
	static std::map<Node*, Node*> GreedyBestFirstSearch(Graph* graph, Node* start, Node* goal);
	static std::map<Node*, Node*> A(Graph* graph, Node* start, Node* goal);

	static std::map<Node*, Node*> VisitedByDijkstra(std::map<Node*, std::pair<Node*, int>> d);
	static int ComputeH(Node* n, Node* goal);
};

