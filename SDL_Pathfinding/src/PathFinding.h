#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include "Grafo.h"

#pragma once
class PathFinding
{
public:
	PathFinding();
	~PathFinding();


	 std::queue<Nodo*> fronteraBFS;
	 std::vector<Nodo*> visitadosBFS;
	 bool BFSgotPath = false;

	 void BreathFirstSearch(Grafo* g, int agentX, int agentY, int coinX, int coinY);
	

};

