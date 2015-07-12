#ifndef _DECK_
#define _DECK_

#include "../Card.h"
#include <vector>

class Deck {
public:
	Deck();
	std::vector<Card*> &getMyDeck() ;	// getter for the deck
	void shuffle();
    void print();
	void setSeed(int seed);
private:
	void init();
	std::vector<Card*> myDeck_;
	int seed_;
};

#endif
