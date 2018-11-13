#include <vector>

#pragma once
class Nodo
{
public:
	Nodo();
	Nodo(int, int, int);
	Nodo(int, int, int, std::vector<Nodo*>);
	~Nodo();

	int x;
	int y;
	int heuristica;

	std::vector<Nodo*> adyacentes;
};

