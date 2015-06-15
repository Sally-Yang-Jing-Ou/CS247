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
	arrayOfSets[1] = setOfDiamonds;
	arrayOfSets[2] = setOfHearts;
	arrayOfSets[3] = setOfSpades;

	// 5. Gameplay
	std::list<Card*> currentPlayerDeck;
	std::list<Card*> currentPlayerDiscards;
	bool firstTurn = true;

	while (!cin.eof()) {
		currentPlayerDeck = allPlayers[theChosenOne]->getDeck();
		currentPlayerDiscards = allPlayers[theChosenOne]->getDiscards();
		allPlayers[theChosenOne]->DoAction(firstTurn, currentPlayerDeck, arrayOfSets, currentPlayerDiscards, theChosenOne, allPlayers, myDeck);	
	}

	return 0;
}













