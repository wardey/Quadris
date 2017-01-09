#include "OBlock.h"
using namespace std;

OBlock::OBlock(Board * brd) {
	shared_ptr<Cell> cp1 = make_shared<Cell>(0, 14, level, true, BlockType::OBlock);
	shared_ptr<Cell> cp2 = make_shared<Cell>(1, 14, level, true, BlockType::OBlock);
	shared_ptr<Cell> cp3 = make_shared<Cell>(0, 13, level, true, BlockType::OBlock);
	shared_ptr<Cell> cp4 = make_shared<Cell>(1, 13, level, true, BlockType::OBlock);
	Info i1 = { 0, 14, BlockType::OBlock, 2 };
	Info i2 = { 1, 14, BlockType::OBlock, 2 };
	Info i3 = { 0, 13, BlockType::OBlock, 2 };
	Info i4 = { 1, 13, BlockType::OBlock, 2 };
	this->attachCell(cp1);
	this->attachCell(cp2);
	this->attachCell(cp3);
	this->attachCell(cp4);
	this->attachInfo(i1);
	this->attachInfo(i2);
	this->attachInfo(i3);
	this->attachInfo(i4);
	ori = Orientation::Up;
	ref.x = 1;
	ref.y = 14;
	b = brd;
	init();
}


void OBlock::CW() { //does nothing
	return;
}

void OBlock::CCW() { //does nothing
	return;
}
