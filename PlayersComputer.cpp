#include <istream>
#include <list>
#include "Card.h"
#include <stdlib.h>
#include "PlayersComputer.h"

using namespace std;

PlayersComputer::PlayersComputer() {}

PlayersComputer::~PlayersComputer() {}

PlayersComputer::PlayersComputer(Players& copyPlayer1 ):Players(copyPlayer1) {}

bool isLegal (Card *first, Card *second) {
	return first->getRank() == SEVEN ||
          (first->getSuit() == second->getSuit() && abs(first->getRank() - second->getRank()) <= 1);
}

Card* PlayersComputer::firstLegalCardInDeck (Table &table, bool &firstTurn) {
	Card *sevenSpade = new Card(SPADE, SEVEN);
    if (firstTurn) {
        firstTurn = false;
        return sevenSpade;
    }
	for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
		for (int i = 0; i < 4; i ++) {
			vector<Card*>* setOfSuit = table.returnArrayOfSets()->at(i);
			if (setOfSuit->size() > 0) {
                for (int j = 0; j < setOfSuit->size(); j ++) {
					if (isLegal(*it, setOfSuit->at(j))) {
                        return (*it);
                    }
				}
			}
		}
	}
	return NULL;
}

void PlayersComputer::makeMove (Table &table, bool &firstTurn, int &theChosenOne){
	Card *newCard = firstLegalCardInDeck (table, firstTurn);
	if (newCard != NULL) { //there is a legal card in deck
        Players::playCard(*newCard, theChosenOne);
	} else {
        Players::discardCard(**(this->getDeck().begin()), theChosenOne);
	}
}
