#include "Exercise3Scene.h"

std::vector<Edge*> lastFrame;
std::vector<int> lasWeights;

void Exercise3Scene::init()
{
	system("cls");
	draw_grid = false;

	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;
	initMaze("../res/maze.csv");
	loadTextures("../res/maze.png", "../res/coin.png");

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setTarget(Vector2D(-20, -20));
	//agent->setMaxVelocity(200);
	//agent->max_force = 150;
	agents.push_back(agent);

	Agent *agent2 = new Agent;
	agent2->loadSpriteTexture("../res/zombie1.png", 4);
	agent2->setTarget(Vector2D(-20, -20));
	//agent2->setMaxVelocity(200);
	//agent2->max_force = 150;
	agent2->enemy = true;
	agents.push_back(agent2);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[0]->setPosition(cell2pix(rand_cell));

	//set enemy position in a random cell, far from the agent
	while (!isValidCell(rand_cell) || EnemyNear(agents[0]->getPosition(), cell2pix(rand_cell)))
		rand_cell = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	agents[1]->setPosition(cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));

	near = false;
}

Exercise3Scene::Exercise3Scene()
{
	init();

	m_graph = new Graph(&terrain);
	CreatePathToCoin();
	CreateEnemyPath();
}

Exercise3Scene::~Exercise3Scene()
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

void Exercise3Scene::update(float dtime, SDL_Event *event)
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

	if (EnemyNear(agents[0]->getPosition(), agents[1]->getPosition()) && IsInNode(agents[0], m_graph) && !near)
	{
		std::cout << "Enemy Near" << std::endl;
		near = true;
		agents[0]->path.points.clear();
		agents[0]->setCurrentTargetIndex(-1);
		//Reasign weights around the enemy
		//Vector2D posEnemy = pix2cell(agents[1]->getPosition());
		//std::cout << posEnemy.x << "," << posEnemy.y << std::endl;
		//ChangeEnemyWeights(posEnemy);

		ChangeEnemyWeights2();
		CreatePathToCoin();
	}
	if (!EnemyNear(agents[0]->getPosition(), agents[1]->getPosition()) && IsInNode(agents[0], m_graph) && near)
	{
		std::cout << "Enemy Far" << std::endl;
		near = false;

		RestartWeights();
	}

	//AGENT
	Vector2D steering_force = agents[0]->Behavior()->SimplePathFollowing(agents[0], dtime);
	agents[0]->update(steering_force, dtime, event);

	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		coinPosition = Vector2D(-1, -1);
		while ((!isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 5))
			coinPosition = Vector2D((float)(rand() % num_cell_y), (float)(rand() % num_cell_x));

		//compute new path
		CreatePathToCoin();
	}

	////ENEMY
	steering_force = agents[1]->Behavior()->SimplePathFollowing(agents[1], dtime);
	agents[1]->update(steering_force, dtime, event);

	// if we have arrived to the new position, replace it in a random cell!
	if ((agents[1]->getCurrentTargetIndex() == -1) && (pix2cell(agents[1]->getPosition()) == randomEnemyPosition))
	{
		randomEnemyPosition = Vector2D(-1, -1);
		while ((!isValidCell(randomEnemyPosition)) || (Vector2D::Distance(randomEnemyPosition, pix2cell(agents[1]->getPosition())) < 3))
			randomEnemyPosition = Vector2D((float)(rand() % num_cell_y), (float)(rand() % num_cell_x));

		//compute new path
		CreateEnemyPath();
	}
}


#pragma region GivenFunctions

void Exercise3Scene::draw()
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

	for (int i = 0; i < agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* Exercise3Scene::getTitle()
{
	std::string title = "SDL Path Finding :: Exercise 1 ";
	//title.append(algorithmTitle);
	//return title.c_str();//no funciona
	return "SDL Path Finding :: Exercise 3 ";
}

void Exercise3Scene::drawMaze()
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
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 100 * terrain[j][i] - 100, 0, 0, 255);
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

void Exercise3Scene::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

void Exercise3Scene::initMaze(char* filename)
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

bool Exercise3Scene::loadTextures(char* filename_bg, char* filename_coin)
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

Vector2D Exercise3Scene::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D Exercise3Scene::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool Exercise3Scene::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x] == 0);
}

#pragma endregion

void Exercise3Scene::CreateRandomWeights()
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

void Exercise3Scene::CreateSpecificWeights()
{
	terrain[num_cell_y / 2][num_cell_x / 2] = MAX_WEIGHT;
	terrain[num_cell_y / 2 - 1][num_cell_x / 2] = MAX_WEIGHT;
	terrain[num_cell_y / 2 + 1][num_cell_x / 2] = MAX_WEIGHT;
	terrain[num_cell_y / 2][num_cell_x / 2 - 1] = MAX_WEIGHT;
	terrain[num_cell_y / 2][num_cell_x / 2 + 1] = MAX_WEIGHT;
	terrain[num_cell_y / 2 + 1][num_cell_x / 2 + 1] = MAX_WEIGHT;
	terrain[num_cell_y / 2 - 1][num_cell_x / 2 - 1] = MAX_WEIGHT;
	terrain[num_cell_y / 2 - 1][num_cell_x / 2 + 1] = MAX_WEIGHT;
	terrain[num_cell_y / 2 + 1][num_cell_x / 2 - 1] = MAX_WEIGHT;
}

void Exercise3Scene::CreatePathToCoin()
{
	Vector2D agentCell = pix2cell(agents[0]->getPosition());
	Node* playerNode = m_graph->nodesMap.at(Cell2Pair(agentCell));
	coinNode = m_graph->nodesMap.at(Cell2Pair(coinPosition));

	std::map<Node*, Node*> visited;
	m_graph->CreateHeuristics(coinNode);
	visited = PathFinding::A(m_graph, playerNode, coinNode);

	visitedNodesPosition.clear();
	GetVisitedNodesPosition(visited);
	SetPath(visited);
}

void Exercise3Scene::CreateEnemyPath()
{
	randomEnemyPosition = Vector2D(-1, -1);
	while (!isValidCell(randomEnemyPosition))
		randomEnemyPosition = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));

	Vector2D agentCell = pix2cell(agents[1]->getPosition());
	Node* enemyNode = m_graph->nodesMap.at(Cell2Pair(agentCell));
	Node* randomNode = m_graph->nodesMap.at(Cell2Pair(randomEnemyPosition));

	std::map<Node*, Node*> visited;
	m_graph->CreateHeuristics(randomNode);
	visited = PathFinding::GreedyBestFirstSearch(m_graph, enemyNode, randomNode);

	SetRandomPath(visited, randomNode);
}

std::pair<int, int> Exercise3Scene::Cell2Pair(Vector2D cell)
{
	//std::cout << "cell " << cell.x << " "<<cell.y << std::endl;
	return std::make_pair(cell.y, cell.x);
}

void Exercise3Scene::SetPath(std::map<Node*, Node*> visited)
{
	std::vector<Node*> shortestPath = Graph::GetShortestPath(visited, coinNode);

	for (std::vector<Node*>::reverse_iterator it = shortestPath.rbegin(); it != shortestPath.rend(); ++it)
	{
		agents[0]->addPathPoint(cell2pix((*it)->m_cell));
	}
}

void Exercise3Scene::SetRandomPath(std::map<Node*, Node*> visited, Node* randomNode)
{
	std::vector<Node*> shortestPath = Graph::GetShortestPath(visited, randomNode);

	for (std::vector<Node*>::reverse_iterator it = shortestPath.rbegin(); it != shortestPath.rend(); ++it)
	{
		agents[1]->addPathPoint(cell2pix((*it)->m_cell));
	}
}

void Exercise3Scene::GetVisitedNodesPosition(std::map<Node*, Node*> visited)
{
	for (std::map<Node*, Node*>::iterator it = visited.begin(); it != visited.end(); it++)
	{
		Vector2D pos = cell2pix(it->first->m_cell);
		visitedNodesPosition.push_back(pos);
	}
}

void Exercise3Scene::PaintVisitedNodes()
{
	for each(Vector2D pos in visitedNodesPosition)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)pos.x, (int)pos.y, 15, 75, 75, 0, 255);
	}
}

bool Exercise3Scene::EnemyNear(Vector2D agentPos, Vector2D enemyPos)
{
	return Vector2D::Distance(pix2cell(agentPos), pix2cell(enemyPos)) < MIN_ENEMY_DIST;
}

bool Exercise3Scene::IsInNode(Agent* agent, Graph * graph)
{
	Vector2D agentCell = pix2cell(agent->getPosition());

	return graph->nodesMap.count(Cell2Pair(agentCell)) > 0;
}

void Exercise3Scene::ChangeEnemyWeights(Vector2D enemyPos)
{
	std::map<std::pair<int, int>, Node*>::iterator it;
	Node* current;
	std::vector<Node*> adyacentes;
	std::map<std::pair<Node*, Node*>, Edge*>::iterator it2;

	//Reestablecer los pesos del paso anterior
	if (lastFrame.size() > 0)
	{
		for (int i = 0; i < lastFrame.size(); i++)
		{
			lastFrame[i]->weight = lasWeights[i];
		}

		lastFrame.clear();
		lasWeights.clear();
	}

	//Buscar todos los nodos adyacentes del nodo actual del enemigo
	it=m_graph->nodesMap.find(std::make_pair(enemyPos.x, enemyPos.y));
	if (it != m_graph->nodesMap.end())
	{
		current = it->second;

		for (int i = 0; i<it->second->adjacencyList.size(); i++)
		{
			adyacentes.push_back(it->second->adjacencyList[i]);
		}

		//Buscar todos los edges que salen de este nodo y modificarles el peso
		for (int i = 0; i < adyacentes.size(); i++)
		{
			it2 = m_graph->edgesMap.find(std::make_pair(current, adyacentes[i]));
			lastFrame.push_back(it2->second);
			lasWeights.push_back(it2->second->weight);
			it2->second->weight *= 10;
		}
	}
 }

void Exercise3Scene::ChangeEnemyWeights2()
{
	Vector2D agentCell = pix2cell(agents[1]->getPosition());
	Node* enemyNode = m_graph->nodesMap.at(Cell2Pair(agentCell));
	terrain[enemyNode->m_cell.y][enemyNode->m_cell.x] = MAX_WEIGHT;
	for each(Node* n in enemyNode->adjacencyList)
	{
		terrain[n->m_cell.y][n->m_cell.x] = MAX_WEIGHT;
		if (m_graph->edgesMap[std::make_pair(enemyNode, n)]->weight != MAX_WEIGHT)
		{
			m_graph->edgesMap[std::make_pair(enemyNode, n)]->weight = MAX_WEIGHT;
			m_graph->edgesMap[std::make_pair(n, enemyNode)]->weight = MAX_WEIGHT;
		}
		for each(Node* n2 in n->adjacencyList)
		{
			terrain[n2->m_cell.y][n2->m_cell.x] = MAX_WEIGHT;
			if (m_graph->edgesMap[std::make_pair(n, n2)]->weight != MAX_WEIGHT)
			{
				m_graph->edgesMap[std::make_pair(n, n2)]->weight = MAX_WEIGHT;
				m_graph->edgesMap[std::make_pair(n2, n)]->weight = MAX_WEIGHT;

			}
			for each(Node* n3 in n2->adjacencyList)
			{
				terrain[n3->m_cell.y][n3->m_cell.x] = MAX_WEIGHT;
				if (m_graph->edgesMap[std::make_pair(n2, n3)]->weight != MAX_WEIGHT)
				{
					m_graph->edgesMap[std::make_pair(n2, n3)]->weight = MAX_WEIGHT;
					m_graph->edgesMap[std::make_pair(n3, n2)]->weight = MAX_WEIGHT;
				}
				for each(Node* n4 in n3->adjacencyList)
				{
					terrain[n4->m_cell.y][n4->m_cell.x] = MAX_WEIGHT;
					if (m_graph->edgesMap[std::make_pair(n3, n4)]->weight != MAX_WEIGHT)
					{
						m_graph->edgesMap[std::make_pair(n3, n4)]->weight = MAX_WEIGHT;
						m_graph->edgesMap[std::make_pair(n4, n3)]->weight = MAX_WEIGHT;
					}
				}
			}
		}
	}
}

void Exercise3Scene::RestartWeights()
{
	for (auto& edge: m_graph->edgesMap)
	{
		if (edge.second->weight != 1)
		{
			edge.second->weight == 1;
		}
	}

	//TERRAIN:
	for (int row = 0; row < num_cell_y; row++)
	{
		for (int col = 0; col < num_cell_x; col++)
		{
			if (terrain[row][col] > 1)
				terrain[row][col] = 1;
		}
	}

}
