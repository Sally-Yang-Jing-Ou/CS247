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
#include "View.h"
#include "Controller.h"

using namespace std;

int main(int argc, char ** argv)
{
	Gtk::Main kit(argc, argv);
	GameLogic gameLogic;
	Controller controller(&gameLogic);
	View view(&controller, &gameLogic);
	Gtk::Main::run(view);

	if (argc > 1) {
		seed = atoi(argv[1]); //0. Command Line Parameter
	}

	while (!gameLogic.gameOver()) {
		gameLogic.dealCards();
		gameLogic.beginGame();
	}

	vector<int> winners = gameLogic.winners();

	for(size_t i = 0; i < winners.size(); i++) {
		cout << "Player " << winners[i] << " wins!" << endl;
	}

	return 0;
}
