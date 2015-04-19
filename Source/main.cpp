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
	sf::FloatRect mapBounds = test.getMapBounds();
	mapBounds.left += 100;
	mapBounds.top += 200;
	std::vector<std::vector<tile>> tiles = test.getTiles();
	sf::Sprite tileGUI;
	sf::RectangleShape selected;
	sf::Vector2i selectedTile(0, 0);
	tileGUI.setTexture(tile::tileset);
	tileGUI.setPosition(1, 1);
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setSize(sf::Vector2u(1280, 720)); //locked to 720p
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (tileGUI.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						selected.setSize(sf::Vector2f(16, 24));
						selected.setPosition(sf::Vector2f(tileGUI.getGlobalBounds().left, tileGUI.getGlobalBounds().top));
						selected.move(((int)(event.mouseButton.x - tileGUI.getGlobalBounds().left) / 17) * 17, ((int)(event.mouseButton.y - tileGUI.getGlobalBounds().top) / 25) * 25);
						selected.setOutlineColor(sf::Color::Yellow);
						selected.setFillColor(sf::Color::Transparent);
						selected.setOutlineThickness(1.0);
						selectedTile = sf::Vector2i((int)(event.mouseButton.x - tileGUI.getGlobalBounds().left) / 17, (int)(event.mouseButton.y - tileGUI.getGlobalBounds().top) / 25);
					}
					else if (mapBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
						int i, j;
						i = (int)(event.mouseButton.x - mapBounds.left) / 16;
						j = (int)(event.mouseButton.y - 6 - mapBounds.top) / 16;
						if (j <= 0) {
							j = (int)(event.mouseButton.y - mapBounds.top) / 24;
						} 
						else if (j > 0 && j < test.getHeight() - 1) {
							//j = (int)(event.mouseButton.y - mapBounds.top) / 16;
						}
						else {
							j = test.getHeight() - 1;
						}
						std::cout << (int)((event.mouseButton.x - mapBounds.left) / 16) << " | " << (int)((event.mouseButton.y - mapBounds.top) / 16) << std::endl;
						test.getTiles()[j][i].setSelector(selectedTile.x + selectedTile.y * 3);
					}
				}
				break;
			default:
				break;
			}
		}
		window.draw(selected);
		window.draw(tileGUI);
		drawMap(window, test);
		window.display();
	}
	return 0;
}

void drawMap(sf::RenderWindow& window, map map) {
	std::vector<std::vector<tile>> tiles = map.getTiles();
	for (int i = 0; i < tiles.size(); ++i) {
		for (int j = 0; j < tiles[i].size(); ++j) {
			tiles[i][j].getTile().move(100 + j * 16, 200 +  i * 16);
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