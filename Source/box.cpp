#include "box.h"

Box::Box() {
	mapPosition = sf::Vector2i(0, 0);
	texture.loadFromFile("tileset.png");
	div_t divres;
	divres = div(0, 3);
	this->sprite.setTextureRect(sf::IntRect((divres.rem * 16 + divres.rem), (divres.quot * 24 + divres.quot), 16, 24));
}

Box::Box(int x, int y, int selector) {
	mapPosition = sf::Vector2i(x, y);
	div_t divres;
	divres = div(selector, 3);
	this->sprite.setTextureRect(sf::IntRect((divres.rem * 16 + divres.rem), (divres.quot * 24 + divres.quot), 16, 24));
}

sf::Vector2i Box::getMapPosition() {
	return mapPosition;
}

sf::Vector2i Box::getTarget() {
	return targetHole;
}

void Box::setPosition(int x, int y) {
	position = sf::Vector2f(x, y);
}

void Box::setMapPosition(int x, int y) {
	mapPosition = sf::Vector2i(x, y);
}

void Box::setTarget(int x, int y) {
	targetHole = sf::Vector2i(x, y);
}