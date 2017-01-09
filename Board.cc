#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Board.h"
#include "Enums.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
using namespace std;

Board::Board(int highScore, bool textOnly, int initialLevel, int seed, std::string file) 
	: gridWidth{ 11 }, gridHeight{ 18 }, level{ initialLevel }, prevLevel{ initialLevel }, score{ 0 }, highScore{ highScore }, cmdMult{ 1 }, textOnly{ textOnly }, seed{ seed } {
	for (int i = 0; i < gridWidth; i++) {
		theGrid.emplace_back(vector<Cell *>{});
		for (int j = 0; j < gridHeight; j++) {
			theGrid[i].emplace_back(nullptr);
		}
	}
	setLevel(initialLevel);
	setFile(file);
	init(); //makes both displays
}

void Board::init() { //initialize a board and creates both displays with initialized values, also creates first block
	BlockType first = currLevel->createBlockType();
	td = make_unique<TextDisplay>(highScore, score, level, nextBlock); 
	if (!textOnly) {
		xw = make_shared<Xwindow>(500, 800); //board is 330 x 540, each cell is 30 x 30
		gd = make_unique<GraphicsDisplay>(&(*xw));
		gd->updateHighScore(highScore);
		gd->updateLevel(level);
		gd->updateScore(score);
	} 
	currBlock = currLevel->createBlock(first);
	currBlock->setLevel(level);
	nextBlock = currLevel->createBlockType();
	td->updateNext(nextBlock);
	if(!textOnly) gd->updateNext(nextBlock);
	redraw();
}

void Board::notify(Subject &whoNotified) {
	Info info = whoNotified.getInfo();
	Info prevInfo = whoNotified.getPrevInfo();
	theGrid[prevInfo.x][prevInfo.y] = nullptr;
	newInfo.emplace_back(info);
	tempptrs.emplace_back(&(dynamic_cast<Cell&>(whoNotified)));
	states.emplace_back(whoNotified.getState());
	notifyCounter++;
}

void Board::update() {
	for (int i = 0; i < notifyCounter; i++) {
		if (states[i])
			theGrid[newInfo[i].x][newInfo[i].y] = tempptrs[i];
	}
	notifyCounter = 0;
	tempptrs.clear();
	states.clear();
	newInfo.clear();
	td->update();
	if (!textOnly) gd->update();
}

void Board::commandHandler(string command, string arg) { //multiplier should be set before calling this method break for movement/rotation of block, 
															//returns otherwise
	if (command == "left") {
		for (int i = 0; i < cmdMult; i++) {
			currBlock->moveLeft();
			update();
		}
	}
	else if (command == "right") {
		for (int i = 0; i < cmdMult; i++) {
			currBlock->moveRight();
			update();	
		}
	}
	else if (command == "down") {
		for (int i = 0; i < cmdMult; i++) {
			currBlock->moveDown();
			update();
		}
	}
	else if (command == "clockwise") {
		for (int i = 0; i < cmdMult; i++) {
			currBlock->CW();
			update();
		}
	}
	else if (command == "counterclockwise") {
		for (int i = 0; i < cmdMult; i++) {
			currBlock->CCW();
			update();
		}
	}
	else if (command == "drop") {			//lvl 3+ heaviness does not apply for commands below
		for (int i = 0; i < cmdMult; i++) {
			dropBlock();
			update();
		}
		redraw();
		return;
	}
	else if (command == "levelup") {
		prevLevel = level;
		for (int i = 0; i < cmdMult; i++) {
			levelUp();
		}
		redraw();
		return;
	}
	else if (command == "leveldown") {
		prevLevel = level;
		for (int i = 0; i < cmdMult; i++) {
			levelDown();
		}
		redraw();
		return;
	}
	else if (command == "norandom") {
		if (level >= 3) {
			currLevel->setrandomOn(false);
			if (arg != "") {
				currLevel->setFile(arg);
			}
		}
		return;
	}
	else if (command == "random") {
		if (level >= 3) {
			currLevel->setrandomOn(true);
		}
		return;
	}
	else if (command == "replaceBlock") {
		replaceBlock(stringToBlockType(arg));
		update();
		redraw();
		return;
	}
	else if (command == "hint") {
		hint();
		redraw();
		return;
	}
	else {
		return;
	}

	//apply heaviness and redraw for movement and rotation commands
	if (level >= 3) {
		currBlock->moveDown();
	}
	redraw();
}

void Board::setLevel(int l) { //sets currlevel to l
	level = l;
	switch (l) {
		case 0:
		currLevel = make_unique<Level0>(seed, this);
			break;
		case 1:
			currLevel = make_unique<Level1>(seed, this);
			break;
		case 2:
			currLevel = make_unique<Level2>(seed, this);
			break;
		case 3:
			currLevel = make_unique<Level3>(seed, this);
			break;
		case 4:
			currLevel = make_unique<Level4>(seed, this);
			break;
		default:
			currLevel = make_unique<Level0>(seed, this);
	}
}

void Board::levelUp() {		//increase level by 1
	if(level == 4) return;
	switch (level) {
		case 0:
			currLevel = make_unique<Level1>(seed, this);
			break;
		case 1:
			currLevel = make_unique<Level2>(seed, this);
			break;
		case 2:
			currLevel = make_unique<Level3>(seed, this);
			break;
		case 3:
			currLevel = make_unique<Level4>(seed, this);
			break;
		case 4:
			return;
		default:
			return;
	}
	level++;
	td->updateLevel(level);
	if (!textOnly) gd->updateLevel(level);
}

void Board::levelDown() {		//reduce level by 1
	if (level == 0) return;
	switch (level) {
		case 0:
			return;
		case 1:
			currLevel = make_unique<Level0>(seed, this);
			break;
		case 2:
			currLevel = make_unique<Level1>(seed, this);
			break;
		case 3:
			currLevel = make_unique<Level2>(seed, this);
			break;
		case 4:
			currLevel = make_unique<Level3>(seed, this);
			break;
		default:
			return;
	}
	level--;
	td->updateLevel(level);
	if (!textOnly) gd->updateLevel(level);
}

void Board::checkRows() {	//check all rows to see which need to be deleted, shifts cells down, and calls addLineScore
	int deletecounter = 0;
	for (int i = 0; i < gridHeight; i++) {
		if (rowFull(i)) {
			removeRow(i);
			checkDeadBlocks();
			currLevel->clearCount();
			shiftRows(i);
			update();
			i--;
			deletecounter++;
		}
	}
	if (deletecounter != 0) {
		addLineScore(deletecounter);
	}
}

void Board::removeRow(int r) { //removes a single row
	for (int i = 0; i < gridWidth; i++) {
		theGrid[i][r]->disable();
	}
}

void Board::shiftRows(int r) {//shifts all rows down after deleting row r, overrides current row of ptrs to point at row above
	for (int i = r; i < gridHeight; i++) {
		for (int j = 0; j < gridWidth; j++) {
			if (i == gridHeight - 1) {
				theGrid[j][i] = nullptr;
			}
			else {
				theGrid[j][i] = theGrid[j][i + 1];
				if (theGrid[j][i] != nullptr) {
					theGrid[j][i]->setCoords(j, i);
				}
			}
		}
	}
}

bool Board::rowFull(int r) {//check if row r is full
	for (int i = 0; i < gridWidth; i++) {
		if (theGrid[i][r] == nullptr) {
			return false;
		}
	}
	return true;
}

void Board::newBlock() { //spawn new block
	currBlock = currLevel->createBlock(nextBlock);
	currBlock->setLevel(prevLevel);
	prevLevel = level;
	nextBlock = currLevel->createBlockType();
	td->updateNext(nextBlock);
	if (!textOnly) gd->updateNext(nextBlock);
}

void Board::dropBlock() { //drop current block
	currBlock->drop();
	liveBlocks.emplace_back(currBlock);
	checkRows();
	if (level == 4) {
		if ((currLevel->getCount() - 1) % 5 == 0 && currLevel->getCount() != 0) {
			spawnOneBlock();
			update();
		}
	}
	//testPrint();
	newBlock();
}

void Board::spawnOneBlock() { //creates the one cell block used for level 4
	currBlock = currLevel->createBlock(BlockType::OneBlock);
	currBlock->setLevel(level);
	update();
	currBlock->drop();
	liveBlocks.emplace_back(currBlock);
	checkRows();
}

void Board::replaceBlock(BlockType bt) { //replace current block with given input
	currBlock->disable();
	currBlock = currLevel->createBlock(bt);
	cerr << level << endl;
	currBlock->setLevel(level);
}

void Board::addLineScore(int r) { //adds the score for deleting r number of lines in current level
	score += (level + r) * (level + r);
	cerr << (level + r) * (level + r) << endl;
	td->updateScore(score);
	if (!textOnly) gd->updateScore(score);
	if (score > highScore) {
		highScore = score;
		td->updateHighScore(highScore);
		if (!textOnly) gd->updateHighScore(highScore);
	}
}
void Board::checkDeadBlocks() {	//searches through liveblocks to see if any have been completely deleted in order to add score
	for (int i = 0; i < liveBlocks.size(); i++) {
		if (liveBlocks[i]->checkCells()) {
			addBlockScore(liveBlocks[i]->getLevel());
			liveBlocks.erase(liveBlocks.begin() + i);
			i--;
		}
	}
}
void Board::addBlockScore(int l) { //adds a block's score
	score += (l + 1) * (l + 1);
	cerr << (l + 1) * (l + 1) << endl;
	td->updateScore(score);
	if (!textOnly) gd->updateScore(score);
	if (score > highScore) {
		highScore = score;
		td->updateHighScore(highScore);
		if (!textOnly) gd->updateHighScore(highScore);
	}
}
void Board::redraw() { //tell gd to redraw, print td to cout
	update();
	if (!textOnly) gd->redrawBoard();
	cout << *td;
}

bool Board::checkOccupied(int x, int y) { //check if a cell is occupied, also returns true if out of bounds
	if (x < 0 || x >= gridWidth || y < 0 || y >= gridHeight) {
		return true;
	}
	if (theGrid[x][y] == nullptr) {
		return false;
	}
	if (theGrid[x][y]->getState()) {
		return true;
	}
	return false;
}

bool Board::canSpawn() { //check if the next block can spawn in start location
	return currBlock->canSpawn();
}

void Board::setSeed(int s) { //set seed to s for using rand
	seed = s;
}

void Board::setFile(std::string file) {	//sets the file to read input from 
	currLevel->setFile(file);
}

int Board::getHighScore() {
	return highScore;
}

void Board::attachCell(int x, int y, Cell *c) { //attaches cell to the grid, and attach observers to the cell
	theGrid[x][y] = c;
	c->attach(this);
	c->attach(&(*td));
	if (!textOnly) c->attach(&(*gd));
}

BlockType Board::stringToBlockType(std::string s) { //returns a blocktype that correspondes to the given string, defaults T-block, 
	if (s == "I") {									//ignores oneblock since not an  actual in game block
		return BlockType::IBlock;
	}
	else if (s == "I") {							
		return BlockType::IBlock;
	}
	else if (s == "J") {
		return BlockType::JBlock;
	}
	else if (s == "O") {
		return BlockType::OBlock;
	}
	else if (s == "T") {
		return BlockType::TBlock;
	}
	else if (s == "S") {
		return BlockType::SBlock;
	}
	else if (s == "Z") {
		return BlockType::ZBlock;
	}
	else if (s == "L") {
		return BlockType::LBlock;
	}
	else {
		return BlockType::TBlock;
	}
}

void Board::setMult(int m) { //sets the multiplier for a command
	cmdMult = m;
}
void Board::hint() { //gives player hint for one turn

}

//for testing purposes, to check where cells are in the board
void Board::testPrint() {
	for (int i = gridHeight - 1; i >= 0; i--) {
		for (int j = 0; j < gridWidth; j++) {
			if (theGrid[j][i] == nullptr) {
				cout << ' ';
			}
			else {
				cout << "c";
			}
		}
		cout << endl;
	}
}
