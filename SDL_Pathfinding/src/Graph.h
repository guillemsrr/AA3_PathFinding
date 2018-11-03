#pragma once
#include <vector>
#include <map>

class Graph
{
public:
	Graph(std::vector<std::vector<int>> *terrain);
	~Graph();

	struct Node
	{
		int row;
		int column;
		std::vector<Node*> adjacencyList;
	};
	struct Edge
	{
		int weight=1;
		Node* from_node;
		Node* to_node;
	};

	//std::vector< std::vector<Graph::Node*> > nodesList;
	Node*** nodesList;
	std::map<std::pair<Node*, Node*>,Edge*> edgesList;
	std::vector<Graph::Node*> empty;

	void CheckAndConnectNeighbor(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain);
	void CreateConnection(Node* node1, Node* node2, int weight);
};

