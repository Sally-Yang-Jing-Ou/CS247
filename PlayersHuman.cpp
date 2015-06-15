#include "PlayersHuman.h"
#include "PlayersComputer.h"
#include <cassert>

using namespace std;

bool printed = false;

PlayersHuman::PlayersHuman() {}

PlayersHuman::~PlayersHuman() {}

bool isLegalPlay (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 || 
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
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
					setOfSuit.insert(newCard); //insert into the sets, legal play, tuck this card into one of the sets
					return true;
				}
			}
		}
	}
	return false;
}

void printLegalPlays (std::list<Card*> currentPlayerDeck, array<set<Card*, Players::lex_compare>, 4> arrayOfSets) {
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		printed = false;
		for (int i = 0; i < 4; i ++) {
			set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
			if (!setOfSuit.empty() && !printed) {
				for (std::set<Card*, Players::lex_compare>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
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

void PrintOutTable (std::list<Card*> currentPlayerDeck, array<set<Card*, Players::lex_compare>, 4> arrayOfSets) {
	cout << "Card on the table:" << endl;
	cout << "Clubs:";
	for (int i = 0; i < 4; i ++) {
		set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
		if (i==1) cout << "Diamonds:";
		else if (i==2) cout << "Hearts:";
		else if (i==3) cout << "Spades:";
		if (!setOfSuit.empty()) {
			for (std::set<Card*, Players::lex_compare>::iterator it = setOfSuit.begin(); it != setOfSuit.end(); it++) {
				cout << " " << ((*it)->getRankInString());
			}
			cout << endl;
		} else {
			cout << "" << endl;
		}
	}
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
		printLegalPlays(currentPlayerDeck, arrayOfSets);
		cout << endl;
	} else {
		cout << "" << endl;
	}
}

void DoActionPlay ( Command &command, std::array<std::set<Card*, Players::lex_compare>, 4> &arrayOfSets, bool &firstTurn, std::list<Card*> &currentPlayerDeck, int &theChosenOne ){
	while (!isLegalPlayInCommand(command.card, arrayOfSets, firstTurn)){
		cout << "This is not a legal play." << endl;
		cin >> command;
	}
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		if ((**it) == command.card) currentPlayerDeck.erase(it); // delete this card from the hand 
	}
	cout << "Player " << theChosenOne << " plays " << command.card << "." << endl;
	theChosenOne = (theChosenOne + 1) % 4;
}


void DoActionDiscard (std::list<Card*> &currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> &arrayOfSets, std::list<Card*> &currentPlayerDiscards, int &theChosenOne, Command &command){
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
}

void PlayersHuman::DoAction (bool &firstTurn, std::list<Card*> &currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> &arrayOfSets,
								std::list<Card*> &currentPlayerDiscards, int &theChosenOne, array<Players*, 4> &allPlayers, array<Card*, 52> myDeck) {
	Command command;
	cin >> command;

	PrintOutTable(currentPlayerDeck, arrayOfSets);
	if (command.type == PLAY) { //a) play <card>
		DoActionPlay(command, arrayOfSets, firstTurn, currentPlayerDeck, theChosenOne);

	} else if (command.type == DISCARD) { //b) discard <card>
		DoActionDiscard(currentPlayerDeck, arrayOfSets, currentPlayerDiscards, theChosenOne, command);

	} else if (command.type == DECK) { //c) print out the deck
		for (int i = 0; i < 52; i ++) {
			cout << *myDeck[i]; 
			if ((i%13)==0 && i!=0) {
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
		return;

	} else if (command.type == RAGEQUIT) { //e) ragequit
		PlayersComputer* computerPlayer = new PlayersComputer (*allPlayers[theChosenOne]);
		allPlayers[theChosenOne] = computerPlayer;
		cout << "Player " << theChosenOne << " ragequits. A computer will now take over." << endl;
	}

}

