#include "PlayersComputer.h"
#include "PlayersHuman.h"
#include "GameLogic.h"
#include <typeinfo>

using namespace std;

bool options_printed = false;

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

bool GameLogic::isLegalPlayHelper (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 - 1 ||
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

bool GameLogic::isLegalPlayInCommandHelper (Card theCard) { //TODO: this function is a liar
	Card sevenSpade = Card(SPADE, SEVEN);
	Card *newCard = new Card(theCard.getSuit(), theCard.getRank());
	if (this->firstTurn_ && theCard == sevenSpade) {
		this->firstTurn_ = false;
		this->table_.placeCard(newCard); //insert sevenSpade into setOfSpade
		return true;
	}

	for (int i = 0; i < 4; i++) {
		vector<Card*>* setOfSuit = this->table_.returnArrayOfSets()->at(i);
		if (!setOfSuit->empty()) { 
			for (std::vector<Card*>::iterator it2 = setOfSuit->begin(); it2 != setOfSuit->end(); it2++) {
				if (isLegalPlayHelper((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
					this->table_.placeCard(newCard); //insert into the sets, legal play, tuck this card into one of the sets
					return true;
				}
			}
		}
	}
	return false;
}

void GameLogic::printLegalPlaysHelper (std::list<Card*> currentPlayerDeck) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		if (this->firstTurn_) {
			cout << " " << "7S";
			break;
		} 
		options_printed = false;
		for (int i = 0; i < 4; i ++) {
			vector<Card*>* setOfSuit = this->table().returnArrayOfSets()->at(i);
			if (!setOfSuit->empty() && !options_printed) {

				for (std::vector<Card*>::iterator it2 = setOfSuit->begin(); it2 != setOfSuit->end(); it2++) {
					if (isLegalPlayHelper((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						cout << " " << (**it);
						options_printed = true;
						break;
					}
				}
			}
		}
	}
}

void GameLogic::printOptions (std::list<Card*> currentPlayerDeck) {
	this->table_.printTable();
	cout << "Your hand:";
	if (!currentPlayerDeck.empty()) {
		for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
			cout << " " << (**it);
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}

	cout << "Legal plays:";
	if (!currentPlayerDeck.empty()) {
		printLegalPlaysHelper(currentPlayerDeck);
		cout << endl;
	} else {
		cout << "" << endl;
	}
}

bool GameLogic::legalPlayInDeckExists (std::list<Card*> currentPlayerDeck, Table &table) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		for (int i = 0; i < 4; i ++) {
			vector<Card*>* setOfSuit = table.returnArrayOfSets()->at(i);
			if (!setOfSuit->empty()) {
				for (std::vector<Card*>::iterator it2 = setOfSuit->begin(); it2 != setOfSuit->end(); it2++) {
					if (isLegalPlayHelper((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						return true;
					}
				}
			}
		}
	}
	return false;
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

void GameLogic::playTurn(Players * player, bool shouldDisplayOptions) {
	bool isPlayerComputer = dynamic_cast<PlayersComputer*>(player) ? true : false;

	if (!isPlayerComputer) {
		if (shouldDisplayOptions) {
			printOptions(player->getDeck());
		}
		
		cout << ">";
		Command command;
		cin >> command;

		if (command.type == PLAY) { //a) play <card>
			if (isLegalPlayInCommandHelper(command.card)) {
				player->playCard(command.card, theChosenOne_);
			} else {
				cout << "This is not a legal play." << endl;	
				return playTurn(player, false);
			}
		} else if (command.type == DISCARD) { //b) discard <card>
			if (!legalPlayInDeckExists(player->getDeck(), table())) {
				player->discardCard(command.card, theChosenOne_);
			} else {
				cout << "You have a legal play. You may not discard." << endl;
				return playTurn(player, false);			
			}
		} else if (command.type == DECK) { //c) print out the deck
			this->deck_.print();
			return playTurn(player, false);
		} else if (command.type == QUIT) { //quit: clean up memory first
			for(int i=0; i<4; i++) {
				delete this->allPlayers_[i];
			}	    
			for (int i=0; i<52; i++) {
				delete deck_.getMyDeck()[i];
			}

			exit(0);
		} else if (command.type == RAGEQUIT) { //e) ragequit
			PlayersComputer* computerPlayer = new PlayersComputer(*this->allPlayers_[this->theChosenOne_]);
			this->allPlayers_[this->theChosenOne_] = computerPlayer;
			cout << "Player " << this->theChosenOne_ + 1 << " ragequits. A computer will now take over." << endl;
		}
	} else {
		// do computer stuff
	}
	
}

void GameLogic::beginGame() {
	table_.clearTable();
        cout << "A new round begins. It's player " << theChosenOne_ + 1 << "'s turn to play" << endl;
	this->firstTurn_ = true;
	while (!(allPlayers_[theChosenOne_]->isDeckEmpty())) { //continue to play game if no players have run out the cards
		playTurn(allPlayers_[theChosenOne_], true);
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


