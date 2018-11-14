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
}

void PathFinding::A(Graph * graph, Node * start, Node * goal)
{
}
