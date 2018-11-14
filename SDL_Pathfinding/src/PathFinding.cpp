#include "PathFinding.h"



PathFinding::PathFinding()
{
}


PathFinding::~PathFinding()
{
}

void PathFinding::BreathFirstSearch(Grafo * g, int agentX, int agentY, int coinX, int coinY)
{
	//std::cout << coinX << ",,,,," << coinY << std::endl;
	if (!BFSgotPath)
	{
		int startX = agentX;
		int startY = agentY;
		int objectiveX = coinX;
		int objectiveY = coinY;
		Nodo* current;

		std::cout << startX << " /// " << startY << std::endl;

		std::map<Nodo*, std::vector<Edge*>>::iterator it = g->mapa.begin();
		//std::cout << startX << " : " << startY << std::endl;
		while (it != g->mapa.end())
		{
			if (it->first->x == startX && it->first->y == startY)
			{
				//std::cout << "HOLA   "<< startX << " : " << it->first->x << startY << " : " << it->first->y << std::endl;
				fronteraBFS.push(it->first);
				break;
			}
			//std::cout << it->first->x << " : " << it->first->y << std::endl;
			it++;
		}

		//std::cout << fronteraBFS.front() << std::endl;
		//current = fronteraBFS.front();

		//Iteramos mientras no hayamos encontrado el nodo objetivo(EARLY EXIT)
		//while (!BFSgotPath)
		//{
		//	if (current->x == objectiveX && current->y == objectiveY)
		//	{
		//		std::cout << "Encontrada" << std::endl;
		//		BFSgotPath = true;
		//		break;
		//	}
		//	else
		//	{
		//		//Ponemos current en visitados
		//		visitadosBFS.push_back(current);
		//		//Expandimos la frontera nodo a nodo
		//		std::map<Nodo*, std::vector<Edge*>>::iterator it=g->mapa.find(current);
		//		for (int i = 0; i < it->second.size(); i++)
		//		{
		//			fronteraBFS.push(it->second[i]->to);
		//		}

		//		//Popeamos de la queue
		//		fronteraBFS.pop();

		//		//Ponemos el siguiente nodo de la cola en current
		//		current = fronteraBFS.front();


		//	}

		//}

		do
		{
			///1 -  Comprobar que el nodo que voy a visitar no haya sido visitado ya
			bool yaVisitado = false;
			for (int i = 0; i < visitadosBFS.size(); i++)
			{
				if (fronteraBFS.front() == visitadosBFS[i])
				{
					yaVisitado = true;
				}
			}

			///2 -  Si no ha sido visitado, lo visitamos y expandimos su frontera
			if (!yaVisitado)
			{
				///2.1 -  Asigno el nodo a current
				current = fronteraBFS.front();

				///2.2 -  Expandimos la frontera de current
				std::map<Nodo*, std::vector<Edge*>>::iterator it = g->mapa.find(current);
				for (int i = 0; i < it->second.size(); i++)
				{
					fronteraBFS.push(it->second[i]->to);
				}
				///2.3 -  Lo marcamos como visitado
				visitadosBFS.push_back(current);

				///2.4 -  Miramos si coincide con la posicion de la moneda
				if (current->x == coinX && current->y == coinY)
				{
					BFSgotPath = true;
				}
				///2.5 -  Si no es el objetivo popeamos la cola para seguir iterando
				else
				{
					fronteraBFS.pop();
				}
			}
			///3 -  Si ha sido visitado popeamos la cola
			else
			{
				fronteraBFS.pop();
			}

		} while (!BFSgotPath);


		//Pintamos en consola los nodos visitados
		for (int i = 0; i < visitadosBFS.size(); i++)
		{
			std::cout << "Nodo " << i << ": [" << visitadosBFS[i]->x << "," << visitadosBFS[i]->y << "]" << std::endl;
		}


		BFSgotPath = true;
	}
	
	std::cout << "YA ESTA" << std::endl;
}

