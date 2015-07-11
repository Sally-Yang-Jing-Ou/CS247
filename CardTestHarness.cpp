#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <list>
#include <set>
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "GameLogic.h"
#include <gtkmm/main.h>
#include "view.h"

using namespace std;

int seed = 0;

int main(int argc, char ** argv)
{
	Gtk::Main kit(argc, argv);
	GameLogic* newGame = new GameLogic();
	View view(newGame);
	Gtk::Main::run(view);

	if (argc > 1) {
		seed = atoi(argv[1]); //0. Command Line Parameter
	}

	// for (int i = 0; i < 4; i++){
	// 	cout << "Is player " << i + 1<< " a human(h) or a computer(c)?" << endl;
	// 	cout << ">";
	// 	string choice;
	// 	getline (cin, choice);
	// 	newGame->invitePlayer(choice.at(0), i);
	// }

	while (!newGame->gameOver()) {
		newGame->dealCards();
		newGame->beginGame();
	}

	vector<int> winners = newGame->winners();

	for(size_t i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i] << " wins!" << endl;
	}

	delete newGame;
	return 0;
}
