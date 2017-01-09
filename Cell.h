#ifndef _CELL_H_
#define _CELL_H_
#include "Enums.h"
#include "Subject.h"
#include "Info.h"

class Cell : public Subject{
	int x, y, level;
	bool isEnabled;
	BlockType cellType;
	Info prevInfo;

public:
	Cell();
	Cell(int x, int y, int l, bool enabled, BlockType bt);
	Info getInfo() const override;
	Info getPrevInfo() const override;
	bool getState() const override;
	void enable();
	void disable();
	void setLevel(int l);
	void setBlockType(BlockType bt);
	void setCoords(int x, int y);
};
#endif
