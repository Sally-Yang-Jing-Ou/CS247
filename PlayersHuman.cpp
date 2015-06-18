#include "PlayersHuman.h"
#include "PlayersComputer.h"
#include <cassert>
#include <cstdlib>

using namespace std;

bool printed = false;

PlayersHuman::PlayersHuman() {}

PlayersHuman::~PlayersHuman() {}

bool isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 - 1 ||
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

bool isLegalPlayInCommand (Card theCard, Table &table, bool &firstTurn) {
	Card sevenSpade = Card(SPADE, SEVEN);
	Card *newCard = new Card(theCard.getSuit(), theCard.getRank());
	if (firstTurn && theCard == sevenSpade) {
		firstTurn = false;
		table.placeCard(newCard); //insert sevenSpade into setOfSpade
		return true;
	}

	for (int i = 0; i < 4; i++) {
		vector<Card*> setOfSuit = table.returnArrayOfSets()[i];
		if (!setOfSuit.empty()) { 
			for (std::vector<Card*>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
				if (isLegalPlay((int)theCard.getRank(), (int)(*it2)->getRank(), (int)theCard.getSuit(), (int)(*it2)->getSuit())) {
					table.placeCard(newCard); //insert into the sets, legal play, tuck this card into one of the sets
					return true;
				}
			}
		}
	}
	return false;
}

void printLegalPlays (std::list<Card*> currentPlayerDeck, Table &table, bool firstTurn) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		if (firstTurn) {
			cout << " " << "7S";
			break;
		} 
		printed = false;
		for (int i = 0; i < 4; i ++) {
			vector<Card*> setOfSuit = table.returnArrayOfSets()[i];
			if (!setOfSuit.empty() && !printed) {

				for (std::vector<Card*>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
					if (isLegalPlay((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						cout << " " << (**it);
						printed = true;
						break;
					}
				}
			}
		}
	}
}

bool checkLegalPlaysInDeck (std::list<Card*> currentPlayerDeck, Table &table) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		for (int i = 0; i < 4; i ++) {
			vector<Card*> setOfSuit = table.returnArrayOfSets()[i];
			if (!setOfSuit.empty()) {
				for (std::vector<Card*>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
					if (isLegalPlay((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void printOutTable (Table &table, std::list<Card*> currentPlayerDeck, bool firstTurn) {
	table.printTable();
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
		printLegalPlays(currentPlayerDeck, table, firstTurn);
		cout << endl;
	} else {
		cout << "" << endl;
	}
	cout << ">";
}

void PlayersHuman::DoActionPlay ( Command &command, Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck, int &theChosenOne ){
	while (!isLegalPlayInCommand(command.card, table, firstTurn)){
		cout << "This is not a legal play." << endl;
		cout << ">";
		cin >> command;
	}

	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
        if ((**it) == command.card){
            eraseCardFromHand(*it); // delete this card from the hand
            break;
        }
	}

	cout << "Player " << theChosenOne + 1 << " plays " << command.card << "." << endl;
	theChosenOne = (theChosenOne + 1) % 4;
}


void PlayersHuman::DoActionDiscard (std::list<Card*> &currentPlayerDeck, Table &table, std::list<Card*> &currentPlayerDiscards, int &theChosenOne, Command &command){
	while (checkLegalPlaysInDeck(currentPlayerDeck, table)){
		cout << "You have a legal play. You may not discard." << endl;
		cin >> command;
	}
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
        if ((**it) == command.card) {
            eraseCardFromHand(*it);
            break;
        }
	}

	Card *newDiscard = new Card((command.card).getSuit(), (command.card).getRank());
	currentPlayerDiscards.push_back(newDiscard); 

	cout << "Player " << theChosenOne + 1 << " discards " << command.card << "." << endl;
	theChosenOne = (theChosenOne + 1) % 4;	
}

void PlayersHuman::DoAction (Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck,
								std::list<Card*> &currentPlayerDiscards, int &theChosenOne, array<Players*, 4> &allPlayers, array<Card*, 52> myDeck) {

	printOutTable(table, currentPlayerDeck, firstTurn);

	Command command;
	cin >> command;

	if (command.type == PLAY) { //a) play <card>
		DoActionPlay(command, table, firstTurn, currentPlayerDeck, theChosenOne);

	} else if (command.type == DISCARD) { //b) discard <card>
		DoActionDiscard(currentPlayerDeck, table, currentPlayerDiscards, theChosenOne, command);

	} else if (command.type == DECK) { //c) print out the deck
		for (int i = 0; i < 52; i ++) {
			cout << *myDeck[i]; 
			if (((i+1)%13)==0) {
				cout << endl;
			} else {
				cout << " ";
			}
		}

	} else if (command.type == QUIT) { //quit: clean up memory first
		for(int i=0; i<4; i++) {
			delete allPlayers[i];
		}    
		for (int i=0; i<52; i++) {
			delete myDeck[i];
		}
		exit(0);

	} else if (command.type == RAGEQUIT) { //e) ragequit
		PlayersComputer* computerPlayer = new PlayersComputer (*allPlayers[theChosenOne]);
		allPlayers[theChosenOne] = computerPlayer;
		cout << "Player " << theChosenOne + 1 << " ragequits. A computer will now take over." << endl;
	}

}

