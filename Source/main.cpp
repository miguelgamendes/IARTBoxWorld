#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.h"
#include "map.h"

sf::Texture tile::tileset = sf::Texture(); //needed so linker doesn't crash

void drawMap(sf::RenderWindow& window, map map);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Warehouse Keeper");
	tile::tileset.loadFromFile("tileset.png");
	map test = map(5, 5);
	test.setTile(tile(6), 1, 1);
	test.setTile(tile(6), 1, 2);
	test.setTile(tile(6), 1, 3);
	test.setTile(tile(6), 2, 1);
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
			tiles[j][i].getTile().move(j * 16, i * 16);
			window.draw(tiles[j][i].getTile());
		}
	}
}