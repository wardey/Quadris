#include <iostream>
#include <utility>
#include <iomanip>
#include "TextDisplay.h"
#include "Subject.h"
#include "Cell.h"
using namespace std;

TextDisplay::TextDisplay(int highScore, int score, int level, BlockType next)
	: highScore{ highScore }, score{ score }, level{ level }, next{ next } {
	for (int i = 0; i < gridWidth; i++) {
		theDisplay.emplace_back(vector<char>{});
		for (int j = 0; j < gridHeight; j++) {
			theDisplay[i].emplace_back(' ');
		}
	}
}

void TextDisplay::updateScore(int score) {
	this->score = score;
}

void TextDisplay::updateHighScore(int highScore) {
	this->highScore = highScore;
}

void TextDisplay::updateLevel(int level) {
	this->level = level;
}

void TextDisplay::updateNext(BlockType bt) {
	this->next = bt;
}

void TextDisplay::printBlock(ostream &out, BlockType bt) const {
	switch (bt) {
	case BlockType::IBlock:
		out << "IIII" << endl;
		return;
	case BlockType::JBlock:
		out << "J" << endl;
		out << "JJJ" << endl;
		return;
	case BlockType::OBlock:
		out << "OO" << endl;
		out << "OO" << endl;
		return;
	case BlockType::TBlock:
		out << "TTT" << endl;
		out << " T " << endl;
		return;
	case BlockType::SBlock:
		out << " SS" << endl;
		out << "SS" << endl;
		return;
	case BlockType::ZBlock:
		out << "ZZ" << endl;
		out << " ZZ" << endl;
		return;
	case BlockType::LBlock:
		out << "  L" << endl;
		out << "LLL" << endl;
		return;
	default:
		return;
	}
}

char TextDisplay::blockTypeToChar(BlockType bt) {
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
		break;
	}
}

void TextDisplay::notify(Subject &whoNotified) {
	Info info = whoNotified.getInfo();
	Info prevInfo = whoNotified.getPrevInfo();
	theDisplay[prevInfo.x][prevInfo.y] = ' ';
	newInfo.emplace_back(info);
	states.emplace_back(whoNotified.getState());
	notifyCounter++;
}

void TextDisplay::update() {
	for (int i = 0; i < notifyCounter; i++) {
		if (states[i])
			theDisplay[newInfo[i].x][newInfo[i].y] = blockTypeToChar(newInfo[i].bt);
	}
	notifyCounter = 0;
	states.clear();
	newInfo.clear();
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	out << setfill(' ');
	out << "Level:" << setw(7) << td.level << endl;
	out << "Score:" << setw(7) << td.score << endl;
	out << "Hi Score:" << setw(4) << td.highScore << endl;
	for (int i = 0; i < 11; i++) {
		out << "-";
	}
	out << endl;
	for (int i = td.gridHeight - 1; i >= 0; i--) {
		for (int j = 0; j < td.gridWidth; j++) {
			out << td.theDisplay[j][i];
		}
		out << endl;
	}
	for (int i = 0; i < 11; i++) {
		out << "-";
	}
	out << endl;
	out << "Next:" << endl;
	BlockType tmp = td.next;
	td.printBlock(out, tmp);
	return out;
}
