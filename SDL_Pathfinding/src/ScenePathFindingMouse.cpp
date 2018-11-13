#include "ScenePathFindingMouse.h"

using namespace std;

//Variables para crear el grafo
std::vector<Nodo*> listaNodos;
std::vector<Edge*> listaEdges;
Grafo* grafo=new Grafo();

bool loadGraphEx1 = false;
bool loadGraphEx2 = false;
bool loadGraphEx3 = false;
bool loadGraphEx4 = false;



ScenePathFindingMouse::ScenePathFindingMouse()
{
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze("../res/maze.csv");
	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setTarget(Vector2D(-20,-20));
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!isValidCell(rand_cell)) 
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3)) 
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));

}

ScenePathFindingMouse::~ScenePathFindingMouse()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFindingMouse::update(float dtime, SDL_Event *event)
{
	/*Exercise detection*/
	//std::cout << exercise;
	switch (exercise)
	{
		case 1:
			///BREATH FIRST-SEARCH

			//Inicializar el grafo
			if(!loadGraphEx1)
				loadGraph(exercise);
			
			//Set the variables de otros ejercicios
			loadGraphEx2 = false;
			loadGraphEx3 = false;
			loadGraphEx4 = false;

			//BREATH FIRST-SEARCH ALGORITHM FUNCTION
			PathFinding::BreathFirstSearch(grafo);

			break;
	}

	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (isValidCell(cell))
				agents[0]->addPathPoint(cell2pix(cell));
		}
		break;
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->SimplePathFollowing(agents[0], dtime);
	agents[0]->update(steering_force, dtime, event);

	// if we have arrived to the coin, replace it ina random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		coinPosition = Vector2D(-1, -1);
		while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition()))<3))
			coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	}
	
}

void ScenePathFindingMouse::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw();
}

const char* ScenePathFindingMouse::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFindingMouse::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < num_cell_y; j++)
	{
		for (int i = 0; i < num_cell_x; i++)
		{		
			//switch (terrain[j][i])
			//{
			//case 0:
			//	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
			//	break;
			//case 1: // Do not draw if it is not necessary (bg is already black)
			//	/*if ((i == 2) && (j == 2))
			//		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 153, 255, 102, 255);
			//	else
			//		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 255);*/


			//	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 255);
			//	break;
			//default:
			//	continue;
			//}

			if (terrain[j][i] == 0)
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
			}
			else
			{
				/*if ((i == 2) && (j == 2))
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 153, 255, 102, 255);
				else
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 255);*/


				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 255);
			}



			coords = cell2pix(Vector2D(i,j)) - Vector2D( (float)CELL_SIZE/2, (float)CELL_SIZE/2 );
			rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			//Alternative: render a tile texture:
			//SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), tile_textures[0], .... );
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void ScenePathFindingMouse::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void ScenePathFindingMouse::initMaze(char* filename)
{
	// Initialize the terrain matrix from file (for each cell a zero value indicates it's a wall, positive values indicate terrain cell cost)
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line))
	{
		vector<int> terrain_row;
		std::stringstream lineStream(line); 
		std::string cell;
		while (std::getline(lineStream, cell, ','))
			terrain_row.push_back(atoi(cell.c_str()));
		SDL_assert(terrain_row.size() == num_cell_x);
		terrain.push_back(terrain_row);
	}
	SDL_assert(terrain.size() == num_cell_y);
	infile.close();
}

bool ScenePathFindingMouse::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D ScenePathFindingMouse::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D ScenePathFindingMouse::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x/CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool ScenePathFindingMouse::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()) )
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x] == 0);
}


void ScenePathFindingMouse::loadGraph(int n)
{
	switch (n)
	{
		case 1:
			//Recojemos todos los nodos en una lista
			for (int i = 0; i < terrain.size(); i++)
			{
				for (int j = 0; j < terrain.size(); j++)
				{
					//std::cout << terrain[i][j];
					if (terrain[i][j] != 0)
					{
						Nodo* aux = new Nodo(i, j, 0);
						listaNodos.push_back(aux);
					}
				}
				//std::cout << std::endl;
			}

			//LLenamos el vector de adyacencia de cada nodo
			for (int i = 0; i < listaNodos.size(); i++)
			{
				std::vector<Nodo*> adj;
				for (int j = 0; j < listaNodos.size(); j++)
				{
					if (j != i)
					{
						//IZQUIERDA
						if ((listaNodos[j]->x == listaNodos[i]->x - 1) && (listaNodos[j]->y == listaNodos[i]->y))
						{
							adj.push_back(listaNodos[j]);
						}
						//IZQUIERDA-ARRIBA
						if ((listaNodos[j]->x == listaNodos[i]->x - 1) && (listaNodos[j]->y == listaNodos[i]->y-1))
						{
							adj.push_back(listaNodos[j]);
						}
						//IZQUIERDA-ABAJO
						if ((listaNodos[j]->x == listaNodos[i]->x - 1) && (listaNodos[j]->y == listaNodos[i]->y+1))
						{
							adj.push_back(listaNodos[j]);
						}
						//DERECHA
						if ((listaNodos[j]->x == listaNodos[i]->x + 1) && (listaNodos[j]->y == listaNodos[i]->y))
						{
							adj.push_back(listaNodos[j]);
						}
						//DERECHA-ARRIBA
						if ((listaNodos[j]->x == listaNodos[i]->x + 1) && (listaNodos[j]->y == listaNodos[i]->y-1))
						{
							adj.push_back(listaNodos[j]);
						}
						//DERECHA-ABAJO
						if ((listaNodos[j]->x == listaNodos[i]->x + 1) && (listaNodos[j]->y == listaNodos[i]->y+1))
						{
							adj.push_back(listaNodos[j]);
						}
						//ARRIBA
						if ((listaNodos[j]->y == listaNodos[i]->y - 1) && (listaNodos[j]->x == listaNodos[i]->x))
						{
							adj.push_back(listaNodos[j]);
						}
						//ABAJO
						if ((listaNodos[j]->y == listaNodos[i]->y + 1) && (listaNodos[j]->x == listaNodos[i]->x))
						{
							adj.push_back(listaNodos[j]);
						}

					}
				}
				listaNodos[i]->adyacentes = adj;
				adj.clear();
			}

			//Creamos los edges de todo el grafo
			for (int i = 0; i < listaNodos.size(); i++)
			{
				for (int j = 0; j < listaNodos[i]->adyacentes.size(); j++)
				{
					Edge* aux = new Edge(listaNodos[i], listaNodos[i]->adyacentes[j], 0);
					listaEdges.push_back(aux);
				}
			}

			//Creamos el grafo con su estructura correspondiente

			
			for (int i = 0; i < listaNodos.size(); i++)
			{
				std::vector<Edge*> aux;
				for (int j = 0; j < listaEdges.size(); j++)
				{
					if (listaEdges[j]->from == listaNodos[i])
					{
						aux.push_back(listaEdges[j]);
					}
				}
				grafo->mapa.insert(std::pair<Nodo*, std::vector<Edge*>>(listaNodos[i], aux));
				aux.clear();
			}
			//grafo->mapa.insert(std::pair< Nodo*, std::vector<Edge*>>());




			loadGraphEx1 = true;
			break;
	}

}
