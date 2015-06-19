#include <list>
#include "Players.h"
#include <stdlib.h>
#include <algorithm>

using namespace std;

Players::Players(): oldScore_(0) {}

Players::~Players() {
	playersDeck_.clear();
	playersDiscards_.clear();
}

Players::Players( Players& copyPlayer ) {
	playersDeck_ = copyPlayer.getDeck();
	playersDiscards_ = copyPlayer.getDiscards();
	oldScore_ = copyPlayer.getOldScore();
}

std::list<Card*> &Players::getDeck() {
	return playersDeck_;
}

std::list<Card*> &Players::getDiscards() {
	return playersDiscards_;
}

int &Players::getOldScore() {
	return oldScore_;
}

void Players::setNewScore (){
	oldScore_ = getOldScore() + scoreGained();
}

bool Players::isDeckEmpty () {
	return getDeck().empty();
}

int Players::scoreGained() {
	int gains = 0;
	if (!(getDiscards().empty())){
		for (std::list<Card*>::iterator it = getDiscards().begin(); it != getDiscards().end(); it++) {
			gains += ((int)((*it)->getRank())) + 1;
		}
	}
	return gains;
}

void Players::roundEndsMessage(int i) {
	cout << "Player " << i + 1<< "'s discards:";
	if (!(getDiscards().empty())){
		for (std::list<Card*>::iterator it = getDiscards().begin(); it != getDiscards().end(); it++) {
			cout << " " << (**it); //list of discards
		}
	} else {
		cout << "";
	}
	cout << endl;
	cout << "Player " << i + 1<< "'s score: ";
	cout << getOldScore() << " + " << scoreGained() << " = ";
	setNewScore();
 	cout << getOldScore() << endl;
}

void Players::eraseCardFromHand (Card *card) {
	list<Card*>::iterator deleteCard = find(playersDeck_.begin(), playersDeck_.end(), card);
	if(!(deleteCard == playersDeck_.end())) {
		playersDeck_.remove(*deleteCard);
	}
}

void Players::addCardToDiscards (Card *card) {
	playersDiscards_.push_back(card);
}

void Players::playCard ( Card card, int &theChosenOne ){
    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card){
            eraseCardFromHand(*it); // delete this card from the hand
            break;
        }
    }

    cout << "Player " << theChosenOne + 1 << " plays " << card << "." << endl;
    theChosenOne = (theChosenOne + 1) % 4;
}

void Players::discardCard (Card card, int &theChosenOne){
    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card) {
            eraseCardFromHand(*it);
            break;
        }
    }

    Card *newDiscard = new Card(card.getSuit(), card.getRank());
    this->getDiscards().push_back(newDiscard);

    cout << "Player " << theChosenOne + 1 << " discards " << card << "." << endl;
    theChosenOne = (theChosenOne + 1) % 4;
}
