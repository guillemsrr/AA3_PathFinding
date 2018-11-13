#include <vector>
#include <map>
#include "Nodo.h"
#include "Edge.h"

#pragma once
class Grafo
{
public:
	Grafo();
	~Grafo();

	std::map<Nodo, std::vector<Edge>> grafo;
};

