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

class Exercise2Scene :
	public Scene
{
public:
	Exercise2Scene();
	~Exercise2Scene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;

	int num_cell_x;
	int num_cell_y;
	bool draw_grid;

	void initMaze(char* filename);
	std::vector< std::vector<int> > terrain;

	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);

	void drawMaze();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

	//New Code
	void init();
	Graph* m_graph;
	const int MAX_WEIGHT = 6;
	const int MIN_WEIGHT = 1;
	void CreateRandomWeights();
	void CreateSpecificWeights();
	Node* coinNode;
	void CreatePathToCoin();
	void SetPath(std::map<Node*, Node*> v);
	std::pair<int, int> Cell2Pair(Vector2D);
	void GetVisitedNodesPosition(std::map<Node*, Node*> visited);
	void PaintVisitedNodes();
	std::vector<Vector2D>visitedNodesPosition;

	//Exercice2 specific
	const int numCoins = 10;
	std::vector<Vector2D> coinPositions;
	Vector2D currentCoinPosition;
	bool validCoinPosition(Vector2D coinPos);
	void drawCoins();
};

