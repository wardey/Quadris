#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <fstream>
#include <string>
#include <memory>
#include "Enums.h"
class Board;
class Block;

class Level {
protected:
	bool randomOn = true;
    Board * b;
    std::ifstream source;
    int seed;
	int count; //only used for lvl 4
    int level;

    bool fileExists(std::string s);
public:
    std::shared_ptr<Block> createBlock(BlockType);
	virtual BlockType createBlockType() = 0;
    void setFile(std::string);
    //void readFile();
    //void setSeed(int);
	int getCount();
	void clearCount();
	void setrandomOn(bool b); //onyl useful for level 3 and 4, turning on and off random
    virtual ~Level();

};

#endif
