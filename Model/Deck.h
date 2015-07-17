#ifndef _DECK_
#define _DECK_

#include "../Card.h"
#include <vector>
#include <random>

class Deck {
public:
	Deck(); //constructor
	std::vector<Card*> &getMyDeck() ;	// getter for the deck
	void shuffle(); //shuffles the deck
    void print(); //outputs deck in console
    void init(); //initializes deck
	void setSeed(int seed); //setter for rng seed
private:
	std::vector<Card*> myDeck_; //backing data structure for deck
	int seed_; //seed that'll be passed to mt19937 for rng
	std::mt19937 rng_;
};

#endif
