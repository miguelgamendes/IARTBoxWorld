#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "tile.h"
#include "map.h"

sf::Texture tile::tileset = sf::Texture(); //needed so linker doesn't crash

void drawMap(sf::RenderWindow& window, map map);
map loadMap(std::string filename);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Warehouse Keeper");
	tile::tileset.loadFromFile("tileset.png");
	map test = loadMap("map1");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		drawMap(window, test);
		window.display();
	}
	return 0;
}

void drawMap(sf::RenderWindow& window, map map) {
	std::vector<std::vector<tile>> tiles = map.getTiles();
	for (int i = 0; i < tiles.size(); ++i) {
		for (int j = 0; j < tiles[i].size(); ++j) {
			tiles[i][j].getTile().move(j * 16, i * 16);
			window.draw(tiles[i][j].getTile());
		}
	}
}

map loadMap(std::string filename) {
	int width, height, selector;
	std::ifstream file(filename + ".txt", std::ifstream::in);
	std::string read;
	std::getline(file, read);
	std::istringstream(read) >> width;
	std::getline(file, read);
	std::istringstream(read) >> height;
	map map(width, height);
	std::vector<std::vector<tile>> tiles = map.getTiles();
	for (int i = 0; i < tiles.size(); ++i) {
		for (int j = 0; j < tiles[i].size(); ++j) {
			std::getline(file, read, ',');
			std::istringstream(read) >> selector;
			map.setTile(tile(selector), i, j);
		}
	}
	return map;
}