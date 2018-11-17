#include "Node.h"



Node::Node()
{
	m_cell = (-1, -1);
	h = 0;
}


Node::Node(Vector2D cell)
{
	m_cell = cell;
	h = 0;
};

Node::~Node()
{
}
