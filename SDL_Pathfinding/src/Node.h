#pragma once
#include <vector>
#include "Vector2D.h"

class Node
{
public:
	Node();
	Node(Vector2D cell);
	~Node();
	Vector2D m_cell;
	std::vector<Node*> adjacencyList;
	int h;
};

