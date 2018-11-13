#include "Nodo.h"

#pragma once
class Edge
{
public:
	Edge();
	Edge(Nodo*, Nodo*, int);
	~Edge();

	Nodo* from;
	Nodo* to;
	int peso;
};

