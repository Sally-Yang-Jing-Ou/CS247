#include "Deck.h"
#include <iostream>
#include <cstdlib>
#include "shuffle.h"
#include <random>

using namespace std;

Deck::Deck() {
	init();
}

array<Card*, 52> &Deck::getMyDeck() {
	return myDeck_;
}

void Deck::init() {
	int i = 0;
	for (int suit = 0; suit < 4; suit ++ ){	//making an ordered deck of cards
		for (int rank = 0; rank < 13; rank ++) {
			Card* newCard = new Card((Suit)suit, (Rank)rank);
			myDeck_[i] = newCard;
			i++;
		}
	}
}

void Deck::shuffle(){
    static std::mt19937 rng(seed);

	int n = 52;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = myDeck_[n];
		myDeck_[n] = myDeck_[k];
		myDeck_[k] = c;
	}
}
