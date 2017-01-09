#include "OneBlock.h"
using namespace std;

OneBlock::OneBlock(Board * brd){
    shared_ptr<Cell> cp = make_shared<Cell>(5, 14, level, true, BlockType::OneBlock);
    Info i = {5,14, BlockType::OneBlock, 2};
    this->attachCell(cp);
    this->attachInfo(i);
    ori = Orientation::Up;
    ref.x = 5;
    ref.y = 14;
    b = brd;
	init();
}

void OneBlock::CW(){
    return;
}

void OneBlock::CCW(){
    return;
}
