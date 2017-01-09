#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include "Block.h"
class OBlock : public Block {

public:
	OBlock(Board*);
	~OBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
