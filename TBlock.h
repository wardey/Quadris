#ifndef _TBLOCK_H_
#define _TBLOCK_H_
#include "Block.h"
class TBlock : public Block {

public:
	TBlock(Board*);
	~TBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
