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

class Exercise1Scene :
	public Scene
{
public:
	Exercise1Scene(int ex);
	~Exercise1Scene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;

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
	void CreateRandomWeights();
	void CreateSpecificWeights();
	Node* coinNode;
	void CreatePathToCoin();
	void SetPath(std::map<Node*, Node*> v);
	std::pair<int, int> Cell2Pair(Vector2D);
	void GetVisitedNodesPosition(std::map<Node*, Node*> visited);
	void PaintVisitedNodes();
	std::vector<Vector2D>visitedNodesPosition;

	int numVisited;
	int minVisited;
	int maxVisited;
	int meanVisited;
	int numFindings;
	const int maxNumFindings = 10;
	void PrintStatistics();

	std::string algoritmTitle;
	void GetAlghorithmTitle();
};

