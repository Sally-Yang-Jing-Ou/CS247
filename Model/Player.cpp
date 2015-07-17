#include <list>
#include "Player.h"
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

Player::Player(Log * log): oldScore_(0), log_(log) {}

Player::~Player() {
	PlayerDeck_.clear();
	PlayerDiscards_.clear();
}

Player::Player( Player& copyPlayer ) {
	PlayerDeck_ = copyPlayer.getDeck();
	PlayerDiscards_ = copyPlayer.getDiscards();
	oldScore_ = copyPlayer.getOldScore();
	log_ = copyPlayer.log_;
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

string Player::roundEndsMessage(int i) {
	stringstream roundEndStats;
	roundEndStats << "Player " << i + 1<< "'s discards:";
	if (!(getDiscards().empty())){
		for (std::list<Card*>::iterator it = getDiscards().begin(); it != getDiscards().end(); it++) {
			roundEndStats << " " << (**it); //list of discards
		}
	} else {
		roundEndStats << "";
	}
	roundEndStats << endl;
	roundEndStats << "Player " << i + 1<< "'s score: ";
	roundEndStats << getOldScore() << " + " << scoreGained() << " = ";
	setNewScore();
 	roundEndStats << getOldScore() << endl;
 	return roundEndStats.str();
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

Card* Player::playCard ( Card card, Table &table, int &theChosenOne ) {
	bool inHand = true;
	Card* card1 = NULL;
    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card){
        	card1 = *it;
        	inHand = false;
            break;
        }
    }
	eraseCardFromHand(card1); // delete this card from the hand
	
	table.placeCard(card1);
			
	assert(!inHand);

    cout << "Player " << theChosenOne + 1 << " plays " << card << "." << endl;

    stringstream sstm;
    sstm << "Player " << theChosenOne + 1 << " plays " << card << ".";
    string sendThis = sstm.str();
    log_->log(sendThis);


    theChosenOne = (theChosenOne + 1) % 4;
    return card1;
}

Card* Player::discardCard (Card card, Table &table, int &theChosenOne) {
	Card* card1 = NULL;
    for (std::list<Card*>::iterator it = this->getDeck().begin(); it != this->getDeck().end(); it++) {
        if ((**it) == card) {
            card1 = *it;
            break;
        }
    }
    assert(card1);
    eraseCardFromHand(card1);

    this->getDiscards().push_back(card1);

    cout << "Player " << theChosenOne + 1 << " discards " << card << "." << endl;

    stringstream sstm;
    sstm << "Player " << theChosenOne + 1 << " discards " << card << ".";
    string sendThis = sstm.str();
    log_->log(sendThis);

    theChosenOne = (theChosenOne + 1) % 4;
    return NULL;
}

void Player::addCardToHand (Card* card) {
	PlayerDeck_.push_back(card);
}
