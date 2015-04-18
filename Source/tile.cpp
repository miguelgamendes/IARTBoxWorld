#include "tile.h"

tile::tile(int selector)
{
	this->sprite.setTexture(tileset);
	div_t divres;
	divres = div(selector, 3);
	this->sprite.setTextureRect(sf::IntRect((divres.rem * 16 + divres.rem), (divres.quot * 24 + divres.quot), 16, 24));
}

tile::~tile()
{
}

void tile::setSelector(int selector) {
	div_t divres;
	divres = div(selector, 3);
	this->sprite.setTextureRect(sf::IntRect((divres.rem * 16 + divres.rem), (divres.quot * 24 + divres.quot), 16, 24));
}