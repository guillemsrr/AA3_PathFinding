#include "Node.h"


Node::Node()
{
	heuristic = 0;
}

Node::Node(int h, int r, int c): heuristic(h), row(r), column(c)
{

}

Node::~Node()
{
}

std::vector<Edge> Node::GetEdges()
{
	return std::vector<Edge>();
}

int Node::GetHeuristic()
{
	return heuristic;
}

void Node::SetHeuristic(int h)
{
	heuristic = h;
}

std::vector<int> Node::GetCoordinates()
{
	return std::vector<int>(row, column);
}

void Node::SetCoordinates(int r, int c)
{
	row = r;
	column = c;
}
