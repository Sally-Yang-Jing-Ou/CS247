#ifndef _DECK_
#define _DECK_

#include "../Card.h"
#include <vector>
#include <random>

class Deck {
public:
	Deck();
	std::vector<Card*> &getMyDeck() ;	// getter for the deck
	void shuffle();
    void print();
    void init();
	void setSeed(int seed);
private:
	std::vector<Card*> myDeck_;
	int seed_;
	std::mt19937 rng_;
};

#endif
