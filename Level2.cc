#include "Level2.h"
using namespace std;
Level2::Level2(int s, Board *b){
	this->b = b;
    seed = s;
    srand(s);
}

Level2::~Level2(){}

BlockType Level2::createBlockType(){
    int r = rand()%7;

    if (r == 0){
        return BlockType::JBlock;
    }
    else if (r == 1){
        return BlockType::OBlock;
    }
    else if (r==2){
        return BlockType::SBlock;
    }
    else if (r == 3){
        return BlockType::ZBlock;
    }
    else if (r==4){
        return BlockType::TBlock;
    }
    else if (r == 5){
        return BlockType::LBlock;
    }
    else if (r==6){
        return BlockType::IBlock;
    }
}
