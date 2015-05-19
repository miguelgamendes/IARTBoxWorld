#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
	sf::RectangleShape sprite;
	int pos_x;
	int pos_y;
public:
	Player();
	Player(int pos_x, int pos_y);

	//getters
	sf::Vector2f getPosition();
	int getMapPosX();
	int getMapPosY();

	//setters
	void setPosition(sf::Vector2f newPosition);
	void setMapPosX(int x);
	void setMapPosY(int y);

	//functions
	void render(sf::RenderWindow * target);
};