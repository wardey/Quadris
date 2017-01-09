#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <vector>
#include <memory>
#include "Observer.h"
#include "Cell.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Block.h"
#include "Level.h"

class Board : public Observer {
	std::vector<std::vector<Cell *>> theGrid;  // The actual grid.
	std::vector<std::shared_ptr<Block>> liveBlocks;
	int gridHeight;
	int gridWidth;  // Size of the grid.
	std::unique_ptr<TextDisplay> td; // The text display.
	std::shared_ptr<Xwindow> xw;
	std::unique_ptr<GraphicsDisplay> gd;

	std::shared_ptr<Block> currBlock;
	BlockType nextBlock;
	std::unique_ptr<Level> currLevel;

	int level, score, highScore;
	int prevLevel;
	int cmdMult;
	int seed = 1;	//set to level when is constructed, default 1
	bool textOnly = false;

	//used for updating board when cell notifies
	std::vector<Cell *>tempptrs;
	std::vector<Info> newInfo;
	std::vector<bool> states;
	int notifyCounter = 0;

	void levelUp();//increase level by 1
	void levelDown();//reduce level by 1
	void checkRows();//check all rows to see which need to be deleted, shifts cells down, and calls addLineScore
	void removeRow(int r);//removes row r
	void shiftRows(int r);//shifts all rows down after a row is removed
	bool rowFull(int r);//check if row r is full
	void newBlock(); //spawn new block
	void dropBlock(); //drop current block
	void replaceBlock(BlockType bt); //replace current block with given input
	void hint(); //gives player hint for one turn
	void addLineScore(int r); //adds the score for deleting r number of lines in current level
	void checkDeadBlocks();//searches through liveblocks to see if any have been completely deleted in order to add score
	void addBlockScore(int l); //adds a block's score
	void redraw(); //tell gd to redraw, print td to cout
	void init(); //initialize a board, creates first and second block
	BlockType stringToBlockType(std::string s); //returns a blocktype that correspondes to the given string
	void spawnOneBlock(); //spawn a 1x1 block for level 4

public:
	Board(int highScore, bool textOnly, int initialLevel, int seed, std::string file);
	~Board() = default;

	void notify(Subject &whoNotified) override; //cells notify to update their position
	void commandHandler(std::string command, std::string arg=""); //takes a command from game and calls other methods accordingly, mostly for level 3, 4 and multiplier commands, calls redraw at the end
	void setLevel(int l); //sets the level to l
	bool checkOccupied(int x, int y); //check if a cell is occupied
	bool canSpawn(); //check if the next block can spawn in start location, game over if false
	void setSeed(int s); //set seed to s for using rand
	void setFile(std::string file);//sets the file to read input from
	void setMult(int m); //sets the multiplier for a command
//void TextOnly(bool b); //calls graphic display's enable with param b
	int getHighScore(); //returns the high score
	void attachCell(int x, int y, Cell *c); //attaches cell to the grid, and attach observers to the cell
	void testPrint();
	void update();
};

#endif
