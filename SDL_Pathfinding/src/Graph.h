#pragma once
#include <vector>
#include <map>
#include "Edge.h"
#include "Graph.h"
#include "Node.h"


class Graph
{
public:
	Graph();
	~Graph();
	Graph(std::vector<std::vector<int>> *terrain);

private:
	std::map<Node*, std::vector<Edge*>> _map;
};

