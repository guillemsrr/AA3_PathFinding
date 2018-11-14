#include "Node.h"



Node::Node()
{
	m_cell = (-1, -1);
}


Node::Node(Vector2D cell)
{
	m_cell = cell;
};

Node::~Node()
{
}
