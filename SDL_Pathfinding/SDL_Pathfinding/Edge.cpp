#include "Edge.h"


Edge::Edge()
{
	weight = 0;
	to = nullptr;
	from = nullptr;
}

Edge::Edge(int w, Node *prev, Node *next): weight(w), from(prev), to(next)
{
}

Edge::~Edge()
{
}

Node* Edge::GetToNode()
{
	return to;
}

Node* Edge::GetFromNode()
{
	return from;
}

int Edge::GetWeight()
{
	return weight;
}

void Edge::SetWeight(int w)
{
	weight = w;
}
