#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include "Block.h"
class LBlock : public Block {

public:
	LBlock(Board*);
	~LBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
