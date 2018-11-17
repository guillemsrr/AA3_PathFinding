#include "PathFinding.h"


struct Order {
	bool operator()(const std::pair<Node*, int> a, const std::pair<Node*, int> b) const
	{
		return a.second > b.second;
	}
};

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

std::map<Node*, std::pair<Node*, int>> PathFinding::Dijkstra(Graph *graph, Node *start, Node *goal)
{
	std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, Order> frontier;
	std::map<Node*, std::pair<Node*, int>> cameFrom;

	frontier.push(std::make_pair(start, 0));
	cameFrom[start] = std::make_pair(nullptr, NULL);

	Node *current;

	while (!frontier.empty())
	{
		current = frontier.top().first;

		if (current == goal)
		{
			//Goal
			return cameFrom;
		}
		else 
		{
			frontier.pop();
			for each(Node *next in current->adjacencyList)
			{
				int newCost = cameFrom[current].second + graph->edgesMap[std::make_pair(current, next)]->weight;
				if (cameFrom.count(next) == 0 || newCost < cameFrom[next].second)
				{
					cameFrom[next].second = newCost;
					frontier.push(std::make_pair(next, newCost));
					cameFrom[next].first = current;
				}
			}
		}
	}
	return cameFrom;
}

std::map<Node*, Node*> PathFinding::DijkstraV2(Graph * graph, Node * start, Node * goal)
{
	std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, Order> frontier;
	std::map<Node*, Node*> cameFrom;
	std::map<Node*, int> costSoFar;

	frontier.push(std::make_pair(start, 0));
	cameFrom[start] = nullptr;
	costSoFar[start] = 0;

	Node *current;

	while (!frontier.empty())
	{
		current = frontier.top().first;

		if (current == goal)
		{
			//Goal
			return cameFrom;
		}
		else
		{
			frontier.pop();
			for each(Node *next in current->adjacencyList)
			{
				int newCost = costSoFar[current] + graph->edgesMap[std::make_pair(current, next)]->weight;
				if (costSoFar.count(next) == 0 || newCost < costSoFar[next])
				{
					costSoFar[next] = newCost;
					frontier.push(std::make_pair(next, newCost));
					cameFrom[next] = current;
				}
			}
		}
	}
	return cameFrom;
}

std::map<Node*, Node*> PathFinding::GreedyBestFirstSearch(Graph * graph, Node * start, Node * goal)
{
	//std::cout << "Player: [" << start->m_cell.x << "," << start->m_cell.y << "]" << std::endl;
	//std::cout << "Coin: [" << goal->m_cell.x << "," << goal->m_cell.y << "]" << std::endl;

	//std::vector<Node*> frontera;
	std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, Order> frontier2;
	//std::priority_queue<std::pair<Node*, int>> frontier;
	//frontera.push_back(start);
	std::map<Node*, Node*> visitados;
	Node* current;

	//Recorro todos los nodos para asignarles su heur�stica
	for (std::map<std::pair<int, int>, Node*>::iterator it=graph->nodesMap.begin(); it!=graph->nodesMap.end(); it++)
	{
		it->second->h = ComputeH(it->second, goal);
		//std::cout << "[" << it->first.first << "," << it->first.second << "]" << ComputeH(it->second, goal) << std::endl;
	}

	//Aplico algoritmo GBFS
	frontier2.push(std::make_pair(start, 0));

	while (!frontier2.empty())
	{
		current = frontier2.top().first;

		if (current == goal)
		{
			//Early exit
			return visitados;
		}
		else
		{
			frontier2.pop();
			for (int i = 0; i < current->adjacencyList.size(); i++)
			{
				if (visitados.count(current->adjacencyList[i]) <= 0)
				{
					frontier2.push(std::make_pair(current->adjacencyList[i], current->adjacencyList[i]->h));
					//visitados.emplace(current->adjacencyList[i], current);
					visitados[current->adjacencyList[i]] = current;
				}
			}
		}
	}
	//std::cout << "Ya" << std::endl;
	return visitados;	
}

std::map<Node*, Node*> PathFinding::A(Graph * graph, Node * start, Node * goal)
{
	std::map<Node*, Node*> visited;

	return visited;
}

std::map<Node*, Node*> PathFinding::VisitedByDijkstra(std::map<Node*, std::pair<Node*, int>> d)
{
	std::map<Node*, Node*> visited;

	for (auto it = d.begin(); it != d.end(); it++)
	{
		visited[it->first] = it->second.first;
	}
	return visited;
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
