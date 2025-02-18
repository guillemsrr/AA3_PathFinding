#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "PathFinding.h"
#include "Graph.h"

class Exercise3Scene :
	public Scene
{
public:
	Exercise3Scene();
	~Exercise3Scene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;
	Vector2D randomEnemyPosition;

	//bool flag = false;

	int num_cell_x;
	int num_cell_y;
	bool draw_grid;

	void initMaze(char* filename);
	std::vector< std::vector<int> > terrain;

	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);

	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

	//New Code
	void init();
	Graph* m_graph;
	const int MAX_WEIGHT = 6;
	const int MIN_WEIGHT = 1;
	const int MIN_ENEMY_DIST = 6;
	void CreateRandomWeights();
	void CreateSpecificWeights();
	Node* coinNode;
	void CreatePathToCoin();
	void CreateEnemyPath();
	void SetPath(std::map<Node*, Node*> v);
	void SetRandomPath(std::map<Node*, Node*> visited, Node* randomNode);
	std::pair<int, int> Cell2Pair(Vector2D);
	void GetVisitedNodesPosition(std::map<Node*, Node*> visited);
	void PaintVisitedNodes();
	std::vector<Vector2D>visitedNodesPosition;
	bool EnemyNear(Vector2D agentPos, Vector2D enemyPos);
	bool IsInNode(Agent* agent, Graph* graph);
	void ChangeEnemyWeights(Vector2D enemyPos);
	void ChangeEnemyWeights2();
	void RestartWeights();
	bool near;
	int frames;
};

