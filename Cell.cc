#include "Cell.h"
#include <iostream>
using namespace std;

Cell::Cell(int x, int y, int l, bool enabled, BlockType bt) :
	x{ x }, y{ y }, isEnabled{ enabled }, level{ l }, cellType{ bt } {
	prevInfo = Info{ x,y,bt,level };
	notifyObservers();
}

Cell::Cell(): x{ 0 }, y{ 0 }, isEnabled{ false }, level{ 0 } {}

Info Cell::getInfo() const {
	return Info{ x,y,cellType,level };
}

Info Cell::getPrevInfo() const{
	return prevInfo;
}

bool Cell::getState() const {
	return isEnabled;
}

void Cell::enable() {
	isEnabled = true;
	notifyObservers();
}

void Cell::disable() {
	isEnabled = false;
	prevInfo = getInfo();
	notifyObservers();
}

void Cell::setLevel(int l) { //one time call
	level = l;
}

void Cell::setBlockType(BlockType bt) { //one time call
	cellType = bt;
}

void Cell::setCoords(int x, int y) {
	prevInfo.x = this->x;
	prevInfo.y = this->y;
	this->x = x;
	this->y = y;
	notifyObservers();
}
