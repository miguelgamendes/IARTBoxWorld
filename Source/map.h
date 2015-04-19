#pragma once
#include <vector>
#include "tile.h"

class map
{
	std::vector<std::vector<tile>> tiles;
	int width;
	int height;
public:
	map(int width, int height);
	~map();

	void setTile(tile tile, int x, int y);

	int& getWidth() {return this->width; }
	int& getHeight() {return this->height; }
	std::vector<std::vector<tile>>& getTiles() {return this->tiles; }

	sf::FloatRect getMapBounds();
};