#include "Deck.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#define CARD_COUNT 52

Deck::Deck() {
	init();
}

vector<Card*> &Deck::getMyDeck() {
	return myDeck_;
}

void Deck::setSeed(int seed) {
	seed_ = seed;
	rng_.seed(seed_);
}

void Deck::init() {
	rng_.seed(seed_);

	for (int i = 0; i < myDeck_.size(); i++) {
		delete myDeck_[i];
	}
	myDeck_.clear();

	int i = 0;
	for (int suit = 0; suit < 4; suit ++ ){	//making an ordered deck of cards
		for (int rank = 0; rank < 13; rank ++) {
			Card* newCard = new Card((Suit)suit, (Rank)rank);
			myDeck_.push_back(newCard);
			i++;
		}
	}
}

void Deck::shuffle(){
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng_() % n);
		--n;
		Card *c = myDeck_[n];
		myDeck_[n] = myDeck_[k];
		myDeck_[k] = c;
	}
}

void Deck::print() {
	for (int i=0; i<52; ++i) {
        cout << *myDeck_[i];
		if (((i+1)%13)==0) {
			cout << endl;
		} else {
			cout << " ";
		}
    }
}
