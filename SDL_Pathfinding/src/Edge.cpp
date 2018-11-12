#include "Edge.h"



Edge::Edge()
{
	weight = 1;
	from_node = nullptr;
	to_node = nullptr;
}

Edge::Edge(Node* f, Node* t, int w)
{
	from_node = f;
	to_node = t;
	weight = w;
}

Edge::~Edge()
{
}
