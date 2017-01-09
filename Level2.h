#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include "Level.h"
class Level2 : public Level {
    int level = 2;
public:
    BlockType createBlockType();
    Level2(int, Board *);
    ~Level2();
};

#endif
