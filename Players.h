#ifndef _PLAYERS_
#define _PLAYERS_

#include <istream>
#include <list>
#include "Card.h"

class Players {
public: 
	Players();// constructor
    ~Players();  // destructor
    std::list<Card*> &getDeck(); //getter for player's deck

private: 
	std::list<Card*> playersDeck_; //each player's deck of cards
};

#endif