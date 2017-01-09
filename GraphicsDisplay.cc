#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include "GraphicsDisplay.h"
#include "Cell.h"
#include "Subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow *xw) : xw{ xw } {
	for (int i = 0; i < gridWidth; i++) {
		theBoard1.emplace_back(vector<char>{});
		theBoard2.emplace_back(vector<char>{});
		for (int j = 0; j < gridHeight; j++) {
			theBoard1[i].emplace_back(' ');
			theBoard2[i].emplace_back(' ');
		}
	}
	drawBase();
}

void GraphicsDisplay::notify(Subject &whoNotified) {
	Info info = whoNotified.getInfo();
	Info prevInfo = whoNotified.getPrevInfo();
	theBoard1[prevInfo.x][prevInfo.y] = ' ';
	newInfo.emplace_back(info);
	states.emplace_back(whoNotified.getState());
	notifyCounter++;
}

void GraphicsDisplay::update() {
	for (int i = 0; i < notifyCounter; i++) {
		if (states[i])
		{
			theBoard1[newInfo[i].x][newInfo[i].y] = blockTypeToChar(newInfo[i].bt);
		}
	}
	notifyCounter = 0;
	states.clear();
	newInfo.clear();
}

void GraphicsDisplay::updateScore(int score) {
	//clear area
	xw->fillRectangle(140, 90, 100, 10, xw->White);
	this->score = score;
	//redraw score
	stringstream ss;
	ss << score;
	xw->drawString(140, 100, ss.str(), xw->Magenta);
}
void GraphicsDisplay::updateHighScore(int highScore) {
	//clear area
	xw->fillRectangle(160, 110, 100, 10, xw->White);
	this->highScore = highScore;
	//redraw highscore
	stringstream ss;
	ss << highScore;
	xw->drawString(160, 120, ss.str(), xw->Magenta);
}
void GraphicsDisplay::updateLevel(int level) {
	//clear area
	xw->fillRectangle(140, 70, 100, 10, xw->White);
	this->level = level;
	//redraw level
	stringstream ss;
	ss << level;
	xw->drawString(140, 80, ss.str(), xw->Magenta);
}
void GraphicsDisplay::updateNext(BlockType bt) {
	next = bt;
	drawNext();
}

void GraphicsDisplay::enable(bool b) { //sets isEnabled to b
	isEnabled = b;
}

int GraphicsDisplay::charToColor(char c) {
	switch (c) {
		case 'I':
			return 2; //red
		case 'J':
			return 3; //green
		case 'O':
			return 4; //blue
		case 'T':
			return 5; //cyan
		case 'S':
			return 6; //yellow
		case 'Z':
			return 7; //magenta
		case 'L':
			return 8; //orange
		case '*':
			return 9; //brown
		case '?':
			return 1; //black
		default:
			return 0; //white
	}
}

char GraphicsDisplay::blockTypeToChar(BlockType bt) {
	switch (bt) {
		case BlockType::IBlock:
			return 'I';
		case BlockType::JBlock:
			return 'J';
		case BlockType::OBlock:
			return 'O';
		case BlockType::TBlock:
			return 'T';
		case BlockType::SBlock:
			return 'S';
		case BlockType::ZBlock:
			return 'Z';
		case BlockType::LBlock:
			return 'L';
		case BlockType::OneBlock:
			return '*';
		default:
			return ' ';
	}
}

GraphicsDisplay::~GraphicsDisplay() {}

void GraphicsDisplay::drawBase() { //draw everything that doesnt need to be redrawn, just once on initialization
	//draw words
	xw->drawString(230, 40, "Quadris", xw->Magenta);
	xw->drawString(100, 80, "Level:", xw->Magenta);
	xw->drawString(100, 100, "Score:", xw->Magenta);
	xw->drawString(100, 120, "Hi Score:", xw->Magenta);
	xw->drawString(100, 710, "Next:", xw->Magenta);
	//draw background, 
	for (int i = 0; i <= 18; i++) {
		xw->fillRectangle(85, 130 + i * 30, 330, 1, xw->Black); //horizontal lines
	}
	for (int j = 0; j <= 11; j++) {
		xw->fillRectangle(85 + j * 30, 130, 1, 540, xw->Black); //vertical lines
	}
}

void GraphicsDisplay::redrawUI() { //level, score, highscore

}

void GraphicsDisplay::drawNext() { //called by board to draw the next block
	//clear next area
	xw->fillRectangle(140, 710, 130, 70, xw->White);
	//draw block
	switch (next) {
		case BlockType::IBlock:
			drawBorderedCell('I', 140, 710);
			drawBorderedCell('I', 170, 710);
			drawBorderedCell('I', 200, 710);
			drawBorderedCell('I', 230, 710);
			return;
		case BlockType::JBlock:
			drawBorderedCell('J', 140, 710);
			drawBorderedCell('J', 140, 740);
			drawBorderedCell('J', 170, 740);
			drawBorderedCell('J', 200, 740);
			return;
		case BlockType::OBlock:
			drawBorderedCell('O', 140, 710);
			drawBorderedCell('O', 170, 710);
			drawBorderedCell('O', 140, 740);
			drawBorderedCell('O', 170, 740);
			return;
		case BlockType::TBlock:
			drawBorderedCell('T', 140, 710);
			drawBorderedCell('T', 170, 710);
			drawBorderedCell('T', 200, 710);
			drawBorderedCell('T', 170, 740);
			return;
		case BlockType::SBlock:
			drawBorderedCell('S', 170, 710);
			drawBorderedCell('S', 200, 710);
			drawBorderedCell('S', 140, 740);
			drawBorderedCell('S', 170, 740);
			return;
		case BlockType::ZBlock:
			drawBorderedCell('Z', 140, 710);
			drawBorderedCell('Z', 170, 710);
			drawBorderedCell('Z', 170, 740);
			drawBorderedCell('Z', 200, 740);
			return;
		case BlockType::LBlock:
			drawBorderedCell('L', 140, 740);
			drawBorderedCell('L', 170, 740);
			drawBorderedCell('L', 200, 740);
			drawBorderedCell('L', 200, 710);
			return;
		default:
			return;
	}
}

void GraphicsDisplay::drawBorderedCell(char c, int x, int y) { //draw a cell of type c at position (x,y), comes with black borders
	//horizontal lines
	xw->fillRectangle(x, y, boxWidth, 1, xw->Black);
	xw->fillRectangle(x, y + boxHeight, boxWidth, 1, xw->Black);
	//vertical lines
	xw->fillRectangle(x, y, 1, boxHeight, xw->Black);
	xw->fillRectangle(x + boxWidth, y, 1, boxHeight, xw->Black);
	//actual cell
	xw->fillRectangle(x + 1, y + 1, boxHeight - 2, boxWidth - 2, charToColor(c));
}

void GraphicsDisplay::drawBorderlessCell(char c, int x, int y) { //draw a cell of type c at position (x,y), no borders
	xw->fillRectangle(x + 1, y + 1, boxHeight - 2, boxWidth - 2, charToColor(c));
}

void GraphicsDisplay::redrawBoard() { //inefficient to redraw everything, should just redraw the blocks that changed
///check through board1 and compare with board2 to determine which cells need to be redrawn
	for (int i = 0; i < gridHeight; i++) {
		for (int j = 0; j < gridWidth; j++) {
			if (theBoard1[j][i] != theBoard2[j][i]) {
				drawBorderlessCell(theBoard1[j][i], 85 + 30 * j, 640 - 30 * i);
				theBoard2[j][i] = theBoard1[j][i];
			}
		}
	}
}
