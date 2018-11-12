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

Graph::~Graph()
{
	//remove maps?¿
}

void Graph::initNodesMap(std::vector<std::vector<int>> *terrain)
{
	for (int row = 0; row < num_cell_y; row++)//cols
	{
		for (int col = 0; col < num_cell_x; col++)//rows
		{
			nodesMap.insert(std::pair<std::pair<int, int>, Node*> (std::make_pair(row,col), new Node(row, col)));
		}
	}
}

void Graph::initEdgesMap(std::vector<std::vector<int>> *terrain)
{
	for (int row = 0; row < num_cell_y; row++)
	{
		for (int col = 0; col < num_cell_x; col++)
		{
			std::cout << row << " " << col << std::endl;
			if ((*terrain)[row][col] != 0)
			{
				
				//look for all other nodes behind it
				CheckAndConnectNeighborNodeMap(row, col, -1, -1, terrain);
				CheckAndConnectNeighborNodeMap(row, col, -1, 0, terrain);
				CheckAndConnectNeighborNodeMap(row, col, -1, 1, terrain);
				CheckAndConnectNeighborNodeMap(row, col, 0, -1, terrain);
				CheckAndConnectNeighborNodeMap(row, col, 0, 1, terrain);
				CheckAndConnectNeighborNodeMap(row, col, 1, -1, terrain);
				CheckAndConnectNeighborNodeMap(row, col, 1, 0, terrain);
				CheckAndConnectNeighborNodeMap(row, col, 1, 1, terrain);
			}
		}
	}
}

void Graph::CheckAndConnectNeighborNodeMap(int row, int col, int nRow, int nCol, std::vector<std::vector<int>> *terrain)
{
	if (CheckNeighborExists(row + nRow, col + nCol))
	{
		int w = terrain->at(row + nRow).at(col + nCol);
		if (w != 0)
		{
			CreateConnection(nodesMap.at(std::make_pair(row, col)), nodesMap.at(std::make_pair(row + nRow, col + nCol)), w);
		}
	}
}

bool Graph::CheckNeighborExists(int row, int col)
{
	if ((row >= 0 && row < num_cell_y) && (col >= 0 && col < num_cell_x))
		return true;
	return false;
}

void Graph::CreateConnection(Node* node1, Node* node2, int weight = 1)
{
	node1->adjacencyList.push_back(node2);
	node2->adjacencyList.push_back(node1);
	edgesMap.emplace(std::make_pair(node1, node2), new Edge(node1, node2, weight));
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