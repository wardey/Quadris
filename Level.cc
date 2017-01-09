#include "Level.h"
#include "TBlock.h"
#include "JBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "OBlock.h"
#include "LBlock.h"
#include "IBlock.h"
#include "OneBlock.h"
#include <iostream>
#include <string>
using namespace std;
//shared_ptr<Block> createBlock() = 0;
//void setFile(string);
//void readFile();


bool Level::fileExists(string s){   
	if (s == "") return false;
    ifstream infile(s);
    return infile.good();
}

void Level::setFile(string s){
    if (fileExists(s)){ // if file exists
		source.open(s);
    } 
	else {
		source.open("sequence.txt");
    }
}
/**
void Level::setSeed(int s){
    seed = s;
    srand(s);
}*/

int Level::getCount() {
	return count;
}

void Level::clearCount() {
	count = 0;
}

void Level::setrandomOn(bool b) { //for level 3 and 4, turning on and off random
	randomOn = b;
}

Level::~Level(){}

shared_ptr<Block> Level::createBlock(BlockType bt){
    if (bt == BlockType::JBlock){
        shared_ptr<JBlock> jb = make_shared<JBlock>(b);
        jb->setLevel(level);
        return jb;
    }
    else if (bt == BlockType::OBlock){
        shared_ptr<OBlock> ob = make_shared<OBlock>(b);
        ob->setLevel(level);
        return ob;
    }
    else if (bt == BlockType::IBlock){
        shared_ptr<IBlock> ib = make_shared<IBlock>(b);
        ib->setLevel(level);
        return ib;
    }
    else if (bt == BlockType::LBlock){
        shared_ptr<LBlock> lb = make_shared<LBlock>(b);
        lb->setLevel(level);
        return lb;
    }
    else if (bt == BlockType::TBlock){
        shared_ptr<TBlock> tb = make_shared<TBlock>(b);
        tb->setLevel(level);
        return tb;
    }
    else if (bt == BlockType::ZBlock){
        shared_ptr<ZBlock> zb = make_shared<ZBlock>(b);
        zb->setLevel(level);
        return zb;
    }
    else if (bt == BlockType::SBlock){
        shared_ptr<SBlock> sb = make_shared<SBlock>(b);
        sb->setLevel(level);
        return sb;
    }
    else if (bt == BlockType::OneBlock){
        shared_ptr<OneBlock> oneb = make_shared<OneBlock>(b);
        oneb->setLevel(level);
        return oneb;
    }
}
