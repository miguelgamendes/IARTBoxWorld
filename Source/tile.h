#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class tile
{
	sf::Sprite sprite;
	int selector;

public:
	static sf::Texture tileset;

	//Constructor/Destructor
	tile(int selector);
	~tile();

	//Setters
	void setSelector(int selector);

	//Getters
	sf::Sprite& getTile() {return this->sprite; }
	int getSelector() {return this->selector; }
};