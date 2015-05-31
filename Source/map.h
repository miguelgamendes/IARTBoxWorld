#pragma once

#include <cmath>
#include <map>
#include <queue>
#include <vector>
#include "node.h"
#include "player.h"
#include "tile.h"

class map
{
	Player player;
	std::vector<std::vector<tile>> tiles;
	int width;
	int height;
	int pos_x;
	int pos_y;

	//algorithm related members
	struct compareNodes {
		bool operator() (Node const &n1, Node const &n2) {
			return n1.getfx() > n2.getfx();
		}
	};
	
	int cameFrom[30][30][2];

public:
	//Constructor/Destructor
	map(int width, int height);
	map(int width, int height, int pos_x, int pos_y);
	~map();

	//Setters
	void setTile(tile tile, int x, int y);
	void setPos_x(int pos_x) {this->pos_x = pos_x; }
	void setPos_y(int pos_y) {this->pos_y = pos_y; }
	void setPlayerPosition(int x, int y);

	//Getters
	int getTileValue(int x, int y);
	int& getWidth() {return this->width; }
	int& getHeight() {return this->height; }
	std::vector<std::vector<tile>>& getTiles() {return this->tiles; }
	sf::FloatRect getMapBounds();
	int getPlayerPosX();
	int getPlayerPosY();
	sf::Vector2i getGoal();

	//Functions
	void modifyWidth(int rate);
	void modifyHeight(int rate);
	void drawMap(sf::RenderWindow& window);
	std::vector<int> boxPositions();
	int distance(Node n1, Node n2);
	int heuristic(Node n, int destX, int destY);
	std::vector<int> reconstructPath(Node n);
	std::vector<int> findpath(int originX, int originY, int destinationX, int destinationY);
	std::vector<int> findboxpath(int originX, int originY, int destinationX, int destinationY);
};