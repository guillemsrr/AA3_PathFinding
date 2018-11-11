#pragma once
#include "Edge.h"
#include <vector>


class Edge;

class Node
{
public:
	Node();
	Node(int r, int c, int h);
	~Node();

	//std::vector<Edge> GetEdges();

	int GetHeuristic();
	void SetHeuristic(int h);

	std::vector<int> GetCoordinates();
	void SetCoordinates(int r, int c);

private:
	int heuristic;
	//std::vector<Edge> edges;
	int row;
	int column;
};

