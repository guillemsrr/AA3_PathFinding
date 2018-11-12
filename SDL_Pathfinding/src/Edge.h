#pragma once
#include "Node.h"

class Edge
{
public:
	Edge();
	Edge(Node* f, Node* t, int w);
	~Edge();

	int weight = 1;
	Node* from_node;
	Node* to_node;
};

