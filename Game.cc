#include "Game.h"
#include "Board.h"
#include <sstream>
#include <string>
#include <memory>
using namespace std;

Game::Game() {}

int Game::parseString(std::string s) {
	istringstream ss{ s };
	int t;
	ss >> t;
	return t;
}

void Game::createBoard() {
	board = make_shared<Board>(highScore, textOnly, initLevel, seed, file);
}

void Game::restart() {
	board = make_shared<Board>(highScore, textOnly, initLevel, seed, file);
}

void Game::commandInterpret(int args, vector<string> commands) {
	for (int i = 1; i < args; i++) {
		if (commands[i] == "-text") {
			textOnly = true;
		}
		else if (commands[i] == "-seed") {
			i++;
			seed = parseString(commands[i]);
		}
		else if (commands[i] == "-scriptfile") {
			i++;
			file = commands[i];
		}
		else if (commands[i] == "-startlevel") {
			i++;
			initLevel = parseString(commands[i]);
		}
	}
}

void Game::multiplierInterpret(std::string input) { //sets multiplier in board before calling input inpterpreter
	int m = 1;
	string multiplier;
	string command;
	int counter = 0;
	while (input.at(counter) >= '0' && input.at(counter) <= '9') {
		counter++;
	}
	multiplier = input.substr(0, counter);
	command = input.substr(counter);
	istringstream ss{ multiplier };
	if ((ss >> m).fail()) {
		ss.clear();
	}
	board->setMult(m);
	inputInterpreter(command);
}

int Game::inputCounter(string input) {
	int counter = 0;
	for (int i = 0; i < commands.size(); i++) {
		if (commands[i].find(input) == 0 && !input.empty()) counter++;
	}
	return counter;
}

void Game::inputInterpreter(string input) { //handles restart and sequence commands, passes rest to board to handle
	int c = inputCounter(input);
	if (c > 1) {
		return;
	}
	for (int i = 0; i < commands.size(); i++) {
		if (commands[i].find(input) == 0 && !input.empty()) { //an input matches beginning section of a command
			if (commands[i] == "restart") {
				highScore = board->getHighScore();
				restart();
				return;
			}
			else if (commands[i] == "sequence") {
				istream *prevSource = source;
				string arg, command;
				*source >> arg;
				ifstream file{ arg };
				source = &file;
				while (!(*source >> command).fail()) {
					multiplierInterpret(command);
				}
				source = prevSource;
				return;
			}
			else if(commands[i] == "norandom"){
				string arg;
				*source >> arg;
				board->commandHandler(commands[i], arg);
				return;
			}
			else if(commands[i].size() == 1){
				board->commandHandler("replaceBlock", commands[i]);
				return;
			}
			else {
				board->commandHandler(commands[i]);
				return;		
			}
		}
	}
}

int main(int argc, char *argv[]) {
	Game newGame;
	vector<string> commands;
	for (int i = 0; i < argc; i++) {
		commands.emplace_back(argv[i]);
	}
	newGame.commandInterpret(argc, commands);
	newGame.createBoard();
	string s;
	while (cin >> s) {
		try {
			newGame.multiplierInterpret(s);
		}
		catch (...) {
			cerr << "Game Over" << endl;
			break;
		}
	}
}
