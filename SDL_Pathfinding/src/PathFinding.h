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

	static void BreathFirstSearch(Grafo* g);

};

