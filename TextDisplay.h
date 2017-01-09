#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include <string>
#include "Observer.h"
#include "Enums.h"
#include "Info.h"
class Cell;

class TextDisplay : public Observer {
	std::vector<std::vector<char>> theDisplay;
	const int gridWidth = 11;
	const int gridHeight = 18;
	int score, highScore, level;
	BlockType next;
	std::vector<Info> newInfo;
	std::vector<bool> states;
	int notifyCounter = 0;
public:
	TextDisplay(int highScore, int score, int level, BlockType next);
//	void init();
	void printBlock(std::ostream &out, BlockType bt) const;
	void updateScore(int score);
	void updateHighScore(int highScore);
	void updateLevel(int level);
	void updateNext(BlockType bt);
	char blockTypeToChar(BlockType bt);
	void notify(Subject &whoNotified) override;
	void shiftRows(int r);
	void update();
	~TextDisplay();
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
