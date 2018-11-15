#include "PathFinding.h"



PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

std::map<Node*, Node*> PathFinding::BreadthFirstSearch( Node * start, Node * goal)
{
	std::queue<Node*> frontier;
	frontier.push(start);
	std::map<Node*, Node*> visited; //the key is the node, and the value is the node it comes from
	visited.emplace(start, nullptr);
	Node* current;

	while (!frontier.empty())
	{
		current = frontier.front();
		//std::cout << "current BFS: " << current->m_cell.x << " " << current->m_cell.y << std::endl;
		if (current == goal)
		{
			//early access
			return visited;
		}
		else
		{
			frontier.pop();
			for each (Node* n in current->adjacencyList)
			{
				//std::cout << "neighbor BFS: " << n->m_cell.x << " " << n->m_cell.y << std::endl;
				if (visited.find(n) == visited.end())
				{
					frontier.push(n);
					visited.emplace(n, current);
				}
			}
		}
	}
	return visited;
}

void PathFinding::Dijkstra(Graph * graph, Node * start, Node * goal)
{
}

void PathFinding::GreedyBestFirstSearch(Graph * graph, Node * start, Node * goal)
{
	std::cout << "Player: [" << start->m_cell.x << "," << start->m_cell.y << "]" << std::endl;
	std::cout << "Coin: [" << goal->m_cell.x << "," << goal->m_cell.y << "]" << std::endl;

	std::vector<Node*> frontera;
	std::priority_queue<std::pair<Node*, int>> frontier;
	frontera.push_back(start);
	std::map<Node*, Node*> visitados;
	Node* current;

	//Recorro todos los nodos para asignarles su heurística
	for (std::map<std::pair<int, int>, Node*>::iterator it=graph->nodesMap.begin(); it!=graph->nodesMap.end(); it++)
	{
		it->second->h = ComputeH(it->second, goal);
		//std::cout << "[" << it->first.first << "," << it->first.second << "]" << ComputeH(it->second, goal) << std::endl;
	}

	//Aplico algoritmo GBFS
	frontier.push(std::make_pair(start, 0));

	while (!frontier.empty())
	{
		current = frontier.top().first;

		if (current == goal)
		{
			//Early exit

		}

		for (int i = 0; i < current->adjacencyList.size(); i++)
		{
			if (visitados.count(current->adjacencyList[i]) <= 0)
			{
				frontier.push(std::make_pair(current->adjacencyList[i], current->adjacencyList[i]->h));
				visitados.emplace(current->adjacencyList[i], current);
			}
			
		}

	}


	std::cout << "Ya" << std::endl;

	
}

void PathFinding::A(Graph * graph, Node * start, Node * goal)
{
}

int PathFinding::ComputeH(Node * n, Node * goal)
{
	//Chebyshev
	int normalCost=1;
	int diagnoalCost = 1;

	int dx = abs(n->m_cell.x - goal->m_cell.x);
	int dy = abs(n->m_cell.y - goal->m_cell.y);

	return normalCost * (dy + dx) + (diagnoalCost - 2 * normalCost) * std::min(dy, dx);
}
