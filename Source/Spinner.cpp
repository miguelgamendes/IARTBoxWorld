#include "Spinner.h"

Spinner::Spinner(int pos_x, int pos_y, std::string text, int *target) {
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->text = text;
	this->target = target;
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 16, 24));
	this->sprite.setPosition(pos_x, pos_y);
}

Spinner::~Spinner() {

}
