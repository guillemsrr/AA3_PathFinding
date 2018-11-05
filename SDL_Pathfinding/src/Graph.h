#pragma once
#include <vector>
#include <map>

class Graph
{
public:
	Graph(std::vector<std::vector<int>> *terrain);
	~Graph();

	class Node
	{
	public:
		int row;
		int column;
		std::vector<Node*> adjacencyList;

		Node()
		{
			row = -1;
			column = -1;
		};

		Node(int r, int c)
		{
			row = r;
			column = c;
			adjacencyList = empty;
		};
	};
	class Edge
	{
		int weight=1;
		Node* from_node;
		Node* to_node;
	};

	//std::vector< std::vector<Graph::Node*> > nodesList;
	Node** nodesList;
	std::map<std::pair<Node*, Node*>,Edge*> edgesList;
	static std::vector<Graph::Node*> empty;

	void CheckAndConnectNeighbor(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain);
	void CreateConnection(Node* node1, Node* node2, int weight);
};

