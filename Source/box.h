#pragma once

#include <SFML/Graphics.hpp>

class Box {
	sf::Vector2i mapPosition;
	int selector;
	sf::Vector2i targetHole;
	sf::Sprite sprite;
	bool assigned;

public:
	static sf::Texture texture;

	Box();
	Box(int x, int y, int selector);

	//getters
	sf::Vector2i getMapPosition();
	sf::Vector2i getTarget();

	//setters
	void setPosition(int x, int y);
	void setMapPosition(int x, int y);
	void setTarget(int x, int y);

	//functions
	void initialize(int x, int y, int selector);
	void render(sf::RenderWindow& target);
};