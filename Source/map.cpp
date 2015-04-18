#include "map.h"

map::map(int width, int height)
{
	this->width = width;
	this->height = height;
	this->tiles.resize(width, std::vector<tile>(height, tile(3)));
}

map::~map()
{
}

void map::setTile(tile tile, int x, int y)
{
	this->tiles[y][x] = tile;
}