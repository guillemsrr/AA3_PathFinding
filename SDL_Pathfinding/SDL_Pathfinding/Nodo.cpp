#include "Nodo.h"



Nodo::Nodo()
{
}

Nodo::Nodo(int posx, int posy, int h, std::vector<Nodo*> a)
{
	x = posx;
	y = posy;
	heuristica = h;
	adyacentes = a;
}


Nodo::~Nodo()
{
	for (int i = 0; i < adyacentes.size(); i++)
	{
		adyacentes[i] = nullptr;
	}
}
