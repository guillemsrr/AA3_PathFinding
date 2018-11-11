#pragma once
#include "Node.h"


class Node;

class Edge
{
public:
	Edge();
	Edge(int w, Node *prev, Node *next);
	~Edge();

	Node* GetToNode();
	Node* GetFromNode();

	int GetWeight();
	void SetWeight(int w);

private:
	Node *to;
	Node *from;
	int weight;
};

