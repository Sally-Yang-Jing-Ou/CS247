#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include <vector>

extern int seed;

class Deck {
public:
	Deck();
	std::vector<Card*> &getMyDeck() ;	// getter for the deck
	void shuffle();
    void print();
private:
	void init();
	std::vector<Card*> myDeck_;

};

#endif
