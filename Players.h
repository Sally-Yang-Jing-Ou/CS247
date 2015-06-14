#ifndef _PLAYERS_
#define _PLAYERS_

#include <istream>
#include <list>
#include <array>
#include <set>
#include "Card.h"

class Players {
public: 
	Players();// constructor
    ~Players();  // destructor
    std::list<Card*> &getDeck(); //getter for player's deck
    std::list<Card*> &getDiscards(); //getter for the discards
    struct lex_compare {
    	bool operator() (const Card *lhs, const Card *rhs) const{
			return (int)(lhs->getRank()) < (int)(rhs->getRank());
    	}
	};
    virtual void PrintOutTable (std::list<Card*> currentPlayerDeck, std::array<std::set<Card*, lex_compare>, 4> arrayOfSets) = 0; 

private: 
	std::list<Card*> playersDeck_; //each player's deck of cards
	std::list<Card*> playersDiscards_; //each player's deck of discards
};

#endif