#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_
#include "Block.h"
class ZBlock : public Block {

public:
	ZBlock(Board*);
	~ZBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
