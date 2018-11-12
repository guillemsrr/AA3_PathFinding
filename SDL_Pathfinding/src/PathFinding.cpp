#include "PathFinding.h"



PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::BreadthFirstSearch(Graph * graph, Node * start, Node * goal)
{
	std::queue<Node*> frontier;
	frontier.push(start);
	std::set<Node*> visited;
	visited.insert(start);
	Node* current;

	while (!frontier.empty())
	{
		current = frontier.front();
		if (current == goal)
		{
			//found goal
		}
		else
		{
			frontier.pop();
			for each (Node* n in current->adjacencyList)
			{
				if (visited.find(n) != visited.end())
				{
					frontier.push(current);
					visited.insert(n);
				}
			}
		}
	}
}

void PathFinding::Dijkstra(Graph * graph, Node * start, Node * goal)
{
}

void PathFinding::GreedyBestFirstSearch(Graph * graph, Node * start, Node * goal)
{
}

void PathFinding::A(Graph * graph, Node * start, Node * goal)
{
}
