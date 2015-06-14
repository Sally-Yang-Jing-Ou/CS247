#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <array>
#include <list>
#include <set>
#include "Card.h"
#include "Command.h"
#include "shuffle.h"
#include "Players.h"
#include "PlayersHuman.h"
#include "PlayersComputer.h"

using namespace std;

bool printed = false;

bool isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 || 
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

struct lex_compare {
    bool operator() (const Card *lhs, const Card *rhs) const{
		return (int)(lhs->getRank()) < (int)(rhs->getRank());
    }
};

void printLegalPlays (std::list<Card*> currentPlayerDeck, std::set<Card*, lex_compare> setOfClubs, std::set<Card*, lex_compare> setOfDiamonds, std::set<Card*, lex_compare> setOfHearts, std::set<Card*, lex_compare> setOfSpades) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		printed = false;
		if (!setOfClubs.empty() && !printed) {
			for (std::set<Card*, lex_compare>::iterator it2 = setOfClubs.begin(); it2 != setOfClubs.end(); it2++) {
				if (isLegalPlay((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
					cout << " " << (**it);
					printed = true;
				}
			}
		}
		if (!setOfDiamonds.empty() && !printed) {
			for (std::set<Card*, lex_compare>::iterator it2 = setOfDiamonds.begin(); it2 != setOfDiamonds.end(); it2++) {
				if (isLegalPlay((int)(*it)->getRank(), (int)(*it2)->getRank(), (int)(*it)->getSuit(), (int)(*it2)->getSuit())) {
					cout << " " << (**it);
					printed = true;
				}
			}
		}
		if (!setOfHearts.empty() && !printed) {
			for (std::set<Card*, lex_compare>::iterator it2 = setOfHearts.begin(); it2 != setOfHearts.end(); it2++) {
				if (isLegalPlay((int)(*it)->getRank(), (int)(*it2)->getRank(), (int)(*it)->getSuit(), (int)(*it2)->getSuit())) {
					cout << " " << (**it);
					printed = true;
				}
			}
		}
		if (!setOfSpades.empty() && !printed) {
			for (std::set<Card*, lex_compare>::iterator it2 = setOfSpades.begin(); it2 != setOfSpades.end(); it2++) {
				if (isLegalPlay((int)(*it)->getRank(), (int)(*it2)->getRank(), (int)(*it)->getSuit(), (int)(*it2)->getSuit())) {
					cout << " " << (**it);
					printed = true;
				}
			}
		}
	}
}

bool isLegalPlayInCommand (Card theCard, std::set<Card*, lex_compare> &setOfClubs, std::set<Card*, lex_compare> &setOfDiamonds, std::set<Card*, lex_compare> &setOfHearts, std::set<Card*, lex_compare> &setOfSpades, bool &firstTurn) {
	Card sevenSpade = Card(SPADE, SEVEN);
	Card *newCard = new Card(theCard.getSuit(), theCard.getRank());
	if (firstTurn && theCard == sevenSpade) {
		firstTurn = false;
	} else {
		return false;
	}
	if (!setOfClubs.empty()) { 
		for (std::set<Card*, lex_compare>::iterator it2 = setOfClubs.begin(); it2 != setOfClubs.end(); it2++) {
			if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
				setOfClubs.insert(newCard);
				return true;
			}
		}
	}
	if (!setOfDiamonds.empty()) {
		for (std::set<Card*, lex_compare>::iterator it2 = setOfDiamonds.begin(); it2 != setOfDiamonds.end(); it2++) {
			if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
				return true;
			}
		}
	}
	if (!setOfHearts.empty()) {
		for (std::set<Card*, lex_compare>::iterator it2 = setOfHearts.begin(); it2 != setOfHearts.end(); it2++) {
			if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
				return true;
			}
		}
	}
	if (!setOfSpades.empty()) {
		for (std::set<Card*, lex_compare>::iterator it2 = setOfSpades.begin(); it2 != setOfSpades.end(); it2++) {
			if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char const *argv[])
{

	if (argc > 1) {
		if (isdigit(atoi(argv[1]))) {
			seed = atoi(argv[1]); //0. Command Line Parameter
		}
	}

	//1. Invite Players
	array<Players*, 4> allPlayers; //keep track of all 4 players

	for (int i = 0; i < 4; i++){
		cout << "Is player " << i << " a human(h) or a computer(c)?" << endl;
		string playerChoice;
		cin >> playerChoice;
		if (playerChoice == "h") { //human player
			PlayersHuman* newPlayer = new PlayersHuman();
			allPlayers[i] = newPlayer; //put it in the array
		} else if (playerChoice == "c") { //computer player
			PlayersComputer* newPlayer = new PlayersComputer();
			allPlayers[i] = newPlayer;
		} else {
			cerr << "invalid command" << endl;
			return 0; //invalid command
		}
	}

	//2. Shuffling and Dealing
	array<Card*, 52> myDeck; //deck of cards
	int i = 0;
	for (int suit = 0; suit < 4; suit ++ ){	//making an ordered deck of cards
		for (int rank = 0; rank < 13; rank ++) {
			Card* newCard = new Card((Suit)suit, (Rank)rank);
			myDeck [i] = newCard;
			i++;
		}
	}
	shuffle(myDeck); //shuffle the cards
	Players* currentPlayer; 
	currentPlayer = allPlayers[0]; //cards for the first player
	for (int i = 0; i < 13; i ++) {
		currentPlayer->getDeck().push_back (myDeck[i]); 
	}
	currentPlayer = allPlayers[1]; //cards for second player
	for (int i = 13; i < 26; i ++) {
		currentPlayer->getDeck().push_back (myDeck[i]); 
	}
	currentPlayer = allPlayers[2]; //cards for third player
	for (int i = 26; i < 39; i ++) {
		currentPlayer->getDeck().push_back (myDeck[i]); 
	}
	currentPlayer = allPlayers[3]; //cards for fourth player
	for (int i = 39; i < 52; i ++) {
		currentPlayer->getDeck().push_back (myDeck[i]); 
	}

	//3. Gameplay — Start
	Card sevenSpade = Card(SPADE, SEVEN);
	int theChosenOne;
	for (int i = 0; i < 52; i ++) {
		if (*myDeck[i] == sevenSpade) {
			theChosenOne = i/13;
		}
	}
	cout << "A new round begins. It's player " << theChosenOne << "'s turn to play" << endl;

	//4. Gameplay — Human Player
	set<Card*, lex_compare> setOfClubs;
	set<Card*, lex_compare> setOfDiamonds;
	set<Card*, lex_compare> setOfHearts;
	set<Card*, lex_compare> setOfSpades;

	cout << "Card on the table:" << endl;
	cout << "Clubs:";
	if (!setOfClubs.empty()) {
		for (std::set<Card*, lex_compare>::iterator it = setOfClubs.begin(); it != setOfClubs.end(); it++) {
			cout << " " << ((*it)->getRankInString());
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}
	cout << "Diamonds:";
	if (!setOfDiamonds.empty()) {
		for (std::set<Card*, lex_compare>::iterator it = setOfDiamonds.begin(); it != setOfDiamonds.end(); it++) {
			cout << " " << ((*it)->getRankInString());
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}
	cout << "Hearts:";
	if (!setOfHearts.empty()) {
		for (std::set<Card*, lex_compare>::iterator it = setOfHearts.begin(); it != setOfHearts.end(); it++) {
			cout << " " << ((*it)->getRankInString());
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}
	cout << "Spades:";
	if (!setOfSpades.empty()) {
		for (std::set<Card*, lex_compare>::iterator it = setOfSpades.begin(); it != setOfSpades.end(); it++) {
			cout << " " << ((*it)->getRankInString());
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}
	std::list<Card*> currentPlayerDeck = allPlayers[theChosenOne]->getDeck();
	cout << "Your hand:";
	if (!currentPlayerDeck.empty()) {
		for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
			cout << " " << (**it);
		}
		cout << endl;
	} else {
		cout << "" << endl;
	}

	cout << "Legal Plays:";
	if (!currentPlayerDeck.empty()) {
		printLegalPlays(currentPlayerDeck, setOfClubs, setOfDiamonds, setOfHearts, setOfSpades);
		cout << endl;
	} else {
		cout << "" << endl;
	}

	// 5. Gameplay — Commands
	Command command;
	cin >> command;

	bool firstTurn = true;
	while (!cin.eof()) {
		if (command.type == PLAY) {
			while (!isLegalPlayInCommand(command.card, setOfClubs, setOfDiamonds, setOfHearts, setOfSpades, firstTurn)){
				cout << "This is not a legal play." << endl;
				cin >> command;
			}
			cout << "Player " << theChosenOne << " plays " << command.card << "." << endl;

		} else if (command.type == DISCARD) {

		} else if (command.type == DECK) {

		} else if (command.type == QUIT) {

		} else if (command.type == RAGEQUIT) {

		} else if (command.type == BAD_COMMAND){

		}
	}
	return 0;
}













