#include "Spinner.h"

Spinner::Spinner(int pos_x, int pos_y, sf::Text text) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->text = text;
	this->sprite.setTexture(texture);
	this->sprite.setPosition(pos_x, pos_y);
}

Spinner::Spinner(int pos_x, int pos_y, sf::Text text, int *target) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->text = text;
	this->target = target;
	this->sprite.setTexture(texture);
	this->sprite.setPosition(pos_x, pos_y);
}

Spinner::~Spinner() {

}

void Spinner::drawSpinner(sf::RenderWindow& window) {
	window.draw(this->sprite);
	window.draw(this->text);
}