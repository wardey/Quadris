#ifndef _LEVEL4_H_
#define _LEVEL4_H_
#include "Level.h"
class Level4 : public Level {
    int level = 4;
public:
    BlockType createBlockType();
    Level4(int, Board *);
    ~Level4();
};

#endif
