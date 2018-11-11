#include "Graph.h"
#include <iostream>

Graph::Graph()
{
}

Graph::~Graph()
{
}

Graph::Graph(std::vector<std::vector<int>> *terrain)
{
	for (int i = 0; i < terrain->size(); i++)
	{
		for (int j = 0; j < (*terrain)[i].size(); j++)
		{
			std::cout << " " << (*terrain)[i][j];
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < terrain->size(); i++)
	{
		for (int j = 0; j < (*terrain)[i].size(); j++)
		{
			std::cout << " " << (*terrain)[i][j];
			_map[new Node(i, j, 0)] = std::vector<Edge*>{ new Edge(), new Edge(), new Edge(), new Edge() };
		}
		std::cout << std::endl;
	}
}
