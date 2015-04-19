#include "map.h"

map::map(int width, int height)
{
	this->width = width;
	this->height = height;
	this->tiles.resize(height, std::vector<tile>(width, tile(3)));
}

map::~map()
{
}

void map::setTile(tile tile, int x, int y)
{
	this->tiles[x][y] = tile;
}

sf::FloatRect map::getMapBounds() {
	if ((this->width >= 1) && (this->height >= 1)) {
		return sf::FloatRect(this->tiles[0][0].getTile().getGlobalBounds().left, this->tiles[0][0].getTile().getGlobalBounds().top, width * 16, height * 16 + 8);
	}
	return sf::FloatRect(0, 0, 0, 0);
}