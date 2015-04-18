#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.h"

sf::Texture tile::tileset = sf::Texture(); //needed so linker doesn't crash

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Warehouse Keeper");
	tile::tileset.loadFromFile("tileset.png");
	tile test = tile(0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(test.getTile());
		window.display();
	}

	return 0;
}