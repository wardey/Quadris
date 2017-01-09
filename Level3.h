#ifndef _LEVEL3_H_
#define _LEVEL3_H_
#include "Level.h"
class Level3 : public Level {
    int level = 3;
public:
    BlockType createBlockType();
    Level3(int, Board *);
    ~Level3();
};

#endif
