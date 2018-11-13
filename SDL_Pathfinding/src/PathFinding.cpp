#include "PathFinding.h"



PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::BreathFirstSearch(Grafo * g)
{
	std::map< Nodo*, std::vector<Edge*>>::iterator it = g->mapa.begin();
	std::cout << it->first << std::endl;
}
