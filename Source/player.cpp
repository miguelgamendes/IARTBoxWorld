#include "player.h"

Player::Player() {
	texture.loadFromFile("player.png");
	sprite.setTexture(texture);
	pos_x = 0;
	pos_y = 0;
}

Player::Player(int pos_x, int pos_y) {
	texture.loadFromFile("player.png");
	sprite.setTexture(texture);
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

sf::Vector2f Player::getPosition() {
	return sprite.getPosition();
}

int Player::getMapPosX() {
	return pos_x;
}

int Player::getMapPosY() {
	return pos_y;
}

void Player::setPosition(sf::Vector2f newPosition) {
	sprite.setPosition(newPosition);
}

void Player::setMapPosX(int x) {
	pos_x = x;
}

void Player::setMapPosY(int y) {
	pos_y = y;
}

void Player::render(sf::RenderWindow * target) {
	target->draw(sprite);
}