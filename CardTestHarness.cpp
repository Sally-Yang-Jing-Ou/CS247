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
#include "Players.h"
#include "PlayersHuman.h"
#include "PlayersComputer.h"
#include "GameLogic.h"

using namespace std;

int seed = 0;

int main(int argc, char const *argv[])
{
	GameLogic* newGame = new GameLogic();

	if (argc > 1) {
		seed = atoi(argv[1]); //0. Command Line Parameter
	}

	for (int i = 0; i < 4; i++){
		cout << "Is player " << i + 1<< " a human(h) or a computer(c)?" << endl;
		cout << ">";
		char playerChoice;
		cin >> playerChoice;
		newGame->invitePlayers(playerChoice, i);
	}

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
