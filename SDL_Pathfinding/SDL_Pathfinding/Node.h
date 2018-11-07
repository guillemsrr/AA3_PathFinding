#pragma once
#include "Edge.h"
#include <vector>


class Node
{
public:
	Node();
	Node(int h, int r, int c);
	~Node();

	std::vector<Edge> GetEdges();

	int GetHeuristic();
	void SetHeuristic(int h);

	std::vector<int> GetCoordinates();
	void SetCoordinates(int r, int c);

private:
	int heuristic;
	std::vector<Edge> edges;
	int row;
	int column;
};

