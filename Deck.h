#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <array>

extern int seed;

class Deck {
public:
	Deck();
	std::array<Card*, 52> &getMyDeck() ;	// getter for the deck
	void shuffle();
    void print();
private:
	void init();
	std::array<Card*, 52> myDeck_;
};

#endif
