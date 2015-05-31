#include "node.h"

Node::Node(int x, int y) {
	posX = x;
	posY = y;
}

Node::Node(int x, int y, int g, int h) {
	posX = x;
	posY = y;
	gx = g;
	hx = h;
}

int Node::getX() {
	return posX;
}

int Node::getY() {
	return posY;
}

int Node::getgx() const {
	return gx;
}

int Node::gethx() const {
	return hx;
}

int Node::getfx() const {
	return gx + hx;
}

Node * Node::getOrigin() {
	return origin;
}

void Node::setgx(int g) {
	gx = g;
}

void Node::sethx(int h) {
	hx = h;
}

void Node::cameFrom(Node * n) {
	origin = n;
}