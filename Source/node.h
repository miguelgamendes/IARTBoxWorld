#pragma once

#include <vector>

class Node {
	int posX;
	int posY;
	int gx; //distance travelled so far
	int hx; //heuristic, predicted distance to target
	Node * origin;
	std::vector<Node*> neighbours;

public:
	//constructors
	Node(int x, int y);
	Node(int x, int y, int g, int h);

	//getters
	int getX();
	int getY();
	int getgx() const;
	int gethx() const;
	int getfx() const;
	Node * getOrigin();

	//setters
	void setgx(int g);
	void sethx(int h);
	void cameFrom(Node * n);
};