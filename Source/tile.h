#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class tile
{
	sf::Sprite sprite;
	int selector;

public:
	static sf::Texture tileset;

	tile(int selector);
	~tile();

	sf::Sprite& getTile() {return this->sprite; }
	void setSelector(int selector);
};