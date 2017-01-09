#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
class Board;

class Game {
	std::vector<std::string> commands = {"left","right","down","clockwise","counterclockwise","drop",
		"levelup","leveldown","norandom","random","sequence", "I", "J", "L", "O", "S", "Z", "T", "restart", "hint"};
	int commandMultiplier;
	std::istream *source = &std::cin;
	std::shared_ptr<Board> board;
	int highScore = 0;
	int seed = 1;
	int initLevel = 0;
	bool textOnly = false;
	std::string file;
	int parseString(std::string s);//parse the string for a number
public:
	Game();
	void createBoard();
	void restart();
	void commandInterpret(int args, std::vector<std::string> commands); //interprets command line arguments passes in at start of program
	void multiplierInterpret(std::string input);
	void inputInterpreter(std::string input);
	int inputCounter(std::string input);
};
#endif
