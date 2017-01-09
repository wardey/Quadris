#ifndef _ONEBLOCK_H_
#define _ONEBLOCK_H_
#include "Block.h"

class OneBlock : public Block {

public:
    void CW() override;
    void CCW() override;
    OneBlock(Board*);
	~OneBlock() = default;
};

#endif
