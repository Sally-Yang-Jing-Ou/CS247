#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "GameLogic.h"
#include <typeinfo>
#include <cassert>
#include <sstream>

using namespace std;

bool options_printed = false;

GameLogic::GameLogic() : isRoundFinished_(false), theChosenOne_(-1), mostRecentCard_(NULL), firstTurn_(true) {
	for (int i = 0; i<4; ++i) {
		allPlayerScores_[i]= 0;
	}
}

GameLogic::~GameLogic() {
	if(mostRecentCard_ != NULL) {
		mostRecentCard_ = NULL;
	}
	for (int i = 0; i < 4; i++) {
		Player *play = allPlayer_[i];
		if(play != NULL) {
			delete play;
		}
	}
}

GameLogic::InvalidMoveException::InvalidMoveException(std::string msg):
    message(msg){}

Deck &GameLogic::deck() {
	return deck_;
}

Table &GameLogic::table() {
	return table_;
}

int &GameLogic::theChosenOne() {
	return theChosenOne_;
}

int* GameLogic::allPlayerScores() {
	return allPlayerScores_;
}

bool GameLogic::isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 - 1 ||
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

bool GameLogic::isLegalPlayInCommand (Card theCard) {
	for (int i = 0; i < 4; i++) {
		vector<Card*>* setOfSuit = this->table().returnArrayOfSets()->at(i);
		if (!setOfSuit->empty()) {
			for (std::vector<Card*>::iterator it2 = setOfSuit->begin(); it2 != setOfSuit->end(); it2++) {
				if (**it2 == theCard) {
					return false;
				}
			}
		}
	}
	Card sevenSpade = Card(SPADE, SEVEN);
	if (this->firstTurn_ && theCard == sevenSpade) {
		this->firstTurn_ = false;
		return true;
	}

	for (int i = 0; i < 4; i++) {
		vector<Card*>* setOfSuit = this->table_.returnArrayOfSets()->at(i);
		if (!setOfSuit->empty()) {
			for (std::vector<Card*>::iterator it2 = setOfSuit->begin(); it2 != setOfSuit->end(); it2++) {
				if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
					return true;
				}
			}
		}
	}
	return false;
}

void GameLogic::printLegalPlays (std::list<Card*> currentPlayerDeck) {
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
					if (isLegalPlay((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
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
		printLegalPlays(currentPlayerDeck);
		cout << endl;
	} else {
		cout << "" << endl;
	}
}

bool GameLogic::legalPlayInDeckExists (std::list<Card*> currentPlayerDeck, Table &table) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		if ((*it)->getRank()==SEVEN) {
        	return true;
        }

		for (int i = 0; i < 4; i ++) {
			vector<Card*>* setOfSuit = table.returnArrayOfSets()->at(i);
			if (!setOfSuit->empty()) {
				for (std::vector<Card*>::iterator it2 = setOfSuit->begin(); it2 != setOfSuit->end(); it2++) {
					if (isLegalPlay((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void GameLogic::invitePlayer(int playerChoice){
	assert(playerChoice == 0 || playerChoice == 1);
	Player* newPlayer;
	if (playerChoice == 0) { //human player
		newPlayer = new HumanPlayer();
		allPlayer_.push_back(newPlayer); //put it in the array
		//cout << "invited!" << endl;
	} else if (playerChoice == 1) { //computer player
		newPlayer = new ComputerPlayer();
		allPlayer_.push_back(newPlayer);		
		//cout << "invited!" << endl;

	} else {
		cerr << "invalid command" << endl;
	}
}

void GameLogic::dealCards() {
	deck_.shuffle(); //shuffle the cards
	Player* currentPlayer;
	vector<Card*> deck = deck_.getMyDeck();
	for (int i = 0; i < 4; i ++) {
		currentPlayer = allPlayer_[i]; //cards for each player
		for (int j = 0; j < 13; j ++) {
			currentPlayer->addCardToHand(deck[i*13+j]);			
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

void GameLogic::playTurn(int index) {
	if (theChosenOne_ == -1) {return;}
	Player *player = allPlayer_[theChosenOne_];
	bool isPlayerComputer = dynamic_cast<ComputerPlayer*>(player) ? true : false;
	list<Card*> &currentHand = player->getDeck();

	if (!isPlayerComputer && index < currentHand.size()) {
    	list<Card*>::iterator it = currentHand.begin();
    	advance(it, index);
    	Card playedCard = **it;

		if (isLegalPlayInCommand(playedCard)) {
			mostRecentCard_ = player->playCard(playedCard, this->table(), theChosenOne_);

			notify();
		} else {
			if (!legalPlayInDeckExists(player->getDeck(), table())) {
				mostRecentCard_ = player->discardCard(playedCard, this->table(), theChosenOne_);

				notify();
			} else {
				throw InvalidMoveException("Invalid Move! Try again!");
			}	
		}
	} else if (isPlayerComputer) {
		if(mostRecentCard_ != NULL) {
			mostRecentCard_=NULL;
		}
		mostRecentCard_ = static_cast<ComputerPlayer*>(player)->makeMove(this->table(), this->firstTurn_, theChosenOne_);
		
		notify();
	} else {
		mostRecentCard_ = NULL;
	}

	player = allPlayer_[theChosenOne_];
	isPlayerComputer = dynamic_cast<ComputerPlayer*>(player) ? true : false;
    
    if ((player->isDeckEmpty())) {
		cout << "Round finished" << endl;

		isRoundFinished_ = true;
		roundStats_="";
		for (int i = 0; i < 4; i ++) {

			roundStats_ += allPlayer_[i]->roundEndsMessage(i);
			allPlayer_[i]->getDiscards().clear(); //destruct
		    table_.returnArrayOfSets()->at(i)->clear();
			allPlayerScores_[i] = allPlayer_[i]->getOldScore();
		}
		cout << roundStats_<<endl;
		mostRecentCard_ = NULL;
		
		notify();

		if (gameOver()) {
			isPlayerComputer = false;
			restartGame();

		} else {
			dealCards();
			beginGame();
		}
	}

	if (isPlayerComputer) {
		playTurn(-1);
	}

}

void GameLogic::beginGame() {
	table_.clearTable();
	this->firstTurn_ = true;
	isRoundFinished_ = false;
	notify();

	bool isPlayerComputer = dynamic_cast<ComputerPlayer*>(allPlayer_[theChosenOne_]) ? true : false;
	if (isPlayerComputer){
		playTurn(-1);
	}
}

bool GameLogic::gameOver () {
	for(int i = 0; i < PLAYER_COUNT; i++) {
		if(allPlayerScores_[i] >= 80) {
			return true;
		}
	}

	return false;
}

string GameLogic::winners() const {
	int min = allPlayerScores_[0];

	for(int i = 1; i < PLAYER_COUNT; i++) {
		if(allPlayerScores_[i] < min) {
			min = allPlayerScores_[i];
		}
	}

	vector<int> winningPlayerNumbers = vector<int>();

	for(int i = 0; i < PLAYER_COUNT; i++) {
		if(allPlayerScores_[i] == min) {
			winningPlayerNumbers.push_back(i + 1);
		}
	}

	stringstream winningPlayers;
	for(int i = 0; i < winningPlayerNumbers.size(); i++) {
		winningPlayers	<< "Player " << winningPlayerNumbers[i] << " wins!" << endl;
	}
	return winningPlayers.str();
}

void GameLogic::setSeed(int seed) {
	deck().setSeed(seed);
}

std::list<Card*> GameLogic::getHandForCurrentPlayer() {
	return allPlayer_[theChosenOne_]->getDeck();
}

Card* GameLogic::mostRecentCard() const {
	return mostRecentCard_;
}	

bool GameLogic::isRoundFinished() {
	return isRoundFinished_;
}	

string GameLogic::roundStats() {
	return roundStats_;
}

void GameLogic::restartGame(bool resetAll) {
	for(int i = 0; i < 4; i++) {
		
		if (resetAll && allPlayer_[i] != NULL) { //resetting players and scores
			delete allPlayer_[i];
		} else if (allPlayer_[i] != NULL) { //only resetting scores not players
			allPlayer_[i]->getDiscards().clear();
			allPlayer_[i]->getDeck().clear();
		}
		allPlayerScores_[i] = 0;
	}
	if (resetAll) {
		allPlayer_.clear();
	}
	
	theChosenOne_ = -1;
	isRoundFinished_ = false;
	deck().init();

	if(mostRecentCard_ != NULL) {
		mostRecentCard_ = NULL;
	}
}

void GameLogic::ragequit() {
	ComputerPlayer* computerPlayer = new ComputerPlayer(*this->allPlayer_[this->theChosenOne_]);
	this->allPlayer_[this->theChosenOne_] = computerPlayer;
	playTurn(-1);
}

vector<int> GameLogic::discardsAmount() const {
	vector<int> discards = vector<int>(4);
	for(int i = 0; i < 4; i++) {
		discards[i] = allPlayer_[i]->getDiscards().size();
	}

	return discards;
}

