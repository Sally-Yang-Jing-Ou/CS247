#include <iostream>
#include <list>
#include "Players.h"

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
	cout << "Player " << i << "'s discards:";
	if (!(getDiscards().empty())){
		for (std::list<Card*>::iterator it = getDiscards().begin(); it != getDiscards().end(); it++) {
			cout << " " << (**it); //list of discards
		}
	} else {
		cout << "";
	}
	cout << endl;
	cout << "Player " << i << "'s score: ";
	cout << getOldScore() << " + " << scoreGained() << " = ";
	setNewScore();
 	cout << getOldScore() << endl;
}

