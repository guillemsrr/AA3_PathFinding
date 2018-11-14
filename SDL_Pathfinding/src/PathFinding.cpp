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

std::map<Node*, std::pair<Node*, int>> PathFinding::Dijkstra(Graph *graph, Node *start, Node *goal)
{
	std::priority_queue<std::pair<Node*, int>> frontier;
	std::map<Node*, std::pair<Node*, int>> cameFrom;

	frontier.push(std::make_pair(start, 0));
	cameFrom[start] = std::make_pair(nullptr, NULL);

	Node *current;

	while (!frontier.empty)
	{
		current = frontier.top->first;

		if (current == goal)
		{
			//Goal
			return cameFrom;
		}
		else 
		{
			for each(Node *next in current->adjacencyList)
			{
				int newCost = cameFrom[current].second + graph->edgesMap[std::make_pair(current, next)]->weight;
				if (cameFrom.count(next) == 0 || newCost < cameFrom[next].second)
				{
					//int priority = newCost;
					frontier.push(std::make_pair(next, newCost));
					cameFrom[next].first = current;
				}
			}
		}
	}
	return cameFrom;
}

void PathFinding::GreedyBestFirstSearch(Graph * graph, Node * start, Node * goal)
{
	std::cout << "Player: [" << start->m_cell.x << "," << start->m_cell.y << "]" << std::endl;
	std::cout << "Coin: [" << goal->m_cell.x << "," << goal->m_cell.y << "]" << std::endl;
}

void PathFinding::A(Graph * graph, Node * start, Node * goal)
{
}
