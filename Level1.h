#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include "Level.h"
class Level1 : public Level {
    int level = 1;
public:
    BlockType createBlockType();
    Level1(int, Board*);
    ~Level1();
};

#endif
