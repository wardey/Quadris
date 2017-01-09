#include "Block.h"
#include "Board.h"
#include <memory>
#include <vector>
using namespace std;

//for all intensive purposes, components and pairs always have the same size, usually 4
bool Block::notInInfo(int x, int y) {
	for (int c = 0; c < components.size(); ++c) {
		if (pairs[c].x == x && pairs[c].y == y) {
			return false;
		}
	}
	return true;
}

void Block::moveRight() {
	for (int d = 0; d < components.size(); ++d) {
		if (b->checkOccupied(pairs[d].x + 1, pairs[d].y)
			&& notInInfo(pairs[d].x + 1, pairs[d].y)) {
			return;
		}
	}
	for (int c = 0; c < components.size(); ++c) {
		pairs[c].x++;
		components[c]->setCoords(pairs[c].x, pairs[c].y);
	}
	ref.x++;
}

void Block::moveLeft() {
	for (int d = 0; d < components.size(); ++d) {
		if (b->checkOccupied(pairs[d].x - 1, pairs[d].y)
			&& notInInfo(pairs[d].x - 1, pairs[d].y)) {
			return;
		}
	}
	for (int c = 0; c < components.size(); ++c) {
		pairs[c].x--;
		components[c]->setCoords(pairs[c].x, pairs[c].y);
	}
	ref.x--;
}

bool Block::canMoveDown() {
	for (int c = 0; c < components.size(); ++c) {
		if (b->checkOccupied(pairs[c].x, pairs[c].y - 1)
			&& notInInfo(pairs[c].x, pairs[c].y - 1)) {
			return false;
		}
	}
	return true;
}

void Block::moveDown() {
	if (canMoveDown()) {
		for (int c = 0; c < components.size(); ++c) {
			pairs[c].y--;
			components[c]->setCoords(pairs[c].x, pairs[c].y);
		}
		ref.y--;
	}
}

void Block::drop() {
	while (canMoveDown()) {
		moveDown();
		b->update();
	}
}

bool Block::checkCells() {
	for (int c = 0; c < components.size(); ++c) {
		if (components[c]->getState()) {
			return false;
		}
	}
	return true;
}

void Block::init() {
	if (!canSpawn()) {
		throw("GameOver");
	}
	for (int i = 0; i < components.size(); i++) {
		Info tmp = components[i]->getInfo();
		b->attachCell(tmp.x, tmp.y, &(*components[i]));
		components[i]->notifyObservers();
	}
}

void Block::attachInfo(Info &i) {
	pairs.emplace_back(i);
}

void Block::attachCell(shared_ptr<Cell> c) {
	components.emplace_back(c);
}

bool Block::canSpawn() {
	for (int i = 0; i < components.size(); i++) {
		Info tmp = components[i]->getInfo();
		if (b->checkOccupied(tmp.x, tmp.y)) return false;
	}
	return true;
}

void Block::disable() {
	for (int i = 0; i < components.size(); i++) {
		components[i]->disable();
	}
}

void Block::setLevel(int l) {
	level = l;
}

int Block::getLevel() {
	return level;
}

Block::Block() {}

Block::~Block() {}
	/**
	void setCoords();
	void drop();
	void redraw();
	void checkCells();
	void init();
	void attachCell(Cell);
	*/

//rotation helper methods
void Block::copyPairs() {
	for (int i = 0; i < pairs.size(); i++) {
		tmppairs.emplace_back(pairs[i]);
	}
}

void Block::cwrotate() { //rotates tmppairs clock wise to get desired location
	for (int i = 0; i < tmppairs.size(); i++) {
		if (tmppairs[i].x == ref.x && tmppairs[i].y == ref.y) {}
		int tmpx = tmppairs[i].x - ref.x;
		int tmpy = tmppairs[i].y - ref.y;
		tmppairs[i].x = tmpy + ref.x;
		tmppairs[i].y = -tmpx + ref.y;
	}
}

void Block::ccwrotate() { //rotates tmppairs counter clock wise to get desired location
	for (int i = 0; i < tmppairs.size(); i++) {
		if (tmppairs[i].x == ref.x && tmppairs[i].y == ref.y) {}
		int tmpx = tmppairs[i].x - ref.x;
		int tmpy = tmppairs[i].y - ref.y;
		tmppairs[i].x = -tmpy + ref.x;
		tmppairs[i].y = tmpx + ref.y;
	}
}

void Block::shift(int x, int y) { //shifts tmppairs x horizontally, y vertically
	for (int i = 0; i < tmppairs.size(); i++) {
		tmppairs[i].x += x;
		tmppairs[i].y += y;
	}
}

bool Block::checkCoords() { //check if tmppairs is a valid set of coordinates for block, ignoring cells that were part of the block pre-rotate, 
	for (int i = 0; i < tmppairs.size(); i++) {	//assigns new coords to cells and clears tmppair
		if (notInInfo(tmppairs[i].x, tmppairs[i].y) && b->checkOccupied(tmppairs[i].x, tmppairs[i].y)) {
			tmppairs.clear();
			return false;
		}
	}
	for (int i = 0; i < pairs.size(); i++) {
		pairs[i] = tmppairs[i]; //notify observers when rotating, use set coords???????? or something...... idk just fix
		components[i]->setCoords(pairs[i].x, pairs[i].y);
	}
	tmppairs.clear();
	return true;
}
