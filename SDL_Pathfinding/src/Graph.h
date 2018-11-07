#pragma once
#include <vector>
#include <map>
#include <iostream>

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
		};
	};
	class Edge
	{
	public:
		int weight=1;
		Node* from_node;
		Node* to_node;

		Edge()
		{
			weight = 1;
			from_node = nullptr;
			to_node = nullptr;
		}

		Edge(Node* f, Node* t, int w)
		{
			from_node = f;
			to_node = t;
			weight = w;
		}
	};

	//std::vector< std::vector<Graph::Node*> > nodesList;
	Node** nodeArray2D;
	std::map<std::pair<int, int>, Node*> nodesMap;
	std::map<std::pair<Node*, Node*>,Edge*> edgesMap;

	void initNodesMap(std::vector<std::vector<int>> *terrain);
	void initEdgesMap(std::vector<std::vector<int>> *terrain);
	void CheckAndConnectNeighborNodeMap(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain);

	void initNodeArray2D(std::vector<std::vector<int>> *terrain);
	void CheckAndConnectNeighborArray2D(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain);
	void CreateConnection(Node* node1, Node* node2, int weight);
};

