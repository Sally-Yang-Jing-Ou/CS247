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

bool isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 || 
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

bool checkLegalPlaysInDeck (std::list<Card*> currentPlayerDeck, array<set<Card*, Players::lex_compare>, 4> arrayOfSets) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		for (int i = 0; i < 4; i ++) {
			set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
			if (!setOfSuit.empty()) {
				for (std::set<Card*, Players::lex_compare>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
					if (isLegalPlay((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool isLegalPlayInCommand (Card theCard, array<set<Card*, Players::lex_compare>, 4> &arrayOfSets, bool &firstTurn) {
	Card sevenSpade = Card(SPADE, SEVEN);
	Card *newCard = new Card(theCard.getSuit(), theCard.getRank());
	
	if (firstTurn && theCard == sevenSpade) {
		firstTurn = false;
		arrayOfSets[3].insert(newCard); //insert sevenSpade into setOfSpade
		return true;
	} else {
		return false;
	}

	for (int i = 0; i < 4; i++) {
		set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
		if (!setOfSuit.empty()) { 
			for (std::set<Card*, Players::lex_compare>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
				if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
					setOfSuit.insert(newCard); //insert into the sets
					return true;
				}
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
	for (int i = 0; i < 4; i ++) {
		currentPlayer = allPlayers[i]; //cards for each player
		for (int j = 0; j < 13; j ++) {
			currentPlayer->getDeck().push_back (myDeck[i*13+j]); 
		}
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
	set<Card*, Players::lex_compare> setOfClubs;
	set<Card*, Players::lex_compare> setOfDiamonds;
	set<Card*, Players::lex_compare> setOfHearts;
	set<Card*, Players::lex_compare> setOfSpades;
	array< set<Card*, Players::lex_compare>, 4> arrayOfSets;
	arrayOfSets[0] = setOfClubs;
	arrayOfSets[0] = setOfDiamonds;
	arrayOfSets[0] = setOfHearts;
	arrayOfSets[0] = setOfSpades;

	// 5. Gameplay — Commands
	Command command;
	cin >> command;
	std::list<Card*> currentPlayerDeck;
	std::list<Card*> currentPlayerDiscards;
	bool firstTurn = true;

	while (!cin.eof()) {
		currentPlayerDeck = allPlayers[theChosenOne]->getDeck();
		currentPlayerDiscards = allPlayers[theChosenOne]->getDiscards();
		allPlayers[theChosenOne]->PrintOutTable(currentPlayerDeck, arrayOfSets);

		if (command.type == PLAY) { //a) play <card>
			while (!isLegalPlayInCommand(command.card, arrayOfSets, firstTurn)){
				cout << "This is not a legal play." << endl;
				cin >> command;
			}
			// legal play, tuck this card into one of the sets
			cout << "Player " << theChosenOne << " plays " << command.card << "." << endl;
			// delete this card from the hand 
			for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
				if ((**it) == command.card) currentPlayerDeck.erase(it);
			}
			theChosenOne = (theChosenOne + 1) % 4;

		} else if (command.type == DISCARD) { //b) discard <card>
			while (checkLegalPlaysInDeck(currentPlayerDeck, arrayOfSets)){
				cout << "You have a legal play. You may not discard." << endl;
				cin >> command;
			}
			for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
				if ((**it) == command.card) currentPlayerDeck.erase(it);
			}
			Card *newDiscard = new Card((command.card).getSuit(), (command.card).getRank());
			currentPlayerDiscards.push_back(newDiscard); 
			cout << "Player " << theChosenOne << " discards " << command.card << "." << endl;
			theChosenOne = (theChosenOne + 1) % 4;

		} else if (command.type == DECK) { //c) print out the deck
			for (int i = 0; i < 52; i ++) {
				cout << *myDeck[i]; 
				if ((i%13)==0 && i!=0) {
					cout << endl;
				} else {
					cout << " ";
				}
			}

		} else if (command.type == QUIT) {

		} else if (command.type == RAGEQUIT) {

		} else if (command.type == BAD_COMMAND){

		}
	}
	return 0;
}













