#include <istream>
#include <list>
#include "Card.h"
#include <stdlib.h>
#include "ComputerPlayer.h"

using namespace std;

ComputerPlayer::ComputerPlayer() {}

ComputerPlayer::~ComputerPlayer() {}

ComputerPlayer::ComputerPlayer(Player& copyPlayer1 ):Player(copyPlayer1) {}

bool isLegal (Card *first, Card *second) {
	return first->getRank() == SEVEN ||
          (first->getSuit() == second->getSuit() && abs(first->getRank() - second->getRank()) <= 1);
}

Card* ComputerPlayer::firstLegalCardInDeck (Table &table, bool &firstTurn) {
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

void ComputerPlayer::makeMove (Table &table, bool &firstTurn, int &theChosenOne){
	Card *newCard = firstLegalCardInDeck (table, firstTurn);
	if (newCard != NULL) { //there is a legal card in deck
        Player::playCard(*newCard, table, theChosenOne);
	} else {
        Player::discardCard(**(this->getDeck().begin()), table, theChosenOne);
	}
}
