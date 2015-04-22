#include "map.h"
#include <iostream>

map::map(int width, int height) {
	this->width = width;
	this->height = height;
	this->tiles.resize(height, std::vector<tile>(width, tile(3)));
}

map::map(int width, int height, int pos_x, int pos_y)
{
	this->width = width;
	this->height = height;
	this->tiles.resize(height, std::vector<tile>(width, tile(3)));
	this->pos_x = pos_x;
	this->pos_y = pos_y;
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
		return sf::FloatRect(this->tiles[0][0].getTile().getGlobalBounds().left, this->tiles[0][0].getTile().getGlobalBounds().top, this->width * 16, this->height * 16 + 8);
	}
	return sf::FloatRect(0, 0, 0, 0);
}

void map::modifyWidth(int rate) {
	this->width += rate;
	if (width >= 1) {
		if (rate > 0) {
			for (int i = 0; i < this->tiles.size(); ++i) {
				this->tiles[i].push_back(tile(3));
			}
		}
		else if (rate < 0) {
			for (int i = 0; i < this->tiles.size(); ++i) {
				this->tiles[i].erase(this->tiles[i].end() - 1);
			}
		}
	}
	else this->width = 1;
}

void map::modifyHeight(int rate) {
	this->height += rate;
	if (height >= 1) {
		if (rate > 0) {
			this->tiles.push_back(std::vector<tile>(this->width, tile(3)));
		}
		else if (rate < 0) {
			this->tiles.erase(this->tiles.end() - 1);
		}
	}
	else this->height = 1;
}

void map::drawMap(sf::RenderWindow& window) {
	for (int i = 0; i < this->tiles.size(); ++i) {
		for (int j = 0; j < this->tiles[i].size(); ++j) {
			this->tiles[i][j].getTile().setPosition(this->pos_x + j * 16, this->pos_y + i * 16);
			window.draw(this->tiles[i][j].getTile());
		}
	}
}