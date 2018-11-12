#include "Graph.h"



Graph::Graph(std::vector<std::vector<int>> *terrain)
{
	//cell sizes:
	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;

	std::cout << num_cell_x << std::endl;
	std::cout << num_cell_y << std::endl;

	//initialize nodes:
	initNodesMap(terrain);

	//create connections:
	initEdgesMap(terrain);
}

void Graph::initNodesMap(std::vector<std::vector<int>> *terrain)
{
	//for (int i = 0; i < terrain->size(); i++)
	//{
	//	for (int j = 0; j < (*terrain)[i].size(); j++)//si poso '1' en comptes de 'i', peta
	//	//for (int j = 0; j < terrain->at(i).size(); j++)
	//	{
	//		nodesMap.insert(std::pair<std::pair<int, int>, Node*> (std::make_pair(i,j), new Node(i,j)));
	//	}
	//	//std::cout << i;//a la segona 'i', peta.
	//}

	for (int i = 0; i < num_cell_x; i++)//cols
	{
		for (int j = 0; j < num_cell_y; j++)//rows
		{
			nodesMap.insert(std::pair<std::pair<int, int>, Node*> (std::make_pair(i,j), new Node(i,j)));
		}
	}
	
}

void Graph::initEdgesMap(std::vector<std::vector<int>> *terrain)
{
	//for (int i = 0; i < terrain->size(); i++)
	//{
	//	for (int j = 0; j < (*terrain)[i].size(); j++)//si poso '1' en comptes de 'i', peta
	for (int i = 0; i < num_cell_x; i++)
	{
		for (int j = 0; j < num_cell_y; j++)
		{
			std::cout << i << " " << j << std::endl;
			if ((*terrain)[j][i] != 0)
			{
				
				//look for all other nodes behind it
				CheckAndConnectNeighborNodeMap(j, i, -1, -1, terrain);
				CheckAndConnectNeighborNodeMap(j,i, -1, 0, terrain);
				CheckAndConnectNeighborNodeMap(j,i, -1, 1, terrain);
				CheckAndConnectNeighborNodeMap(j,i, 0, -1, terrain);
				CheckAndConnectNeighborNodeMap(j,i, 0, 1, terrain);
				CheckAndConnectNeighborNodeMap(j,i, 1, -1, terrain);
				CheckAndConnectNeighborNodeMap(j,i, 1, 0, terrain);
				CheckAndConnectNeighborNodeMap(j,i, 1, 1, terrain);
			}
		}
	}
	std::cout << " end of init edges";
}

void Graph::CheckAndConnectNeighborNodeMap(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain)
{
	if ((i + ni) >= 0 && (i + ni) < num_cell_x && (j + nj) >= 0 && (j + nj) < num_cell_y)
	{
		int w = terrain->at(i + ni).at(j + nj);
		if (w != 0)
		{
			CreateConnection(nodesMap.at(std::make_pair(i, j)), nodesMap.at(std::make_pair(i + ni, j + nj)), w);
		}
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
	//std::cout << "hola";
}

//unused
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
					Node node = Node(i, j);
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

//unused
void Graph::CheckAndConnectNeighborArray2D(int i, int j, int ni, int nj, std::vector<std::vector<int>> *terrain)
{
	//int w = terrain[i + ni][j + nj];
	int w = (terrain->at(i + ni)).at(j + nj);
	if (w != 0)
	{
		if (&nodeArray2D[i + ni][j + nj] )
		{
			Node node = Node( i + ni, j + nj );
			nodeArray2D[i + ni][j + nj] = node;
		}
		CreateConnection(&nodeArray2D[i][j], &nodeArray2D[i+ni][j+nj], w);
	}
}