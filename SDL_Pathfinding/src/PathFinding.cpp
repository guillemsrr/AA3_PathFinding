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

// -------------------------------- ALEX -------------------------------------//
//BFS
void PathFinding::BreadthFirstSearch(Graph *graph, Node *start, Node *end)
{
	std::queue<Node*> frontier;
	std::map<Node*, Node*> cameFrom;

	Node* aux = nullptr;

	frontier.push(start);
	cameFrom[start] = aux;

	Node *current = nullptr;

	while (!frontier.empty())
	{
		current = frontier.front();

		if (current == end)
		{
			//Goal
			break;
		}

		std::vector<Edge*> neighbors = graph->m_graph[current];
		for (const auto &e : neighbors) 
		{
			Node *next = e->to_node;
			if (cameFrom.count(next) == 0) 
			{
				frontier.push(next);
				cameFrom[next] = current;
			}
		}
	}
}

//DIJKSTRA
void PathFinding::Dijkstra(Graph *graph, Node *start, Node *end) 
{
	std::priority_queue<std::pair<Node*, int>> frontier;
	std::map<Node*, std::pair<Node*, int>> cameFrom;

	Node* aux = nullptr;

	frontier.push(std::make_pair(start, 0));
	cameFrom[start] = std::make_pair(aux, 0);

	Node *current = nullptr;

	while (!frontier.empty)
	{
		//current = frontier.top;
		current = frontier.top->first;

		if (current == end) 
		{
			//Goal
			break;
		}

		std::vector<Edge*> neighbors = graph->m_graph[current];
		for (const auto &e : neighbors)
		{
			Node *next = e->to_node;
			//TODO
		}
	}
}
//----------------------------------------------------------------------------//

void PathFinding::Dijkstra(Graph * graph, Node * start, Node * goal)
{
}

void PathFinding::GreedyBestFirstSearch(Graph * graph, Node * start, Node * goal)
{
}

void PathFinding::A(Graph * graph, Node * start, Node * goal)
{
}
