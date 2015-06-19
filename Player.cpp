#include <list>
#include "Player.h"
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

Player::Player(): oldScore_(0) {}

Player::~Player() {
	PlayerDeck_.clear();
	PlayerDiscards_.clear();
}

Player::Player( Player& copyPlayer ) {
	PlayerDeck_ = copyPlayer.getDeck();
	PlayerDiscards_ = copyPlayer.getDiscards();
	oldScore_ = copyPlayer.getOldScore();
}

std::list<Card*> &Player::getDeck() {
	return PlayerDeck_;
}

std::list<Card*> &Player::getDiscards() {
	return PlayerDiscards_;
}

int &Player::getOldScore() {
	return oldScore_;
}

void Player::setNewScore (){
	oldScore_ = getOldScore() + scoreGained();
}

bool Player::isDeckEmpty () {
	return getDeck().empty();
}

int Player::scoreGained() {
	int gains = 0;
	if (!(getDiscards().empty())){
		for (std::list<Card*>::iterator it = getDiscards().begin(); it != getDiscards().end(); it++) {
			gains += ((int)((*it)->getRank())) + 1;
		}
	}
	return gains;
}

void Player::roundEndsMessage(int i) {
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

void Player::eraseCardFromHand (Card *card) {
	list<Card*>::iterator deleteCard = find(PlayerDeck_.begin(), PlayerDeck_.end(), card);
	if(!(deleteCard == PlayerDeck_.end())) {
		PlayerDeck_.remove(*deleteCard);
	}
}

void Player::addCardToDiscards (Card *card) {
	PlayerDiscards_.push_back(card);
}

void Player::playCard ( Card card, Table &table, int &theChosenOne ) {
	bool inHand = true;

    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card){
            eraseCardFromHand(*it); // delete this card from the hand
			table.placeCard(*it);
			inHand = false;
            break;
        }
    }

	assert(!inHand);

    cout << "Player " << theChosenOne + 1 << " plays " << card << "." << endl;
    theChosenOne = (theChosenOne + 1) % 4;
}

void Player::discardCard (Card card, Table &table, int &theChosenOne) {
	bool inHand = true;

    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card) {
            eraseCardFromHand(*it);
			inHand = false;
            break;
        }
    }

	assert(!inHand);

    Card *newDiscard = new Card(card.getSuit(), card.getRank());
    this->getDiscards().push_back(newDiscard);

    cout << "Player " << theChosenOne + 1 << " discards " << card << "." << endl;
    theChosenOne = (theChosenOne + 1) % 4;
}
