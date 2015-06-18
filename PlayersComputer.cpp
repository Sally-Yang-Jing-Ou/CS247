#include <istream>
#include <list>
#include "Card.h"
#include "PlayersComputer.h"

using namespace std;

PlayersComputer::PlayersComputer() {}

PlayersComputer::~PlayersComputer() {}

PlayersComputer::PlayersComputer( Players& copyPlayer1 ):Players(copyPlayer1) {}

bool isLegal (int itRank, int it2Rank, int itSuit, int it2Suit) {
	if (itRank == 7 || 
	(itRank -1 == it2Rank && itSuit == it2Suit) ||
	(itRank +1 == it2Rank && itSuit == it2Suit)) {
		return true;
	}
	return false;
}

Card* firstLegalCardInDeck (std::list<Card*> currentPlayerDeck, Table &table, bool &firstTurn) {
	Card sevenSpade = Card(SPADE, SEVEN);
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		for (int i = 0; i < 4; i ++) {
			vector<Card*> setOfSuit = table.returnArrayOfSets()[i];
			if (!setOfSuit.empty()) {
				for (std::vector<Card*> ::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
					if (isLegal((int)((*it)->getRank()), (int)((*it2)->getRank()), (int)((*it)->getSuit()), (int)((*it2)->getSuit()))) {
						if (firstTurn) {
							if ((**it)==sevenSpade) {	//if first turn, must return sevenSpade
								firstTurn = false;
								return (*it);
							}
						} else {
							return (*it);
						}
					}
				}
			}
		}
	}
	return NULL;
}

void PlayersComputer::DoAction (Table &table, bool &firstTurn, std::list<Card*> &currentPlayerDeck,
								std::list<Card*> &currentPlayerDiscards, int &theChosenOne, array<Players*, 4> &allPlayers, array<Card*, 52> myDeck) {
	Card *newCard = firstLegalCardInDeck (currentPlayerDeck, table, firstTurn);
	cout << "PlayersComputer::DoAction" << endl;
	if (newCard!=NULL) { //there is a legal card in deck
		table.placeCard(newCard);
		for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
			if ((**it) == *newCard) currentPlayerDeck.erase(it); // delete this card from the hand 
		}
		cout << "Player " << theChosenOne + 1<< " plays " << *newCard << "." << endl;
		theChosenOne = (theChosenOne + 1) % 4;
	} else {
		list<Card*>::iterator it = currentPlayerDeck.begin();	//discard the first card on hand
		currentPlayerDeck.erase(it);
		currentPlayerDiscards.push_back(*it); 
		cout << "Player " << theChosenOne + 1 << " discards " << (**it) << "." << endl;
		theChosenOne = (theChosenOne + 1) % 4;
	}
}
