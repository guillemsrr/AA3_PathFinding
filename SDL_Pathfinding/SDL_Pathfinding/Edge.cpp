#include "Edge.h"



Edge::Edge()
{
}

Edge::Edge(Nodo* f, Nodo* t, int p)
{
	from = f;
	to = t;
	peso = p;
}


Edge::~Edge()
{
	from = nullptr;
	to = nullptr;
}
