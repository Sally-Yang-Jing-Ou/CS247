#include "PlayersComputer.h"
#include "PlayersHuman.h"
#include "GameLogic.h"

using namespace std;

GameLogic::GameLogic() {}

GameLogic::~GameLogic() {}

Deck &GameLogic::deck() {
	return deck_;
}

Table &GameLogic::table() {
	return table_;
}

int &GameLogic::theChosenOne() {
	return theChosenOne_;
}

void GameLogic::invitePlayers(char playerChoice, int i){
	Players* newPlayer;
	if (playerChoice == 'h') { //human player
		newPlayer = new PlayersHuman();
		allPlayers_.push_back(newPlayer); //put it in the array
	} else if (playerChoice == 'c') { //computer player
		newPlayer = new PlayersComputer();
		allPlayers_.push_back(newPlayer);
	} else {
		cerr << "invalid command" << endl;
	}
}

void GameLogic::dealCards() {
	deck_.shuffle(); //shuffle the cards
	Players* currentPlayer; 
	vector<Card*> deck = deck_.getMyDeck();
	for (int i = 0; i < 4; i ++) {
		currentPlayer = allPlayers_[i]; //cards for each player
		for (int j = 0; j < 13; j ++) {
			currentPlayer->getDeck().push_back (deck[i*13+j]); 
		}
	}
	//determine who gets to go first
	Card sevenSpade = Card(SPADE, SEVEN);
	for (int i = 0; i < 52; i ++) {
		if (*deck[i] == sevenSpade) {
			theChosenOne_ = i/13;
		}
	}
}

void GameLogic::beginGame() {
    table_.clearTable();
	cout << "A new round begins. It's player " << theChosenOne_ + 1 << "'s turn to play." << endl;

	bool firstTurn = true;
    Players* currentPlayer = allPlayers_[theChosenOne_];
	while (!(allPlayers_[theChosenOne_]->isDeckEmpty())) { //continue to play game if no players have run out the cards
        currentPlayer = allPlayers_[theChosenOne_];
        currentPlayer->doAction(table_, firstTurn, theChosenOne_, allPlayers_, deck_.getMyDeck());
        theChosenOne_ = (theChosenOne_ + 1) % 4;
	}

	for (int i = 0; i < PLAYER_COUNT; i ++) {
		allPlayers_[i]->roundEndsMessage(i);
		allPlayers_[i]->getDiscards().clear(); //destruct
        table_.returnArrayOfSets()->at(i)->clear();
		allPlayersScores_[i] = allPlayers_[i]->getOldScore();
	}
}

bool GameLogic::gameOver () {
	for(int i = 0; i < PLAYER_COUNT; i++) {
		if(allPlayersScores_[i] >= 80) {
			return true;
		}
	}

	return false;
}

vector<int> GameLogic::winners() const {
	int min = allPlayersScores_[0];

	for(int i = 1; i < PLAYER_COUNT; i++) {
		if(allPlayersScores_[i] < min) {
			min = allPlayersScores_[i];
		}
	}

	vector<int> winningPlayerNumbers = vector<int>();

	for(int i = 0; i < PLAYER_COUNT; i++) {
		if(allPlayersScores_[i] == min) {
			winningPlayerNumbers.push_back(i + 1);
		}
	}

	return winningPlayerNumbers;
}

