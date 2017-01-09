#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <memory>
#include "Subject.h"
#include "Info.h"
#include "Cell.h"
#include "Enums.h"
class Board;

class Block {
protected:
	Info ref;
	Orientation ori;
	Board * b;
	std::vector<std::shared_ptr<Cell>> components; // holds the 4 cells of a block
	std::vector<Info> pairs; // coordinates (11 x 15)
	std::vector<Info> tmppairs; // for rotating
	int level;

	void attachInfo(Info &i);
	bool notInInfo(int, int);
	bool canMoveDown();

	//for rotating every block except Iblock
	void copyPairs();
	void cwrotate();
	void ccwrotate();
	void shift(int x, int y);
	bool checkCoords();

public:
	Block();
	void moveRight();
	void moveLeft();
	void moveDown();
	virtual void CW() = 0;
	virtual void CCW() = 0;
	void drop();
	bool checkCells();
	bool canSpawn(); //checks if block can spawn in its given coordinates
	void init(); //attaches cells to grid
	void attachCell(std::shared_ptr<Cell>);
	void disable();
	void setLevel(int l);
	int getLevel();

	virtual ~Block();
};

#endif
