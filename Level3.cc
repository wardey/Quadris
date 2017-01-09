#include "Level3.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Level3::Level3(int s, Board *b) {
	this->b = b;
    seed = s;
    srand(s);
}

Level3::~Level3(){}

BlockType Level3::createBlockType(){

    if (randomOn){
        int r = rand()%9; //0 - 8

        if (r <= 1){
            return BlockType::SBlock;
        }
        else if (r <= 3){
            return BlockType::ZBlock;
        }
        else if (r == 4){
            return BlockType::JBlock;
        }
        else if (r == 5){
            return BlockType::OBlock;
        }
        else if (r == 6){
            return BlockType::TBlock;
        }
        else if (r == 7){
            return BlockType::LBlock;
        }
        else if (r == 8){
            return BlockType::IBlock;
        }
    } 
    else {
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
}
