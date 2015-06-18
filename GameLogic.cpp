#include "PlayersComputer.h"
#include "PlayersHuman.h"
#include "shuffle.h"
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
		allPlayers_[i] = newPlayer; //put it in the array
	} else if (playerChoice == 'c') { //computer player
		newPlayer = new PlayersComputer();
		allPlayers_[i] = newPlayer;
	} else {
		cerr << "invalid command" << endl;
	}
}

void GameLogic::dealCards() {
	deck_.shuffle(); //shuffle the cards
	Players* currentPlayer; 
	array<Card*, 52> deck = deck_.getMyDeck();
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
	cout << "A new round begins. It's player " << theChosenOne_ + 1 << "'s turn to play" << endl;

	std::list<Card*> currentPlayerDeck;
	std::list<Card*> currentPlayerDiscards;
	bool firstTurn = true;
	while (!(allPlayers_[theChosenOne_]->isDeckEmpty())) { //continue to play game if no players have run out the cards
		currentPlayerDeck = allPlayers_[theChosenOne_]->getDeck();
		currentPlayerDiscards = allPlayers_[theChosenOne_]->getDiscards();

        allPlayers_[theChosenOne_]->DoAction(table(), firstTurn, currentPlayerDeck, currentPlayerDiscards, theChosenOne_, allPlayers_, deck_.getMyDeck());
	}

	for (int i = 0; i < PLAYER_COUNT; i ++) {
		allPlayers_[i]->roundEndsMessage(i);
		allPlayers_[i]->getDiscards().clear(); //destruct
		(table_.returnArrayOfSets())[i].clear();
		allPlayersScores_[i] = allPlayers_[i]->getOldScore();
	}

	table_ = Table();
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

