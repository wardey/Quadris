#include "IBlock.h"
#include <iostream>
using namespace std;

IBlock::IBlock(Board * brd) {
	shared_ptr<Cell> cp1 = make_shared<Cell>(0, 14, level, true, BlockType::IBlock);
	shared_ptr<Cell> cp2 = make_shared<Cell>(1, 14, level, true, BlockType::IBlock);
	shared_ptr<Cell> cp3 = make_shared<Cell>(2, 14, level, true, BlockType::IBlock);
	shared_ptr<Cell> cp4 = make_shared<Cell>(3, 14, level, true, BlockType::IBlock);
	Info i1 = { 0, 14, BlockType::IBlock, 2 };
	Info i2 = { 1, 14, BlockType::IBlock, 2 };
	Info i3 = { 2, 14, BlockType::IBlock, 2 };
	Info i4 = { 3, 14, BlockType::IBlock, 2 };
	this->attachCell(cp1);
	this->attachCell(cp2);
	this->attachCell(cp3);
	this->attachCell(cp4);
	this->attachInfo(i1);
	this->attachInfo(i2);
	this->attachInfo(i3);
	this->attachInfo(i4);
	ori = Orientation::Right;
	ref.x = 0;
	ref.y = 14;
	b = brd;
	init();
}


void IBlock::CW() { //special rotate for iblock
	iRotate();
}

void IBlock::CCW() { //special rotate for iblock
	iRotate();
}

void IBlock::iRotate() {
	copyPairs();
	cerr << "1";
	switch (ori) {
	case Orientation::Up:
		for (int i = 0; i < tmppairs.size(); i++) {
			int tmpx = ref.x + i;
			int tmpy = ref.y;
			tmppairs[i].x = tmpx;
			tmppairs[i].y = tmpy;
		}
		if (checkCoords()) ori = Orientation::Right;
		return;
	case Orientation::Right:
		cerr << "2";
		for (int i = 0; i < tmppairs.size(); i++) {
			int tmpx = ref.x;
			int tmpy = ref.y + i;
			tmppairs[i].x = tmpx;
			tmppairs[i].y = tmpy;
		}
		cerr << "3";
		if (checkCoords()) ori = Orientation::Up;
		cerr << "4";
		return;
	}
}
