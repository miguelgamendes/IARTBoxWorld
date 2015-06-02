#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Spinner.h"
#include "tile.h"
#include "map.h"

sf::Texture tile::tileset = sf::Texture(); //needed so linker doesn't crash
sf::Texture Spinner::texture = sf::Texture(); //needed so linker doesn't crash
sf::Texture Box::texture = sf::Texture();

std::string intToString(int &number);
map loadMap(std::string filename);
void saveMap(std::string filename, map map);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Warehouse Keeper");
	sf::Font font;
	tile::tileset.loadFromFile("tileset.png");
	Spinner::texture.loadFromFile("spinner.png");
	font.loadFromFile("arial.ttf");
	Box::texture.loadFromFile("tileset.png");
	map test = loadMap("test");
	test.preparePlayer();
	test.setPos_x(300);
	test.setPos_y(200);
	//map test(5, 5, 300, 200);
	sf::Sprite tileGUI;
	sf::RectangleShape selected;
	sf::Vector2i selectedTile(0, 0);
	tileGUI.setTexture(tile::tileset);
	tileGUI.setPosition(1, 1);

	bool placingPlayer = false; //checks whether user is currently placing player
	bool playerReady = false; //true when AI is ready to traverse the map
	sf::Time playerTime;
	sf::Clock playerClock;

	sf::Text widthSpinnerT;
	sf::Text widthLabel;
	widthSpinnerT.setFont(font);
	widthLabel.setFont(font);
	widthSpinnerT.setCharacterSize(12);
	widthLabel.setCharacterSize(12);
	widthSpinnerT.setColor(sf::Color::White);
	widthLabel.setColor(sf::Color::White);
	widthSpinnerT.setPosition(55, 200);
	widthLabel.setPosition(10, 200);
	widthLabel.setString("Width:");
	Spinner widthSpinner(50, 200, widthLabel);


	sf::Text heightSpinnerT;
	sf::Text heightLabel;
	heightSpinnerT.setFont(font);
	heightLabel.setFont(font);
	heightSpinnerT.setCharacterSize(12);
	heightLabel.setCharacterSize(12);
	heightSpinnerT.setColor(sf::Color::White);
	heightLabel.setColor(sf::Color::White);
	heightSpinnerT.setPosition(55, 230);
	heightLabel.setPosition(8, 230);
	heightLabel.setString("Height:");
	Spinner heightSpinner(50, 230, heightLabel);

	std::vector<int> path;
	std::vector<int> holePositions;
	std::vector<int> boxPositions;
	std::vector<int> boxPath;

	while (window.isOpen())
	{
		widthSpinnerT.setString(intToString(test.getWidth()));
		heightSpinnerT.setString(intToString(test.getHeight()));

		// INPUT

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				saveMap("test", test);
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
					else if (test.getMapBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						int i, j;
						i = (int)(event.mouseButton.x - test.getMapBounds().left) / 16;
						j = (int)(event.mouseButton.y - 6 - test.getMapBounds().top) / 16;
						if (j <= 0) {
							j = (int)(event.mouseButton.y - test.getMapBounds().top) / 24;
						} 
						else if (j > 0 && j < test.getHeight() - 1) {
							//j = (int)(event.mouseButton.y - mapBounds.top) / 16;
						}
						else {
							j = test.getHeight() - 1;
						}
						std::cout << (int)((event.mouseButton.x - test.getMapBounds().left) / 16) << " | " << (int)((event.mouseButton.y - test.getMapBounds().top) / 16) << std::endl;
						if(placingPlayer) {
							test.setPlayerPosition(i, j);
						} else {
							if((selectedTile.x + selectedTile.y * 3) > 2)
								test.getTiles()[j][i].setSelector(selectedTile.x + selectedTile.y * 3);
							else
								test.addBox(i, j, (selectedTile.x + selectedTile.y * 3));
						}
						std::cout << selectedTile.x + selectedTile.y * 3 << std::endl;
					}
					else if (widthSpinner.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						if ((event.mouseButton.x - widthSpinner.getSprite().getGlobalBounds().left >= 21) && (event.mouseButton.y - widthSpinner.getSprite().getGlobalBounds().top <= 9)) {
							test.modifyWidth(1);
						}
						else if ((event.mouseButton.x - widthSpinner.getSprite().getGlobalBounds().left >= 21) && (event.mouseButton.y - widthSpinner.getSprite().getGlobalBounds().top > 9)) {
							test.modifyWidth(-1);
						}
					}
					else if (heightSpinner.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						if ((event.mouseButton.x - heightSpinner.getSprite().getGlobalBounds().left >= 21) && (event.mouseButton.y - heightSpinner.getSprite().getGlobalBounds().top <= 9)) {
							test.modifyHeight(1);
						}
						else if ((event.mouseButton.x - heightSpinner.getSprite().getGlobalBounds().left >= 21) && (event.mouseButton.y - heightSpinner.getSprite().getGlobalBounds().top > 9)) {
							test.modifyHeight(-1);
						}
					}
				}
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::P) {
					placingPlayer = true;
				}
				break;
			case sf::Event::KeyReleased:
				if(event.key.code == sf::Keyboard::P) {
					placingPlayer = false;
				}
				if(event.key.code == sf::Keyboard::Return) {
					//find exit
					sf::Vector2i exit = test.getGoal();
					//find the best possible path
					path = test.findpath(test.getPlayerPosX(), test.getPlayerPosY(), exit.x, exit.y);
					
					//identify holes
					for(int i = 0; i < path.size(); i = i + 2) {
						if(test.getTileValue(path[i], path[i+1]) >= 9) {
							holePositions.push_back(path[i]);
							holePositions.push_back(path[i+1]);
						}
					}

					//identify boxes
					boxPositions = test.boxPositions();

					//assign box to first hole
					
					int boxIndex = 0;
					int dist = 1000;
					for(int i = 0; i < test.boxes.size(); i++) {
						int newDist = test.distance(Node(test.boxes[i].getMapPosition().x, test.boxes[i].getMapPosition().y), Node(holePositions[0], holePositions[1]));
						if(newDist < dist) {
							dist = newDist;
							boxIndex = i;
						}
					}
					if(dist < 1000)
						test.boxes[boxIndex].setTarget(holePositions[0], holePositions[1]);
					
					//set player upon his first god damn quest

					//
					boxPath = test.findboxpath(test.boxes[boxIndex].getMapPosition().x, test.boxes[boxIndex].getMapPosition().y, test.boxes[boxIndex].getTarget().x, test.boxes[boxIndex].getTarget().y);

					for(int i = 0; i < boxPath.size(); i = i + 2) {
						std::cout << boxPath[i] << " " << boxPath[i+1] << std::endl;
					}

					path = test.findpath(test.getPlayerPosX(), test.getPlayerPosY(), boxPath[0] + (boxPath[0] - boxPath[2]), boxPath[1] + (boxPath[1] - boxPath[3]));
					path.insert(path.end(), boxPath.begin(), boxPath.end());

					for(int i = 0; i < path.size(); i = i + 2) {
						std::cout << path[i] << " " << path[i+1] << std::endl;
					}

					playerReady = true;
				}
				break;
			default:
				break;
			}
		}

		// UPDATES
		if(playerReady) {
			playerTime  = playerClock.getElapsedTime();
			if(playerTime.asMilliseconds() > 500) {
				playerClock.restart();
				test.setPlayerPosition(path[0], path[1]);
				path.erase(path.begin());
				path.erase(path.begin());
				if(path.empty()){
					if(test.getPlayerPosX() == test.getGoal().x && test.getPlayerPosY() == test.getGoal().y)
						playerReady = false;
					else
						; //figure our next move
				}
			}
		}

		// RENDERING

		window.clear();
		window.draw(selected);
		window.draw(tileGUI);
		test.drawMap(window);
		widthSpinner.drawSpinner(window);
		heightSpinner.drawSpinner(window);
		window.draw(widthSpinnerT);
		window.draw(heightSpinnerT);
		window.display();
	}
	return 0;
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

void saveMap(std::string filename, map map) {
	std::ofstream file(filename + ".txt", std::ofstream::out);
	file << map.getWidth() << std::endl;
	file << map.getHeight() << std::endl;
	for (int i = 0; i < map.getTiles().size(); ++i) {
		for (int j = 0; j < map.getTiles()[i].size(); ++j) {
			file << map.getTiles()[i][j].getSelector() << ",";
		}
		file << std::endl;
	}
	file.close();
}

std::string intToString(int &number) {
	std::stringstream convert;
	convert << number;
	return convert.str();
}