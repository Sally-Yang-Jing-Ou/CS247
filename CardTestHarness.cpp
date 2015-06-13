#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <array>
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

	


	



	
	return 0;
}