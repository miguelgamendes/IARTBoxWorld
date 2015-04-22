#pragma once
#include <vector>
#include "tile.h"

class map
{
	std::vector<std::vector<tile>> tiles;
	int width;
	int height;
	int pos_x;
	int pos_y;

public:
	//Constructor/Destructor
	map(int width, int height);
	map(int width, int height, int pos_x, int pos_y);
	~map();

	//Setters
	void setTile(tile tile, int x, int y);
	void setPos_x(int pos_x) {this->pos_x = pos_x; }
	void setPos_y(int pos_y) {this->pos_y = pos_y; }

	//Getters
	int& getWidth() {return this->width; }
	int& getHeight() {return this->height; }
	std::vector<std::vector<tile>>& getTiles() {return this->tiles; }
	sf::FloatRect getMapBounds();

	//Functions
	void modifyWidth(int rate);
	void modifyHeight(int rate) { this->height += rate; }
	void drawMap(sf::RenderWindow& window);
};