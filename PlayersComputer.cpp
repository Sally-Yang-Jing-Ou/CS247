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

Card* firstLegalCardInDeck (std::list<Card*> currentPlayerDeck, array<set<Card*, Players::lex_compare>, 4> arrayOfSets, bool &firstTurn) {
	Card sevenSpade = Card(SPADE, SEVEN);
	for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
		for (int i = 0; i < 4; i ++) {
			set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[i];
			if (!setOfSuit.empty()) {
				for (std::set<Card*, Players::lex_compare>::iterator it2 = setOfSuit.begin(); it2 != setOfSuit.end(); it2++) {
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

void PlayersComputer::DoAction (bool &firstTurn, std::list<Card*> &currentPlayerDeck, std::array<std::set<Card*, Players::lex_compare>, 4> &arrayOfSets,
								std::list<Card*> &currentPlayerDiscards, int &theChosenOne, array<Players*, 4> &allPlayers, array<Card*, 52> myDeck) {
	Card *newCard = firstLegalCardInDeck (currentPlayerDeck, arrayOfSets, firstTurn);
	if (newCard!=NULL) { //there is a legal card in deck
		set<Card*, Players::lex_compare> setOfSuit = arrayOfSets[(int)newCard->getSuit()];
		setOfSuit.insert(newCard);
		for (std::list<Card*>::iterator it = currentPlayerDeck.begin(); it != currentPlayerDeck.end(); it++) {
			if ((**it) == *newCard) currentPlayerDeck.erase(it); // delete this card from the hand 
		}
		cout << "Player " << theChosenOne << " plays " << *newCard << "." << endl;
		theChosenOne = (theChosenOne + 1) % 4;
	} else {
		list<Card*>::iterator it = currentPlayerDeck.begin();	//discard the first card on hand
		currentPlayerDeck.erase(it);
		currentPlayerDiscards.push_back(*it); 
		cout << "Player " << theChosenOne << " discards " << (**it) << "." << endl;
		theChosenOne = (theChosenOne + 1) % 4;
	}
}
