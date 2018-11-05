#include "Graph.h"



Graph::Graph(std::vector<std::vector<int>> *terrain)
{
	//initialize nodesList:
	nodesList = new Node*[terrain->size()];
	for (int i = 0; i < terrain->size(); ++i)
	{
		nodesList[i] = new Node[terrain[i].size()];
	}

	for (int i = 0; i < terrain->size(); i++)//rows
	{
		for (int j = 0; j < terrain[i].size(); j++)//columns
		{
			if (&terrain[i][j] != 0)
			{
				if (nodesList[i][j].row == -1 && nodesList[i][j].column == -1)//create node if it doesn't exist
				{
					Graph::Node node = Graph::Node( i,j);
					nodesList[i][j] = node;
				}

				//look for all other nodes behind it
				CheckAndConnectNeighbor(i, j, -1, -1, terrain);
				CheckAndConnectNeighbor(i, j, -1, 0, terrain);
				CheckAndConnectNeighbor(i, j, -1, 1, terrain);
				CheckAndConnectNeighbor(i, j, 0, -1, terrain);
				CheckAndConnectNeighbor(i, j, 0, 1, terrain);
				CheckAndConnectNeighbor(i, j, 1, -1, terrain);
				CheckAndConnectNeighbor(i, j, 1, 0, terrain);
				CheckAndConnectNeighbor(i, j, 1, 1, terrain);
			}
		}
	}
}


Graph::~Graph()
{
}

void Graph::CreateConnection(Node* node1, Node* node2, int weight = 1)
{
	node1->adjacencyList.push_back(node2);
	edgesList.emplace(std::make_pair(node1, node2), new Edge{weight, node1, node2});
}

void Graph::CheckAndConnectNeighbor(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain)
{
	//int w = terrain[i + ni][j + nj];
	int w = (terrain->at(i + ni)).at(j + nj);
	if (w != 0)
	{
		if (nodesList[i + ni][j + nj] )
		{
			Graph::Node *node = new Graph::Node{ i + ni,j + nj,empty };
			nodesList[i + ni][j + nj] = node;
		}
		CreateConnection(nodesList[i][j], nodesList[i+ni][j+nj], w);
	}
}
