#include "Level1.h"
using namespace std;

Level1::Level1(int s, Board *b){
	this->b = b;
    seed = s;
    srand(s);
}

Level1::~Level1(){}

BlockType Level1::createBlockType(){
    int r = rand()%12; // 0-11

    if (r <= 1){
        return BlockType::JBlock;
    }
    else if (r <= 3){
        return BlockType::OBlock;
    }
    else if (r <= 5){
        return BlockType::IBlock;
    }
    else if (r <= 7){
        return BlockType::LBlock;
    }
    else if (r <= 9){
		return BlockType::TBlock;
    }
    else if (r == 10){
        return BlockType::ZBlock;
    }
    else {
        return BlockType::SBlock;
    }
}
