#ifndef _LEVEL0_H_
#define _LEVEL0_H_
#include "Level.h"
class Level0 : public Level {
    int level = 0;
public:
    BlockType createBlockType();
    Level0(int, Board*); // no arg cuz not random
	~Level0() = default;
};

#endif
