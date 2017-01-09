#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include "Block.h"
class SBlock : public Block {

public:
	SBlock(Board*);
	~SBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
