#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include "Block.h"
class IBlock : public Block {
	void iRotate();
public:
	IBlock(Board*);
	~IBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
