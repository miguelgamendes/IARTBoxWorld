#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Warehouse Keeper");
	sf::Texture tileset;
	sf::Sprite tile;
	tile.setTexture(tileset);
	tile.setTextureRect(sf::IntRect(0, 0, 16, 24));
	if (!tileset.loadFromFile("tileset.png")) {
		std::cout << "Couldn't load tileset, make sure it's in the correct directory!";
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(tile);
		window.display();
	}

	return 0;
}