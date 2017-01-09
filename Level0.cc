#include "Level0.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Level0::Level0(int s, Board *b){
	this->b = b;
    seed = s;
    //srand(s);
}

BlockType Level0::createBlockType(){
    string word;
    if (source >> word){
      if (word == "J"){
            return BlockType::JBlock;
        }
        else if (word == "O"){
            return BlockType::OBlock;
        }
        else if (word == "S"){
            return BlockType::SBlock;
        }
        else if (word == "Z"){
            return BlockType::ZBlock;
        }
        else if (word == "T"){
            return BlockType::TBlock;
        }
        else if (word == "L"){
            return BlockType::LBlock;
        }
        else if (word == "I"){
            return BlockType::IBlock;
        }
    }  
    else {
		source.clear();
		source.seekg(0, source.beg);
		return createBlockType();
		//throw("EOF");
    }
}
