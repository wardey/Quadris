#include "TBlock.h"
using namespace std;

TBlock::TBlock(Board * brd) {
	shared_ptr<Cell> cp1 = make_shared<Cell>(0, 14, level, true, BlockType::TBlock);
	shared_ptr<Cell> cp2 = make_shared<Cell>(1, 14, level, true, BlockType::TBlock);
	shared_ptr<Cell> cp3 = make_shared<Cell>(1, 13, level, true, BlockType::TBlock);
	shared_ptr<Cell> cp4 = make_shared<Cell>(2, 14, level, true, BlockType::TBlock);
	Info i1 = { 0, 14, BlockType::TBlock, 2 };
	Info i2 = { 1, 14, BlockType::TBlock, 2 };
	Info i3 = { 1, 13, BlockType::TBlock, 2 };
	Info i4 = { 2, 14, BlockType::TBlock, 2 };
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


void TBlock::CW() { //shifts tmppairs accordingly in order to rotate, ori -1
	copyPairs();
	switch (ori) {
	case Orientation::Up:
		cwrotate();
		if (checkCoords()) ori = Orientation::Right;
		break;
	case Orientation::Right:
		cwrotate();
		shift(0, -1);
		if (checkCoords()) ori = Orientation::Down;
		break;
	case Orientation::Down:
		cwrotate();
		if (checkCoords()) ori = Orientation::Left;
		break;
	case Orientation::Left:
		cwrotate();
		shift(0, -1);
		if (checkCoords()) ori = Orientation::Up;
		break;
	}
}

void TBlock::CCW() { //shifts tmppairs accordingly in order to rotate, ori +1
	copyPairs();
	switch (ori) {
	case Orientation::Up:
		ccwrotate();
		shift(-1, 0);
		if (checkCoords()) ori = Orientation::Left;
		break;
	case Orientation::Right:
		ccwrotate();
		if (checkCoords()) ori = Orientation::Up;
		break;
	case Orientation::Down:
		ccwrotate();
		shift(-1, 0);
		if (checkCoords()) ori = Orientation::Right;
		break;
	case Orientation::Left:
		ccwrotate();
		if (checkCoords()) ori = Orientation::Down;
		break;
	}
}
