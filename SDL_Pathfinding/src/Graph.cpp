#include "Graph.h"



Graph::Graph(std::vector<std::vector<int>> *terrain)
{
	//cell sizes:
	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;

	//std::cout << "num_cell_x: " << num_cell_x << std::endl;
	//std::cout << "num_cell_y: " << num_cell_y << std::endl;

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
	for (int row = 0; row < num_cell_y; row++)
	{
		for (int col = 0; col < num_cell_x; col++)
		{
			//std::cout << (*terrain)[row][col] << " ";
			//std::cout << "["<<row<<", "<<col<<"] = "<<(*terrain)[row][col] << "  ";
			//std::cout << "["<<row<<", "<<col<<"]  ";

			if((*terrain)[row][col]!=0)
				nodesMap.emplace(std::make_pair(row, col), new Node(Vector2D(col, row)));
		}
		//std::cout << std::endl << std::endl;
	}
}

void Graph::initEdgesMap(std::vector<std::vector<int>> *terrain)
{
	for (int row = 0; row < num_cell_y; row++)
	{
		for (int col = 0; col < num_cell_x; col++)
		{
			//std::cout << row << " " << col << std::endl;
			if ((*terrain)[row][col] != 0)
			{
				//look for all other nodes next to it
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
std::vector<Node*> Graph::GetShortestPath(std::map<Node*, Node*> visited, Node* goal)
{
	Node* comes_from = goal;
	std::vector<Node*> shortestPath;
	while (comes_from != nullptr)
	{
		shortestPath.push_back(comes_from);
		comes_from = visited.at(comes_from);
	}

	return shortestPath;
}