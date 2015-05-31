#include "map.h"
#include <iostream>

map::map(int width, int height) :
	player(1, 1)
{
	this->width = width;
	this->height = height;
	this->tiles.resize(height, std::vector<tile>(width, tile(3)));
}

map::map(int width, int height, int pos_x, int pos_y) :
	player(1, 1)
{
	this->width = width;
	this->height = height;
	this->tiles.resize(height, std::vector<tile>(width, tile(3)));
	this->pos_x = pos_x;
	this->pos_y = pos_y;

	player.setPosition(sf::Vector2f(pos_x, pos_y));
}

map::~map()
{
}

void map::setTile(tile tile, int x, int y)
{
	this->tiles[x][y] = tile;
}

void map::setPlayerPosition(int x, int y) {
	player.setMapPosX(x);
	player.setMapPosY(y);
}

int map::getTileValue(int x, int y) {
	return tiles[y][x].getSelector();
}

sf::FloatRect map::getMapBounds() {
	if ((this->width >= 1) && (this->height >= 1)) {
		return sf::FloatRect(this->tiles[0][0].getTile().getGlobalBounds().left, this->tiles[0][0].getTile().getGlobalBounds().top, this->width * 16, this->height * 16 + 8);
	}
	return sf::FloatRect(0, 0, 0, 0);
}

int map::getPlayerPosX() {
	return player.getMapPosX();
}

int map::getPlayerPosY() {
	return player.getMapPosY();
}

void map::modifyWidth(int rate) {
	this->width += rate;
	if (width >= 1) {
		if (rate > 0) {
			for (int i = 0; i < this->tiles.size(); ++i) {
				this->tiles[i].push_back(tile(3));
			}
		}
		else if (rate < 0) {
			for (int i = 0; i < this->tiles.size(); ++i) {
				this->tiles[i].erase(this->tiles[i].end() - 1);
			}
		}
	}
	else this->width = 1;
}

void map::modifyHeight(int rate) {
	this->height += rate;
	if (height >= 1) {
		if (rate > 0) {
			this->tiles.push_back(std::vector<tile>(this->width, tile(3)));
		}
		else if (rate < 0) {
			this->tiles.erase(this->tiles.end() - 1);
		}
	}
	else this->height = 1;
}

void map::drawMap(sf::RenderWindow& window) {
	for (int i = 0; i < this->tiles.size(); ++i) {
		for (int j = 0; j < this->tiles[i].size(); ++j) {
			this->tiles[i][j].getTile().setPosition(this->pos_x + j * 16, this->pos_y + i * 16);
			window.draw(this->tiles[i][j].getTile());

			//for drawing the player
			if(i == player.getMapPosY() && j == player.getMapPosX()) {
				player.setPosition(sf::Vector2f(pos_x + player.getMapPosX() * 16, pos_y + player.getMapPosY() * 16));
				window.draw(player.sprite);
			}
		}
	}
}

int map::distance(Node n1, Node n2) {
	if(tiles[n2.getX()][n2.getY()].getSelector() >= 9 &&
		tiles[n2.getX()][n2.getY()].getSelector() <= 11)
		return 1000;
	else
		return 1;
}

int map::heuristic(Node n, int destX, int destY) {
	return std::abs(destX - n.getX()) + std::abs(destY - n.getY());
}

std::vector<int> map::reconstructPath(Node n) {
	/*
	std::vector<int> result; //collection of coordinate values to return
	std::vector<Node> path; //all nodes leading from starting point to goal
	Node current = n;

	//reconstruct node path
	path.push_back(current);
	while(current.getOrigin()){
		current = *(current.getOrigin());
		path.push_back(current);
	}
	path.push_back(current);

	//organize path coordinates
	for(int i = path.size() - 1; i >= 0; i--) {
		result.push_back(path[i].getX());
		result.push_back(path[i].getY());
	}*/

	std::vector<int> result;

	int currentX = n.getX();
	int currentY = n.getY();
	while(currentX != 0 && currentY != 0) {
		result.insert(result.begin(), currentY);
		result.insert(result.begin(), currentX);
		int tempX = currentX;
		currentX = cameFrom[currentX][currentY][0];
		currentY = cameFrom[tempX][currentY][1];
	}

	return result;
}

std::vector<int> map::findpath(int originX, int originY, int destinationX, int destinationY) {
	std::vector<Node> processed;
	//std::priority_queue<Node, std::vector<Node>, compareNodes> unprocessed;
	std::vector<Node> unprocessed;
	std::vector<Node> assist;
	
	cameFrom[originX][originY][0] = 0;
	cameFrom[originX][originY][1] = 0;
	Node current(0, 0); //the current node to analyze
	
	//every operation to the priority queue must be accompanied by operations to the assisting vector
	unprocessed.push_back(Node(originX, originY, 0, (std::abs(destinationX - originX) + std::abs(destinationY - originY)))); //put first node in unprocessed nodes
	assist.push_back(unprocessed.back());

	while(!unprocessed.empty()) {
		int lowestIndex = 0;
		for(int i = 0, j = 1000000; i < unprocessed.size(); i++) {
			if(unprocessed[i].getfx() < j){
				j = unprocessed[i].getfx();
				lowestIndex = i;
			}
		}
		current = unprocessed[lowestIndex];
		if(current.getX() == destinationX && current.getY() == destinationY)
			return reconstructPath(current);

		for(int i = 0; i < assist.size(); i++) {
			if(assist[i].getX() == current.getX() && assist[i].getY() == current.getY())
				assist.erase(assist.begin() + i);
		}
		unprocessed.erase(unprocessed.begin() + lowestIndex);
		processed.push_back(current);

		//get neighbours of current Node
		std::vector<Node> neighbours;
		if(getTileValue(current.getX()+1, current.getY()) >= 6 &&
			getTileValue(current.getX()+1, current.getY()) <= 11) //here we evaluate passable tiles manually, according to the established tileset
			neighbours.push_back(Node(current.getX()+1, current.getY()));
		if(getTileValue(current.getX(), current.getY()+1) >= 6 &&
			getTileValue(current.getX()+1, current.getY()+1) <= 11)
			neighbours.push_back(Node(current.getX(), current.getY()+1));
		if(getTileValue(current.getX()-1, current.getY()) >= 6 &&
			getTileValue(current.getX()-1, current.getY()) <= 11)
			neighbours.push_back(Node(current.getX()-1, current.getY()));
		if(getTileValue(current.getX(), current.getY()-1) >= 6 &&
			getTileValue(current.getX(), current.getY()-1) <= 11)
			neighbours.push_back(Node(current.getX(), current.getY()-1));

		//process neighbours
		for(int i = 0; i < neighbours.size(); i++) {
			//check if neighbour has been processed
			bool processedCheck = false;
			for(int j = 0; j < processed.size(); j++) {
				if(neighbours[i].getX() == processed[j].getX() &&
					neighbours[i].getY() == processed[j].getY())
					processedCheck = true;
			}
			if(processedCheck)
				continue;
			int possibleGX = current.getgx() + distance(current, neighbours[i]);

			bool unprocessedCheck = false;
			for (int j = 0; j < assist.size(); j++) {
				if(neighbours[i].getX() == assist[j].getX() &&
					neighbours[i].getY() == assist[j].getY())
					unprocessedCheck = true;
			}
			if(!unprocessedCheck || possibleGX < current.getgx()) {
				//neighbours[i].cameFrom(&processed[processed.size()-1]);
				cameFrom[neighbours[i].getX()][neighbours[i].getY()][0] = current.getX();
				cameFrom[neighbours[i].getX()][neighbours[i].getY()][1] = current.getY();
				neighbours[i].setgx(possibleGX);
				neighbours[i].sethx(heuristic(neighbours[i], destinationX, destinationY));
				if(!unprocessedCheck)
					unprocessed.push_back(neighbours[i]);
			}
		}
	}
}