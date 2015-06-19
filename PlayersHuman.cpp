#include "PlayersHuman.h"
#include "PlayersComputer.h"
#include <cassert>
#include <cstdlib>

using namespace std;

bool printed = false;

PlayersHuman::PlayersHuman() {}

PlayersHuman::~PlayersHuman() {}

void PlayersHuman::playCard ( Card card, int &theChosenOne ){
    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card){
            eraseCardFromHand(*it); // delete this card from the hand
            break;
        }
    }

    cout << "Player " << theChosenOne + 1 << " plays " << card << "." << endl;
    theChosenOne = (theChosenOne + 1) % 4;
}

void PlayersHuman::discardCard (Card card, int &theChosenOne){
    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card) {
            eraseCardFromHand(*it);
            break;
        }
    }

    Card *newDiscard = new Card((card).getSuit(), (card).getRank());
    this->getDeck().push_back(newDiscard); 

    cout << "Player " << theChosenOne + 1 << " discards " << card << "." << endl;
    theChosenOne = (theChosenOne + 1) % 4;
}

