#include "Graph.h"



Graph::Graph(std::vector<std::vector<int>> *terrain)
{
	//initialize nodes:
	initNodesMap(terrain);

	//create connections:
	initEdgesMap(terrain);
}

void Graph::initNodeArray2D(std::vector<std::vector<int>> *terrain)
{
	nodeArray2D = new Node*[terrain->size()];
	for (int i = 0; i < terrain->size(); i++)
	{
		nodeArray2D[i] = new Node[terrain[i].size()];//<------------crashes here
	}

	for (int i = 0; i < terrain->size(); i++)//rows
	{
		for (int j = 0; j < terrain[i].size(); j++)//columns
		{
			if (&terrain[i][j] != 0)
			{
				if (nodeArray2D[i][j].row == -1 && nodeArray2D[i][j].column == -1)//create node if it doesn't exist
				{
					Graph::Node node = Graph::Node(i, j);
					nodeArray2D[i][j] = node;
				}

				//look for all other nodes behind it
				CheckAndConnectNeighborArray2D(i, j, -1, -1, terrain);
				CheckAndConnectNeighborArray2D(i, j, -1, 0, terrain);
				CheckAndConnectNeighborArray2D(i, j, -1, 1, terrain);
				CheckAndConnectNeighborArray2D(i, j, 0, -1, terrain);
				CheckAndConnectNeighborArray2D(i, j, 0, 1, terrain);
				CheckAndConnectNeighborArray2D(i, j, 1, -1, terrain);
				CheckAndConnectNeighborArray2D(i, j, 1, 0, terrain);
				CheckAndConnectNeighborArray2D(i, j, 1, 1, terrain);
			}
		}
	}
}

void Graph::initNodesMap(std::vector<std::vector<int>> *terrain)
{
	for (int i = 0; i < terrain->size(); i++)
	{
		for (int j = 0; j < terrain[i].size(); j++)
		//for (int j = 0; j < terrain->at(i).size(); j++)
		{
			nodesMap.insert(std::pair<std::pair<int, int>, Node*> (std::make_pair(i,j), new Node(i,j)));
		}
		std::cout << i;//a la segona 'i', peta.
	}
}

void Graph::initEdgesMap(std::vector<std::vector<int>> *terrain)
{
	for (int i = 0; i < terrain->size(); i++)//rows
	{
		for (int j = 0; j < terrain[i].size(); j++)//columns
		{
			if (&terrain[i][j] != 0)
			{
				//look for all other nodes behind it
				CheckAndConnectNeighborNodeMap(i, j, -1, -1, terrain);
				CheckAndConnectNeighborNodeMap(i, j, -1, 0, terrain);
				CheckAndConnectNeighborNodeMap(i, j, -1, 1, terrain);
				CheckAndConnectNeighborNodeMap(i, j, 0, -1, terrain);
				CheckAndConnectNeighborNodeMap(i, j, 0, 1, terrain);
				CheckAndConnectNeighborNodeMap(i, j, 1, -1, terrain);
				CheckAndConnectNeighborNodeMap(i, j, 1, 0, terrain);
				CheckAndConnectNeighborNodeMap(i, j, 1, 1, terrain);
			}
		}
	}
}

void Graph::CheckAndConnectNeighborNodeMap(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain)
{
	//int w = terrain[i + ni][j + nj];
	int w = (terrain->at(i + ni)).at(j + nj);
	if (w != 0)
	{
		CreateConnection(nodesMap.at(std::make_pair(i,j)), nodesMap.at(std::make_pair(i + ni, j + nj)), w);
	}
}

Graph::~Graph()
{
	//remove maps?¿
}

void Graph::CreateConnection(Node* node1, Node* node2, int weight = 1)
{
	node1->adjacencyList.push_back(node2);
	node2->adjacencyList.push_back(node1);
	edgesMap.emplace(std::make_pair(node1, node2), new Edge(node1, node2, weight));
}

void Graph::CheckAndConnectNeighborArray2D(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain)
{
	//int w = terrain[i + ni][j + nj];
	int w = (terrain->at(i + ni)).at(j + nj);
	if (w != 0)
	{
		if (&nodeArray2D[i + ni][j + nj] )
		{
			Graph::Node node = Graph::Node( i + ni, j + nj );
			nodeArray2D[i + ni][j + nj] = node;
		}
		CreateConnection(&nodeArray2D[i][j], &nodeArray2D[i+ni][j+nj], w);
	}
}
