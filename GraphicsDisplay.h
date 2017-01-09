#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_
#include "window.h"
#include "Observer.h"
#include "Enums.h"
#include "Info.h"
#include <vector>
#include <memory>
class Cell;

class GraphicsDisplay : public Observer {
	Xwindow *xw;
	std::vector<std::vector<char>> theBoard1; //always the board being updated
	std::vector<std::vector<char>> theBoard2;	//always one turn behind board1
	const int gridHeight = 18;
	const int gridWidth = 11;
	const int boardWidth = 330;
	const int boardHeight = 540;
	const int boxHeight = 30;
	const int boxWidth = 30;
	int score, highScore, level;
	bool isEnabled; //not in use, fix later, board does not create a graphic display if text only
	BlockType next;
	std::vector<Info> newInfo;
	std::vector<bool> states;
	int notifyCounter = 0;
	std::vector<Info> changedInfos; //vector of infos corresponding to positions that have changed
	std::vector<Info> emptyInfos; //vector of infos that correspond to the previous position of infos in changedinfos

	void drawBase(); //one time draw everything on initialization
	void redrawUI(); //responsible for redrawing everything except the board
	void redrawCell(std::string s, int x, int y);
	int charToColor(char c);
	char blockTypeToChar(BlockType bt);
	void drawBorderedCell(char c, int x, int y);
	void drawBorderlessCell(char c, int x, int y);
public:
	GraphicsDisplay(Xwindow *xw);
	void redrawBoard(); //redraws parts of the board that have changed
	void updateScore(int score);
	void updateHighScore(int highScore);
	void updateLevel(int level);
	void updateNext(BlockType bt);
	void drawNext();
	void enable(bool b); //sets isEnabled to b
	void notify(Subject &whoNotified) override; //redraw individual cells on notify
	void update();
	~GraphicsDisplay();
};

#endif
