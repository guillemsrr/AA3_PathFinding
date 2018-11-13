#include "PathFinding.h"



PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::BreathFirstSearch(Grafo * g, int agentX, int agentY)
{
	int startX = agentX;
	int startY = agentY;

	std::map<Nodo*, std::vector<Edge*>>::iterator it = g->mapa.begin();

	while (it != g->mapa.end())
	{
		if (it->first->x == startX && it->first->y == startY)
		{
			fronteraBFS.push(it->first);
		}
	}
}

