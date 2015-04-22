#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Spinner
{
	sf::Sprite sprite;
	int pos_x;
	int pos_y;
	std::string text;
	int* target;

public:
	static sf::Texture texture;

	//Constructor/Destructor
	Spinner(int pos_x, int pos_y, std::string text, int* target);
	~Spinner();

	//Setters

	//Getters
	sf::Sprite getSprite() {return this->sprite; }

	//Functions
	void incrementTarget() {*(this->target) += 1; }
	void decrementTarget() {*(this->target) += 1; }
};