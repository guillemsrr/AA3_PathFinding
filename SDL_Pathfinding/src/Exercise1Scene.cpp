#include "Exercise1Scene.h"


void Exercise1Scene::init()
{
	std::srand(2);//seed is set to 1
	system("cls");
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze("../res/maze.csv");
	loadTextures("../res/maze.png", "../res/coin.png");

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
}

Exercise1Scene::Exercise1Scene(int ex)
{
	init();
	exercise = ex;

	if (ex == 3 || ex== 5) //Dijkstra or A*
	{
		CreateSpecificWeights();
		//CreateRandomWeights();
	}

	//title
	GetAlghorithmTitle(ex);

	m_graph = new Graph(&terrain);

	//init statistics
	minVisited = 100000;
	maxVisited = 0;
	meanVisited = 0;
	numFindings = 0;

	CreatePathToCoin();
}

Exercise1Scene::~Exercise1Scene()
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

void Exercise1Scene::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	default:
		break;
	}

	if (numFindings < maxNumFindings) {

		Vector2D steering_force = agents[0]->Behavior()->SimplePathFollowing(agents[0], dtime);
		agents[0]->update(steering_force, dtime, event);

		// if we have arrived to the coin, replace it in a random cell!
		if ((agents[0]->getCurrentTargetIndex() == -1) && (pix2cell(agents[0]->getPosition()) == coinPosition))
		{
			coinPosition = Vector2D(-1, -1);
			while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3))
				coinPosition = Vector2D((float)(rand() % num_cell_y), (float)(rand() % num_cell_x));

			//compute new path
			CreatePathToCoin();
			numFindings++;

			PrintStatistics();
		}
	}
}


#pragma region GivenFunctions

void Exercise1Scene::draw()
{
	drawMaze();
	
	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	PaintVisitedNodes();
	drawCoin();
	agents[0]->draw();
}

const char* Exercise1Scene::getTitle()
{
	std::string title = "SDL Path Finding :: Exercise 1 ";
	//title.append(algorithmTitle);
	//return title.c_str();//no funciona
	return "SDL Path Finding :: Exercise 1 ";
}

void Exercise1Scene::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < num_cell_y; j++)
	{
		for (int i = 0; i < num_cell_x; i++)
		{
			switch (terrain[j][i])
			{
			case 0:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				break;
			default:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 100*terrain[j][i] - 100, 0, 0, 255);
				break;
			}

			coords = cell2pix(Vector2D(i, j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
			rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			//Alternative: render a tile texture:
			//SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), tile_textures[0], .... );
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );s
}

void Exercise1Scene::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void Exercise1Scene::initMaze(char* filename)
{
	// Initialize the terrain matrix from file (for each cell a zero value indicates it's a wall, positive values indicate terrain cell cost)
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line))
	{
		std::vector<int> terrain_row;
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

bool Exercise1Scene::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image)
	{
		std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image)
	{
		std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

Vector2D Exercise1Scene::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D Exercise1Scene::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool Exercise1Scene::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x] == 0);
}

#pragma endregion

void Exercise1Scene::CreateRandomWeights()
{
	for (int i = 0; i < num_cell_x; i++)//rows
	{
		for (int j = 0; j < num_cell_y; j++)//columns
		{
			if (terrain[j][i] == 1)
				terrain[j][i] = MIN_WEIGHT + rand() % (MAX_WEIGHT - MIN_WEIGHT + 1);
		}
	}
}

void Exercise1Scene::CreateSpecificWeights()
{
	terrain[num_cell_y/ 2][num_cell_x / 2] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 -1][num_cell_x / 2] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 +1][num_cell_x / 2] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 ][num_cell_x / 2 -1] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 ][num_cell_x / 2 +1] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 +1][num_cell_x / 2 +1] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 -1][num_cell_x / 2 -1] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 -1][num_cell_x / 2 +1] = MAX_WEIGHT;
	terrain[num_cell_y/ 2 +1][num_cell_x / 2 -1] = MAX_WEIGHT;
}

void Exercise1Scene::CreatePathToCoin()
{
	Vector2D agentCell = pix2cell(agents[0]->getPosition());
	Node* playerNode = m_graph->nodesMap.at(Cell2Pair(agentCell));
	coinNode = m_graph->nodesMap.at(Cell2Pair(coinPosition));
	
	std::map<Node*, Node*> visited;
	switch (exercise)
	{
	case 2:
		///BFS
		visited = PathFinding::BreadthFirstSearch(playerNode, coinNode);
		break;
	case 3:
		///DIJKSTRA
		visited = PathFinding::DijkstraV2(m_graph, playerNode, coinNode);
		break;
	case 4:
		///GBFS
		m_graph->CreateHeuristics(coinNode);
		visited = PathFinding::GreedyBestFirstSearch(m_graph, playerNode, coinNode);
		break;
	case 5:
		///A*
		m_graph->CreateHeuristics(coinNode);
		visited = PathFinding::A(m_graph, playerNode, coinNode);
		break;
	}

	numVisited = visited.size();
	visitedNodesPosition.clear();
	GetVisitedNodesPosition(visited);
	SetPath(visited);
}

std::pair<int, int> Exercise1Scene::Cell2Pair(Vector2D cell)
{
	//std::cout << "cell " << cell.x << " "<<cell.y << std::endl;
	return std::make_pair(cell.y, cell.x);
}

void Exercise1Scene::SetPath(std::map<Node*, Node*> visited)
{
	std::vector<Node*> shortestPath = Graph::GetShortestPath(visited, coinNode);

	for (std::vector<Node*>::reverse_iterator it = shortestPath.rbegin(); it != shortestPath.rend(); ++it)
	{
		agents[0]->addPathPoint(cell2pix((*it)->m_cell));
	}
}

void Exercise1Scene::GetVisitedNodesPosition(std::map<Node*, Node*> visited)
{
	for (std::map<Node*, Node*>::iterator it = visited.begin(); it != visited.end(); it++)
	{
		Vector2D pos = cell2pix(it->first->m_cell);
		visitedNodesPosition.push_back(pos);
	}
}

void Exercise1Scene::PaintVisitedNodes()
{
	for each(Vector2D pos in visitedNodesPosition)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)pos.x, (int)pos.y, 15, 75, 75, 0, 255);
	}
}

void Exercise1Scene::PrintStatistics()
{
	system("cls");
	PrintTitle();
	std::cout << "Min visited: " << minVisited << " max visited: " << maxVisited << " mean: " << meanVisited / numFindings << std::endl;
	if (numVisited < minVisited)
		minVisited = numVisited;
	if (numVisited > maxVisited)
		maxVisited = numVisited;

	meanVisited += numVisited;
}

void Exercise1Scene::GetAlghorithmTitle(int ex)
{
	switch (ex)
	{
	case 2:
		algorithmTitle = "Breadth First Search";
		break;
	case 3:
		algorithmTitle = "Dijkstra";
		break;
	case 4:
		algorithmTitle = "Greedy Best First Search";
		break;
	case 5:
		algorithmTitle = "A*";
		break;
	default:
		algorithmTitle = "default";
		break;
	}
	PrintTitle();
}

void Exercise1Scene::PrintTitle() {
	std::string title = "SDL Path Finding :: Exercise 1 ";
	title.append(algorithmTitle);
	std::cout << title << std::endl;
}
