#pragma once
#include <vector>
class Node
{
public:
	Node();
	Node(int r, int c);
	~Node();
	int row;
	int column;
	std::vector<Node*> adjacencyList;
};

