#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include "Block.h"

class JBlock : public Block {
	
public:
	JBlock(Board*);
	~JBlock() = default;

	void CW() override;
	void CCW() override;
};

#endif
